/**
  * @file    main.cpp
  * @version 1.0.0
  * @author   
  * @brief   Example of an application using the Think Pilot hardware/software
  * 
  */

/** Includes 
 */

Serial pc(PC_TXD, PC_RXD);


#include "board.h"

// #include "Dummy_Sensor_1.h"
// #include "Dummy_Sensor_2.h"

NodeFlow mydevice;

//uint8_t NumofSensors=2;
uint8_t sensorId[]={D1,D2};

uint8_t readingTime_m[]={5,3};


//Dummy_Sensor_1 SensorId[0];

int standby_time=0;

//periodic or specific time of day for NB-IOT
int sendTime_h=10;

int main()
{

 pc.baud(9600);
 mydevice.start();
 /**Wakeup type
  */
 WakeupType wakeup = mydevice.get_wakeup_type();
 //Initialisation/setup
 if (wakeup==WAKEUP_RESET) {
       pc.printf("\r\nWAKEUP_RESET");
      // mydevice.reset();
 /**After first wakeup from interrupt, sleep 5 mins without interrupt from pin
  * 
  */
       mydevice.set_max_interrupt_sleep(5);

/** Register each sensor to the eeprom
 *  Each sensor has to register to the EEPROM before starting to report data  
 */
       for (int i=0; i<sizeof(SensorId); i++ ) {
       mydevice.registerSensor(sensorId[i],readingTime_h[i]);
       }

//Calculates & returns the next sensor reading time defined by the user 
       mydevice.set_reading_time();
/** Uncoment for NB-IOT      
       mydevice.set_send_time(time);
*/

  }
 if (wakeup==WAKEUP_TIMER) {
       
       //if sensor/Check which sensor else just kick the wdg
       mydevice.SensorsHandler();
       printf("Sensor Reading time");

       //NB 


       //lora ModemSend
       mydevice.ModemSend(int port,sizeof(payload),FLAG);
       //User specific application
       standby_time=mydevice.next_reading_time();       
   }
 if (wakeup==WAKEUP_PIN) {
       printf("Trigger");
       //user specific application
       standby_time=mydevice.next_reading_time();
   }
 
  
  mydevice.enter_standby(standby_time); 
}

