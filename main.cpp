/**
******************************************************************************
* @file    main.cpp
* @version 1.0.0
* @author  The User 
* @brief   Example of an application using the Wright || Earhart nodes by Think Pilot
******************************************************************************
* */

/** Includes 
 */
#include "node_flow.h"
         
string device_id("MyFabulousDevice01");
// uint8_t sensor_id[]={30,10,15,10};
//value from 0-65535  (45 days approx.) it will be awake every 2 hours to kick the watchdog, and once a day to sync the RTC
//uint16_t reading_time_s[]={120,120,120,120}; 

/**Reading specific times of the day.
 * Values from 0-23.59 where 0 value is exact midnight. Format HH.MM
 */  
float reading_specific_time_h_m[]={10,11.30,0.30,25.00,9.34,18.05}; 

uint8_t length= 3;
uint8_t payload[9];

uint16_t next_time=300; //in seconds

NodeFlow myapp(EEPROM_WC, I2C_SDA, I2C_SCL, I2C_FREQ);
//HDC1080 hdc(I2C_SDA, I2C_SCL);

int main()
{
    
    int sensor_value =40;
    //Example payload random values, hex
    payload[0]=0;                       //sent as a sign, 0 for pos & 1 for negative
    payload[1]=sensor_value>>8 & 0xFF; // two byte number
    payload[2]=sensor_value& 0xFF;
    payload[3]=sensor_value & 0xFF;     //One byte num
    payload[4]=sensor_value>>16 & 0xFF; // two byte number
    payload[5]=sensor_value>>8 & 0xFF;
    payload[6]=sensor_value & 0xFF;   //One byte num
    payload[7]=sensor_value & 0xFF;   
    payload[8]=sensor_value & 0xFF;

/**Returns wakeup type WAKEUP_RESET, WAKEUP_PIN
    * 
    */
    int retc=myapp.start(device_id);
  

// if(isReadingTime()){
    //if yes then read and store in bytes
    // int sensor_value=DHT.ReadTemp();
    // payload[1]= sensor_value>>8 & 0xFF; // two byte number
    // payload[2]=sensor_value & 0xFF;
    //other sensors }

    myapp.sendTTN(1, payload, sizeof(payload));
    myapp.receiveTTN();
    
    next_time=myapp.set_scheduler(reading_specific_time_h_m, 6);
    myapp.standby(100,true,true);
}

//SARA module
// int main()
// {
    
//     /**Returns wakeup type WAKEUP_RESET, WAKEUP_PIN
//      * 
//      */
//     int retc=myapp.start(device_id);

//     myapp.joinNBIOT();
    
//     /**It will only add sensors if they are not already initialized
//      * 
//      */
//     //myapp.add_sensors(sensor_id,reading_time_s,sizeof(sensor_id));

//     //next_time=myapp.task_scheduler(reading_specific_time_h_m);
//     //next_time=myapp.set_specific_reading_times(reading_specific_time_h_m);
//     // if(isReadingTime()){
//         //if yes then read and store in bytes
//         // int sensor_value=DHT.ReadTemp();
//         // payload[1]= sensor_value>>8 & 0xFF; // two byte number
//         // payload[2]=sensor_value & 0xFF;
//         //myapp.addpayload(payload,sizeof(payload))
//         //other sensors
//     // }

//     myapp.sendNBIOT(send_times);
//    // next_time= myapp.set_reading_time(reading_time_s, 4);
//    //next_time=myapp.task_scheduler(reading_specific_time_h_m);
//    myapp.standby(next_time,true,true);
// }