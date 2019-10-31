/**
  * @file    main.cpp
  * @version 1.0.0
  * @author   
  * @brief   Example of an application using the Think Pilot hardware/software
  * 
  */

/** Includes 
 */
#include "node_flow.h"


            
string device_id("MyFabulousDevice01");
uint8_t sensor_id[]={30,10,15};
uint8_t device_type[]={20,10,5};
uint16_t reading_time_m[]={120,120,120};
uint16_t number_of_sensors=3;
uint8_t payload[9];
int next_time=10;

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

    myapp.joinTTN();
    
    /**It will only add sensors if they are not already initialized
     * 
     */
    myapp.add_sensors(sensor_id,device_type,reading_time_m,number_of_sensors);

    next_time= myapp.set_reading_time(reading_time_m,number_of_sensors);
    // if(isReadingTime(sensor1)){
        //if yes then read and store in bytes
        // int sensor_value=DHT.ReadTemp();
        // payload[1]= sensor_value>>8 & 0xFF; // two byte number
        // payload[2]=sensor_value & 0xFF;
        //myapp.addpayload(payload,sizeof(payload),port)
   
        
    // }
    //myapp.get_timestamp();
   

    myapp.sendTTN(1, payload, sizeof(payload));
    myapp.standby(next_time,true,true);
}

