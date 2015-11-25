/* 
 * File:   main.h
 * Author: rday
 *
 * Created on November 24, 2015, 9:27 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"
#include "mem.h"

#define user_qTaskPrio        2      // Highest priority is get Wifi configured
#define user_procTaskPrio        0
#define user_procTaskQueueLen    1

#ifdef	__cplusplus
extern "C" {
#endif

void init_wifi();
os_event_t    user_procTaskQueue[user_procTaskQueueLen];
void handle_wifi_event(System_Event_t *evt);


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

