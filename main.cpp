/**
  * @file    main.cpp
  * @version 1.0.0
  * @author   
  * @brief   Example of an application using the Think Pilot hardware/software
  * 
  */

/** Includes 
 */

#include "mbed.h"
#include "node_flow.h"
#include <string>

string device_id("MyFabulousDevice01");
uint8_t sensor_id[]={30,10,15};
uint8_t device_type[]={20,10,5};
uint16_t reading_time_m[]={60,120,120};
uint16_t number_of_sensors=3;


NodeFlow myapp(EEPROM_WC, I2C_SDA, I2C_SCL, I2C_FREQ);
//HDC1080 hdc(I2C_SDA, I2C_SCL);

int main()
{
    
    /**Returns wakeup type WAKEUP_RESET, WAKEUP_PIN
     * 
     */
    
    int retc=myapp.start(device_id);
    int next_time=10;

    /**It will only add sensors if they are not already initialized
     * 
     */
    myapp.add_sensors(sensor_id,device_type,reading_time_m,number_of_sensors);

    next_time= myapp.set_reading_time(reading_time_m,number_of_sensors);
    // if(isReadingTime(sensor1)){


        
    // }
   // myapp.get_timestamp();

    myapp.standby(next_time,true,true);
}

