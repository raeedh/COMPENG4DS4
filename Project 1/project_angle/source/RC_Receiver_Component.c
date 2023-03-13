#include "RC_Receiver_Component.h"

SemaphoreHandle_t rc_hold_semaphore;
TaskHandle_t rc_task_handle;

void setupRCReceiverComponent()
{
    setupRCPins();

    setupUART_RC();

    /*************** RC Task ***************/
    //Create RC Semaphore
    //Create RC Task
}

void setupRCPins()
{
    //Configure RC pins
    CLOCK_EnableClock(kCLOCK_PortC);
    PORT_SetPinMux(PORTC, 3U, kPORT_MuxAlt3);

}

void setupUART_RC()
{
    //setup UART for RC receiver
    uart_config_t config;

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = 115200;
    config.enableTx = false;
    config.enableRx = true;

    UART_Init(RC_UART, &config, CLOCK_GetFreq(kCLOCK_CoreSysClk));
}

void rcTask(void* pvParameters)
{
    //RC task implementation
    BaseType_t status;

    SemaphoreHandle_t hold_semaphore = (SemaphoreHandle_t) pvParameters ;


    RC_Values rc_values;
    uint8_t* ptr = (uint8_t*) &rc_values;

	int motor_value;
    int angle_value;
    uint8_t led_value[3];

	if( xSemaphoreTake(hold_semaphore, portMAX_DELAY) == pdTRUE ){
		while (1)
		{

				UART_ReadBlocking(RC_UART, ptr, 1);
				if(*ptr != 0x20)
					continue;

				UART_ReadBlocking(UART1, &ptr[1], sizeof(rc_values) - 1);

				if(rc_values.header == 0x4020)
				{
//				printf("Channel 1 = %d\t", rc_values.ch1);
//				printf("Channel 2 = %d\t", rc_values.ch2);
				printf("Channel 3 = %d\t", rc_values.ch3); // used control joy stick motor input
				printf("Channel 4 = %d\t", rc_values.ch4); // used control joy stick angle input
//				printf("Channel 5 = %d\t", rc_values.ch5);
				printf("Channel 6 = %d\t", rc_values.ch6); // three mode motor switch
				printf("Channel 7 = %d\t", rc_values.ch7); // used to control joy stick motor or switch motor
				printf("Channel 8 = %d\r\n", rc_values.ch8); // used to control forward and back ward
				}



				if(rc_values.header == 0x4020)
				{

				if (rc_values.ch7 == 1000)
				{
						switch (rc_values.ch6)
						{
							case 1000:
								motor_value = rc_values.ch8 == 1000 ? 20 : -20;
								led_value[0] = 255;
								led_value[1] = 0;
								led_value[2] = 0;
								break;
							case 1500:
								motor_value = rc_values.ch8 == 1000 ? 60 : -60;
								led_value[0] = 255;
								led_value[1] = 255;
								led_value[2] = 0;
								break;
							case 2000:
								motor_value = rc_values.ch8 == 1000 ? 100 : -100;
								led_value[0] = 0;
								led_value[1] = 255;
								led_value[2] = 0;
								break;
						}
						if(rc_values.ch8 == 1500){
							motor_value = 0;
						}
					}
					else // speed controlled by joystick
					{


						motor_value = ((rc_values.ch3 - 1000) * 100) / 1000;

						led_value[0] = 0;
						led_value[1] = 0;
						led_value[2] = 255;

						if(rc_values.ch3 == 1500 || rc_values.ch8 == 1500 ){
							motor_value = 0;
						}

						if(rc_values.ch8 == 2000){
							motor_value = motor_value* -1;
						}

					}



					angle_value = ((rc_values.ch4 - 1000) * 200)/1000 - 100;

					if(rc_values.ch4 == 1500){
						angle_value = 0;
					}

					printf("motor speed now is %d\n",motor_value);
					printf("angle  now is %d\n",angle_value);



					status = xQueueSend(motor_queue,  &motor_value, portMAX_DELAY);
					if (status != pdPASS) {
						PRINTF("Queue Send failed!.\r\n");
						while (1)
							;
					}

					status = xQueueSend(angle_queue,  &angle_value, portMAX_DELAY);
					if (status != pdPASS) {
						PRINTF("Queue Send failed!.\r\n");
						while (1)
							;
					}

//					status = xQueueSend(led_queue, &led_value, portMAX_DELAY);
//					if (status != pdPASS) {
//						PRINTF("Queue Send failed!.\r\n");
//						while (1)
//							;
//					}
				}
			}
    }else{
		printf("please enter 1 to start rc control\n");
	}
}


