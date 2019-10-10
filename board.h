/**
  * @file    main.h
  * @version 1.0.0
  * @author  
  * @brief    
  * 
  */

/** Includes 
 */
#include "mbed.h"
#include "node_flow.h"

//UART
#define         PC_TXD         PC_10
#define         PC_RXD         PC_11
//Pin Defines for I2C Bus
#define         SDA            PB_9 
#define         SCL            PB_8
#define         I2C_FREQ       100000

#define BOARD DEVELOPMENT_BOARD_V1_1_0 