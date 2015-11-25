/* 
 * File:   queue.h
 * Author: rday
 *
 * Created on November 24, 2015, 2:29 PM
 */

#ifndef QUEUE_H
#define	QUEUE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct queue {
    char *data;
    char *head;
    char *tail;
    size_t max_size;
    size_t items;
} queue;

queue *queue_init(uint8 size);
bool queue_empty(queue* q);
bool queue_full(queue* q);
bool queue_push(queue* q, char ch);
char queue_pop(queue *q);
#ifdef	__cplusplus
}
#endif

#endif	/* QUEUE_H */

