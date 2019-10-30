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
#include <string>

#include "debug.h"

/** Access Keys from TTN Network for Lorawan. In MSB format.
 *  Device parameters for Back-End registration
 Change in mbed_app.json
"lora.device-eui": "{ 0x00, 0x6E, 0x15, 0x9D, 0x9B, 0x1F, 0x1B, 0x26 }",
"lora.application-eui": "{ 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x02, 0x1A, 0xF3 }",
"lora.application-key": "{ 0x66, 0x72, 0x93, 0x0B, 0xE7, 0x5C, 0xD2, 0xFA, 0x49, 0xA8, 0xCB, 0xF7, 0xA4, 0xDD, 0x29, 0x67 }"
 */
//  //OTAA
//  static uint8_t LORAWAN_DEV_EUI[] = { 0x00, 0x6E, 0x15, 0x9D, 0x9B, 0x1F, 0x1B, 0x26 };
//  static uint8_t LORAWAN_APP_EUI[] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x02, 0x1A, 0xF3 };
//  static uint8_t LORAWAN_APP_KEY[] = { 0x66, 0x72, 0x93, 0x0B, 0xE7, 0x5C, 0xD2, 0xFA, 0x49, 0xA8, 0xCB, 0xF7, 0xA4, 0xDD, 0x29, 0x67 };
// //ABP CONNECTION
//  static uint32_t LORAWAN_DEV_ADDRESS=0x26011AF4;
//  static uint8_t NWK_SESSION_KEY[]={ 0xE9, 0x0E, 0x55, 0xEA, 0x02, 0x3A, 0x3C, 0x4B, 0x96, 0x5E, 0x0E, 0x65, 0x68, 0x3E, 0xF4, 0x2E };
//  static uint8_t APP_SESSION_KEY[]={ 0x01, 0xD8, 0xAC, 0x51, 0xE6, 0xFB, 0xD5, 0xC6, 0x5A, 0x33, 0x17, 0xF1, 0x03, 0x9E, 0xBA, 0xF7 };


            
string device_id("MyFabulousDevice01");
uint8_t sensor_id[]={30,10,15};
uint8_t device_type[]={20,10,5};
uint16_t reading_time_m[]={120,300,300};
uint16_t number_of_sensors=3;
uint8_t payload[9];
int next_time=10;

NodeFlow myapp(EEPROM_WC, I2C_SDA, I2C_SCL, I2C_FREQ);
//HDC1080 hdc(I2C_SDA, I2C_SCL);

int main()
{
    
    int sensor_value_t =10;
    //Example payload
    payload[0]=0;
    payload[1]= 20>>8 & 0xFF; // two byte number
    payload[2]=20 & 0xFF;
    payload[3]=20 & 0xFF;
    payload[4]= 20>>16 & 0xFF; // two byte number
    payload[5]= 20>>8 & 0xFF;
    payload[6]=20 & 0xFF;
    payload[7]=10 & 0xFF;
    payload[8]=36 & 0xFF;
    
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

