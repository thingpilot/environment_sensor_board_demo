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

/**SCHEDULER SPECIFICS */
#define SCHEDULER false
extern float scheduler[];

#define NEXT_TIME 10 //scheduler working with seconds 

#define SCHEDULER_SIZE  1



