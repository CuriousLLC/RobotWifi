#include "main.h"
#include "user_config.h"
#include "espconn.h"
#include "mem.h"
#include "udp.h"

static queue *recv_q;
void recv_datagram(void *arg, char *pData, unsigned short len);

/**
 * Setup our UDP handler. The UDP receive callback will stick data
 * in the queue*, which should be accessible from the caller.
 * @param q queue pointer to store UDP data
 * @return 
 */
struct espconn*
init_udp(queue *q)
{
    sint8 err;
    struct espconn *conn;
    esp_udp *udp;

    conn = (struct espconn *)os_zalloc(sizeof(struct espconn));
    if (conn == NULL) {
        return NULL;
    }

    udp = (esp_udp *)os_zalloc(sizeof(esp_udp));
    if (udp == NULL) {
        return NULL;
    }

    conn->type = ESPCONN_UDP;
    conn->state = ESPCONN_NONE;
    udp->local_port = UDP_LISTEN_PORT;
    conn->proto.udp = udp;
    
    if (espconn_create(conn) < 0) {
        return NULL;
    }

    recv_q = q;
    espconn_regist_recvcb(conn, recv_datagram);
    
    return conn;
}

void
teardown_udp(struct espconn *conn)
{
    // XXX This is undocumented and the difference between 
    // espconn_delete and espconn_disconnect isn't spelled out.
    espconn_delete(conn);
    os_free(conn->proto.udp);
    os_free(conn);
}

/**
 * Called when a new datagram is received. If we are currently
 * processing a datagram, this function does NOT get called. The
 * datagram is simply dropped.
 * 
 * This callback does have higher priority than the queue process
 * task. If too much data is received, then we start dropping packets.
 */
void
recv_datagram(void *arg, char *pData, unsigned short len)
{
    uint8_t i=0;

    if ((len + recv_q->items) > recv_q->max_size) {
        os_printf("Dropping message, not enough buffer\n");
        return;
    }

    for(i=0; i<len; i++) {
        queue_push(recv_q, pData[i]);
    }
}