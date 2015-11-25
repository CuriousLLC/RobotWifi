#include "main.h"
#include "queue.h"
#include "uart.h"

static os_timer_t tick_timer;
static queue *recv_q;

//Main code function
void
timer_func(void *pArg)
{
    uint8_t station_count = wifi_softap_get_station_num();
    struct station_info *stations = wifi_softap_get_station_info();

    os_printf("Connected stations: %u\n", station_count);
    if (stations != NULL) {
        while (stations != NULL) {
            os_printf("  IP: %d.%d.%d.%d", IP2STR(&(stations->ip)));
            stations = STAILQ_NEXT(stations, next);
        }
        wifi_softap_free_station_info();
    }
}

void ICACHE_FLASH_ATTR
process_queue()
{
    if (!queue_empty(recv_q)) {
        os_printf("\nXXX %u Data in queue, processing\n", recv_q->items);
        while (!queue_empty(recv_q)) {
            uart_tx_one_char_no_wait(1, queue_pop(recv_q));
        }
    }

    system_os_post(user_qTaskPrio, 0, 0 );
}

void ICACHE_FLASH_ATTR
extra_init()
{
    // Create a 64 byte receive queue for data
    recv_q = queue_init(64);
    if (recv_q == NULL) {
        os_printf("Could not allocate receive queue\n");
        return;
    }

    init_udp(recv_q);

    //Start wifi config task
    system_os_task(process_queue, user_qTaskPrio, user_procTaskQueue, user_procTaskQueueLen);
    
    os_timer_setfn(&tick_timer, timer_func, NULL);
    os_timer_arm(&tick_timer, 1000, 1);

    system_os_post(user_qTaskPrio, 0, 0 );
}

//Init function 
void ICACHE_FLASH_ATTR
user_init()
{
    // Configure UART0 and UART1 to 115200
    // This also sets up a uart rx handler at priority 0.
    uart_init(115200, 115200);

    init_wifi();
    system_init_done_cb(extra_init);
}