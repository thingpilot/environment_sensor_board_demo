/**
************************************************************************************
       __|__       
--@--@--(_)--@--@--
   _____ _     _       _     ______ _____ _       _   
  |_   _| |   (_)     | |    | ___ \_   _| |     | |  
    | | | |__  _ _ __ | | __ | |_/ / | | | | ___ | |_ 
    | | | '_ \| | '_ \| |/ / |  __/  | | | |/ _ \| __|
    | | | | | | | | | |   <  | |    _| |_| | (_) | |_ 
    \_/ |_| |_|_|_| |_|_|\_\ \_|    \___/|_|\___/ \__|
                                                                            
* @file    main.cpp
* @version 1.0.0
* @author  The User 
* @brief   Example of an application using the Wright || Earhart nodes by Think Pilot
*          A) Choose board, Wright for NB-IOT || Earhart for LoRaWan
*          B) For Earhart: Option to send with OTAA or ABP, all keys have to be specified 
*             in the mbed_lib.json in big endian byte order
*             Note: With OTAA the device have to rejoin the network each time, this 
*             increases security but it has higher power consumption rate.
*          C) For Earhart: Two options on scheduling sensing times, periodically or with
*             a scheduler 
*************************************************************************************
* */

/** Includes 
 */
#include "MyApp.h"

#include"HDC1080.h"
#include"OPT3001.h"
//value from 0-65535  (45 days approx.) it will be awake every 2 hours to kick the watchdog, and once a day to sync the RTC
//uint16_t reading_time_s[]={120,120,120,120}; 

// /**Reading specific times of the day.
//  * Values from 0-23.59 where 0 value is exact midnight. Format HH.MM
//  */ 
float scheduler[11]={17.55,18.27,19.33,20.4,22.5,1.30,5.40,9.50,8.5,12.57,13.00}; 

MyApp myapp;
//NodeFlow myapp(EEPROM_WC, I2C_SDA, I2C_SCL, I2C_FREQ);
HDC1080 hdc(I2C_SDA, I2C_SCL);
OPT3001 opt(I2C_SDA, I2C_SCL);
Serial a(PC_10, PC_11);


int main()
{ 
    
    myapp.start();
    // myapp.set_reading_time(scheduler,size(scheduler));
    // myapp.add_sensors(sensor_id,reading_time_s,size(sensor_id));
    // next_time=myapp.set_scheduler(scheduler,size(scheduler));
    // myapp.standby(120,true,true);
    
}


uint8_t* MyApp::HandlePeriodic(uint16_t &length){
    
    static uint8_t payload[9];
    int temp_C =100*hdc.ReadTemperature();
    a.printf("Temperature   : %d\r\n", temp_C);
    int hmdt_P =hdc.ReadHumidity();
    a.printf("ReadHumidity   : %d\r\n", hmdt_P);
    payload[0]=0;
    payload[1]=temp_C>>8 & 0xFF; // two byte number
    payload[2]=temp_C& 0xFF;
    payload[3]=hmdt_P& 0xFF;     //One byte num
    int lux_lx =100*opt.Readlight();
    a.printf("Light   : %d\r\n",lux_lx);
    payload[4]=lux_lx>>16 & 0xFF; // three byte number
    payload[5]=lux_lx>>8 & 0xFF;
    payload[6]=lux_lx & 0xFF;  
    payload[7]=lux_lx>>16 & 0xFF; // three byte number
    payload[8]=lux_lx>>8 & 0xFF;
    
    length=size(payload);
    return payload;  

}

int MyApp::setup(){

return 0;
}
int MyApp::HandleInterrupt(){
    

return 0;
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
//    //next_time= myapp.set_reading_time(reading_time_s, 4);
//    //next_time=myapp.task_scheduler(reading_specific_time_h_m);
//    myapp.standby(next_time,true,true);
// }