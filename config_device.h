/**
  * @file    config_device.h
  * @version 0.0.0
  * @author  Rafaella Neofytou, Adam Mitchell
  * @brief   
  */

/** Define to prevent recursive inclusion
 */
#pragma once
#include "mbed.h"

/**CLOCK SYNCH SPECIFICS */
#define CLOCK_SYNCH false
#define CLOCK_SYNCH_TIME 120 //0-86400 time in seconds 

#define INTERRUPT_DELAY 21

/**SCHEDULER SPECIFICS */
#define SCHEDULER true
extern float scheduler[];
#define SCHEDULER_SIZE 6

/**-NBIOT ONLY- SEND SCHEDULER */
#define MAX_BUFFER_SENDING_TIMES 10
#define SEND_SCHEDULER true
extern float nbiot_send_scheduler[];
#define SEND_SCHEDULER_SIZE 3





