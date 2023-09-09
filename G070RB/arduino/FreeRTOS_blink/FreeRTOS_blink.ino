/*
 * Based on Blink_AnalogRead example from: https://github.com/feilipu/Arduino_FreeRTOS_Library
 * Modified by: Frederic Pillon <frederic.pillon (at) st.com>
 */

/*
  Thanks to:
  https://github.com/stm32duino/STM32FreeRTOS/blob/main/examples/Blink_AnalogRead/Blink_AnalogRead.ino
 */

#include <STM32FreeRTOS.h>

void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

void setup() {

  Serial.begin(9600);

  while (!Serial) {
  }

  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"Blink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskHello
    ,  (const portCHAR *) "Hello"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  // start scheduler
  vTaskStartScheduler();
  Serial.println("Insufficient RAM");
  while(1);
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 200 / portTICK_PERIOD_MS ); // wait for 200m second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 200 / portTICK_PERIOD_MS ); // wait for 200m second
  }
}

void TaskHello(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;)
  {
    Serial.println("Hello!");
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}
