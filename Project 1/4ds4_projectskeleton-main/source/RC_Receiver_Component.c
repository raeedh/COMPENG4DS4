#include "RC_Receiver_Component.h"

SemaphoreHandle_t rc_hold_semaphore;
TaskHandle_t rc_task_handle;

void setupRCReceiverComponent()
{
    BaseType_t status;
    setupRCPins();

    setupUART_RC();

    /*************** RC Task ***************/
    //Create RC Semaphore
    rc_hold_semaphore = xSemaphoreCreateBinary();

    //Create RC Task
    status = xTaskCreate(rcTask, "RC task", 200, (void*) rc_hold_semaphore, 2, rc_task_handle); // check priority for this
    if (status != pdPASS) {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
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

    RC_Values rc_values;
    uint8_t* ptr = (uint8_t*) &rc_values;

    int motor_value;
    int angle_value;
    uint8_t led_value[3];


    while (1)
    {
        UART_ReadBlocking(RC_UART, ptr, 1);
        if(*ptr != 0x20)
            continue;
        UART_ReadBlocking(RC_UART, &ptr[1], sizeof(rc_values) - 1);
        if(rc_values.header == 0x4020)
        {
            // printf("Channel 1 = %d\t", rc_values.ch1);
            // printf("Channel 2 = %d\t", rc_values.ch2);
            printf("Channel 3 = %d\t", rc_values.ch3); // used control joy stick motor input
            printf("Channel 4 = %d\t", rc_values.ch4); // used control joy stick angle input
            // printf("Channel 5 = %d\t", rc_values.ch5);
            printf("Channel 6 = %d\t", rc_values.ch6); // three mode motor switch
            printf("Channel 7 = %d\t", rc_values.ch7); // used to control joy stick motor or switch motor
            printf("Channel 8 = %d\r\n", rc_values.ch8); // used to control forward and back ward

            if (rc_values.ch8 == 1500) {
                motor_value = 0;
            }
            else if (rc_values.ch7 == 1000)
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
            }
            else // speed controlled by joystick
            {
                motor_value = rc_values.ch8 == 1000 ? (rc_values.ch3 - 1000) / 10 : (rc_values.ch3 - 1000) / -10;
                led_value[0] = 0;
                led_value[1] = 0;
                led_value[2] = 255;
            }

            angle_value = (rc_values.ch3 - 1500) * (45/500);

            status = xQueueSend(motor_queue, (void* ) &motor_value, portMAX_DELAY);
            if (status != pdPASS) {
                PRINTF("Queue Send failed!.\r\n");
                while (1)
                    ;
            }
            
            status = xQueueSend(angle_queue, (void* ) &angle_value, portMAX_DELAY);
            if (status != pdPASS) {
                PRINTF("Queue Send failed!.\r\n");
                while (1)
                    ;
            }

            status = xQueueSend(led_queue, (void* ) &led_value, portMAX_DELAY);
            if (status != pdPASS) {
                PRINTF("Queue Send failed!.\r\n");
                while (1)
                    ;
            }
        }
    }
}


