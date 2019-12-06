/**
************************************************************************************
*                               __|__       
*                        --@--@--(_)--@--@--                 
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
**/

/** Includes 
 */
#include "MyApp.h"
#include"HDC1080.h"
#include"OPT3001.h"

/**Two options: A)Scheduler. Reading specific times of the day. 
                B)Interval.
 * A) Values from 0-23.59 where 0 value is exact midnight. Format HH.MM
 */ 
//float scheduler[4]={60,20,20,20};

float nbiot_send_scheduler[2]={11,22};
float schedulerA[10]={17.38,17.40,17.15,17.20,18,19,1,5,11,13};
float schedulerB[4]={19,1,7,22};
float schedulerC[4]={12,1,6,20};

MyApp myapp;
HDC1080 hdc(I2C_SDA, I2C_SCL);
OPT3001 opt(I2C_SDA, I2C_SCL);
Serial a(TP_PC_TXU,TP_PC_RXU);

void MyApp::setup(){

}

int main(){ 

    myapp.start();
}

void MyApp::HandleInterrupt(){

    int increment_value;
    if(increment(1)==0){
        read_increment(&increment_value);
        a.printf("Incremented to   : %d\r\n", increment_value);
    }    
    else{
        a.printf("Error reading the increment\r\n");
    }
    
}

/**Default metric group for handling either scheduled times(SCHEDULED TRUE in the config_device.h) 
  * or a constant periodic time (SCHEDULED FALSE & SIZE 1) for all sensors 
  * To use the other metric groups the user has to define SCHEDULED FALSE && the SIZE
  * 
  */
uint8_t* MyApp::MetricGroupA(uint16_t &length){   
    a.printf("Welcome to MetricGroupA\r\n");

    int temp_C =100*hdc.ReadTemperature();
    uint8_t hmdt_P=hdc.ReadHumidity();
    uint32_t lux_lx =100*opt.Readlight();
    int increment_value;
    read_increment(&increment_value);

    add_record<uint16_t>(temp_C);
    add_record<uint8_t>(hmdt_P);
    add_record<uint16_t>(30);
    add_record<uint32_t>(lux_lx);
    add_record<uint8_t>(increment_value);


    static uint8_t payload[9];
    payload[0]=0;
    payload[1]=temp_C>>8 & 0xFF; // two byte number
    payload[2]=temp_C& 0xFF;
    payload[3]=hmdt_P& 0xFF;     //One byte num
    payload[4]=lux_lx>>16 & 0xFF; // three byte number
    payload[5]=lux_lx>>8 & 0xFF;
    payload[6]=lux_lx & 0xFF;
    payload[7]=increment_value & 0xFF;  //one byte
    payload[8]=increment_value & 0xFF;

    
    a.printf("Temperature:      : %d\r\n", temp_C);
    a.printf("ReadHumidity      : %d\r\n", hmdt_P);
    a.printf("Light             : %d\r\n", lux_lx);
    a.printf("Incremented to    : %d\r\n", increment_value);

    length=size(payload);

    return payload;
}



uint8_t* MyApp::MetricGroupB(uint16_t &length){
     a.printf("Welcome to MetricGroupB\r\n");
     static uint8_t payload[2];

     payload[0]=10& 0xFF;
     payload[1]=20& 0xFF;
     length=size(payload);
   
     return payload;
}

uint8_t* MyApp::MetricGroupC(uint16_t &length){
    a.printf("Welcome to MetricGroupC\r\n");
    static uint8_t payload[3];
    payload[0]=0;
    payload[1]=0;
    payload[2]=0;
    length=size(payload);
   
    return payload;  
}
uint8_t* MyApp::MetricGroupD(uint16_t &length){
    a.printf("Welcome to MetricGroupD\r\n");

    static uint8_t payload[4];
    payload[0]=0;
    payload[1]=0;
    payload[2]=0;
    payload[3]=0;
    length=size(payload);
     
    return payload;
}


