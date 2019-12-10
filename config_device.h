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


/**CLOCK SYNC/HEART BEAT*/
#define CLOCK_SYNCH false

/**SCHEDULER SPECIFICS - FALSE==INTERVAL, TRUE==SCHEDULED TIMES*/
#define SCHEDULER true

/**NBIOT ONLY- SEND SCHEDULER */
#define SEND_SCHEDULER false

#define INTERRUPT_DELAY 60
#define MAX_SEND_RETRIES 3
#define MAX_OVERWRITE_RETRIES 3

#if (SCHEDULER)
    #define SCHEDULER_A true
    #define SCHEDULER_B true
    #define SCHEDULER_C true
    #define SCHEDULER_D false

    #define SCHEDULER_A_SIZE 10
    #define SCHEDULER_B_SIZE 4
    #define SCHEDULER_C_SIZE 4
    #define SCHEDULER_D_SIZE 0
    #define SCHEDULER_SIZE (SCHEDULER_A_SIZE + SCHEDULER_B_SIZE + SCHEDULER_C_SIZE + SCHEDULER_D_SIZE)

    extern float scheduler[]; 
    extern float schedulerA[];
    extern float schedulerB[];
    extern float schedulerC[];
    extern float schedulerD[];
#endif

#if(!SCHEDULER)
    #define SCHEDULER_SIZE 8 /*SCHEDULER SIZE  */ //TODO: CHANGE THE NAME TO INTERVALS
    extern float scheduler[]; //CHANGE TO INTERVALS
#endif


//#if(SEND_SCHEDULER)
    #define MAX_BUFFER_SENDING_TIMES 10
    #define SEND_SCHEDULER_SIZE 2
    extern float nbiot_send_scheduler[];
//#endif

//#if (CLOCK_SYNCH)
    #define CLOCK_SYNCH_TIME 86400 //0-86400 time in seconds 
//#endif


