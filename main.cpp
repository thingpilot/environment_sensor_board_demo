/**
  * @file    main.cpp
  * @version 1.0.0
  * @author  
  * @brief    
  * 
  */

/** Includes 
 */
#include "main.h"

NodeFlow mydevice;
//HDT1080 HDT1080(); 
int standby_time=0;


int main()
{

 mydevice.start();
 //optional
 if (mydevice.alivebeat()==0){
    printf("\r\nSuccess\r\n");
 }
 else {
     printf("\r\nUnsuccess\r\n");
 }
 
 WakeupType wakeup = mydevice.get_wakeup_type();
 if (wakeup==WAKEUP_RESET) {
       
       mydevice.reset();
       //after first wakeup sleep 5 mins without interrupt from pin
       mydevice.set_max_interrupt_sleep(5);

/*I need to re-think about the following process
       Presentation- each sensor has to present itself before starting to report data
        
       
        uint8_t numSensors=3;
        uint8_t childSensorId[numSensors];
        uint8_t sensorType[numSensors];
        uint8_t readingTime_h[numSensors];
        const char *description=NULL;
        bool echo=true;
        mydevice.present(childSensorId[1],sensorType[1],readingTime_h[1],"Temp sensor/every hour",echo);
       //set devices each sensor type has a specific value for 1:Temp_C 
       mydevice.set_sensors(1,2);
       
*/

/**Calculates & returns the next sensor reading time defined by the user 
  *Finds the smallest interval, substracts from the second smallest 
  */
       standby_time=mydevice.next_reading_time();

       }
 if (wakeup==WAKEUP_TIMER) {
       
       //if sensor/Check which sensor else just kick the wdg
       mydevice.SensorsHandler();
       printf("Sensor Reading time");
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

