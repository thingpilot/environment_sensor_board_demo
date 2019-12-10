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
float schedulerA[10]={17.37,17.40,18,20,21,3,1,5,9,8};
float schedulerB[4]={18,21,7,22};
float schedulerC[4]={8,21,6,20};

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
    read_increment(&increment_value);
    a.printf("Incremented to   : %d\r\n", increment_value);
}

/**Default metric group for handling either scheduled times(SCHEDULED TRUE in the config_device.h) 
  * or a constant periodic time (SCHEDULED FALSE & SIZE 1) for all sensors 
  * To use the other metric groups the user has to define SCHEDULED FALSE && the SIZE
  * 
  */
void MyApp::MetricGroupA(){   
    a.printf("Welcome to MetricGroupA\r\n");

    int temp_C =100*hdc.ReadTemperature(); 
    uint8_t hmdt_P=hdc.ReadHumidity();
    uint32_t lux_lx =100*opt.Readlight();
    int increment_value;
    read_increment(&increment_value);

    a.printf("Temperature:      : %d\r\n", temp_C);
    a.printf("ReadHumidity      : %d\r\n", hmdt_P);
    a.printf("Light             : %d\r\n", lux_lx);
    a.printf("Incremented to    : %d\r\n", increment_value);

    //it's 8 bytes but the first byte it will send will be the groups flag
    add_record<int16_t>(temp_C); 
    add_record<uint8_t>(hmdt_P);   
    add_record<uint32_t>(lux_lx);
    add_record<uint8_t>(increment_value);

}

void MyApp::MetricGroupB(){
     a.printf("Welcome to MetricGroupB\r\n");
     uint8_t randomB=10;
     a.printf("Random value:      : %d\r\n",randomB);
     add_record<uint8_t>(randomB); 
     
}

void MyApp::MetricGroupC(){
    a.printf("Welcome to MetricGroupC\r\n");
    uint8_t randomC=20;
    a.printf("Random value:      : %d\r\n",randomC );
    add_record<uint8_t>(randomC); 
   
}
void MyApp::MetricGroupD(){
    a.printf("Welcome to MetricGroupD\r\n");

}


