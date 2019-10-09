/**
  * @file    main.cpp
  * @version 1.0.0
  * @author  
  * @brief    Example of an application using the Think Pilot hardware/software
  * 
  */

/** Includes 
 */
#include "main.h"

#include "Dummy_Sensor_1.h"
#include "Dummy_Sensor_2.h"

NodeFlow mydevice;

//uint8_t NumofSensors=2;
uint8_t sensorId[]={D1,D2};
uint8_t seadingTime_h[]={5,10};


Dummy_Sensor_1 SensorId[0];

//int standby_time=0;


int main()
{

 mydevice.start();
 /**Wakeup type
  */
 WakeupType wakeup = mydevice.get_wakeup_type();
 //Initialisation/setup
 if (wakeup==WAKEUP_RESET) {
       
       mydevice.reset();
 /**After first wakeup from interrupt, sleep 5 mins without interrupt from pin
  * 
  */
       mydevice.set_max_interrupt_sleep(5);

/** Register each sensor to the eeprom
 *  Each sensor has to register to the EEPROM before starting to report data  
 */
       for (int i=0; i<sizeof(SensorId); i++ ) {
       mydevice.registerSensor(sensorId[i],seadingTime_h[i]);
       }

//Calculates & returns the next sensor reading time defined by the user 
       standby_time=mydevice.set_reading_time();

  }
 if (wakeup==WAKEUP_TIMER) {
       
       //if sensor/Check which sensor else just kick the wdg
       mydevice.SensorsHandler();
       printf("Sensor Reading time");
       //User specific application
       //standby_time=mydevice.next_reading_time();       
   }
 if (wakeup==WAKEUP_PIN) {
       printf("Trigger");
       //user specific application
       //standby_time=mydevice.next_reading_time();
   }
 

  mydevice.enter_standby(standby_time); 
}

