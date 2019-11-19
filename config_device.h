/**
  * @file    config_device.h
  * @version 0.0.0
  * @author  Rafaella Neofytou, Adam Mitchell
  * @brief   
  */

/** Define to prevent recursive inclusion
 */
#pragma once
#include <mbed.h>


/**CLOCK SYNCH SPECIFICS */
#define CLOCK_SYNCH true
#define CLOCK_SYNCH_TIME 0 //0-86400 time in seconds 

#define INTERRUPT_DELAY 5

/**SCHEDULER SPECIFICS */
#define SCHEDULER true
#define SCHEDULER_SIZE  11
extern float scheduler[];
extern uint16_t periodic[];





