/**
 * There is sure to be a queue implementation in the ESP NON OS SDK 
 * somewhere. But I certainly can't find it.
 */

#include "main.h"
#include "mem.h"
#include "queue.h"

queue *
queue_init(uint8 size)
{
    queue *q;

    q = (queue*)os_zalloc(sizeof(queue));
    if (q == NULL) {
        return NULL;
    }
    
    q->data = (char*)os_zalloc(sizeof(char) * size);
    if (q->data == NULL) {
        os_free(q);
        return NULL;
    }

    q->head = q->tail = q->data;
    q->max_size = size;
    q->items = 0;

    return q;
}

bool
queue_empty(queue* q)
{
    if(!q) {
        return true;
    }

    return q->head == q->tail;
}

bool
queue_full(queue* q)
{
    if(!q) {
        return true;
    }

    return q->items == q->max_size;
}

// Caller should check if queue is full before calling
bool
queue_push(queue* q, char ch)
{
    if (!q) {
        return false;
    }
    
    *(q->head) = ch;
    q->items++;

    if (q->head == (q->data + q->max_size)) {
        q->head = q->data;
    } else {
        q->head++;
    }
}

// Caller should check if the queue is empty before calling this.
// Otherwise the return value might not make sense.
char
queue_pop(queue *q)
{
    char ch;

    if (!q) {
        return false;
    }
    
    ch = *(q->tail);
    q->items--;

    if (q->tail == (q->data + q->max_size)) {
        q->tail = q->data;
    } else {
        q->tail++;
    }

    return ch;
}