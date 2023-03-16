#include "Terminal_Component.h"

EventGroupHandle_t event_group;
QueueHandle_t uart_queue;

void setupTerminalComponent() {
    BaseType_t status;

    setupTerminalPins();

    setupUART();

    /*************** UART Task ***************/
    uart_queue = xQueueCreate(10, sizeof(char*));
    if (uart_queue == NULL) {
        PRINTF("Queue creation failed!.\r\n");
        while (1)
            ;
    }
    status = xTaskCreate(uartTask, "UART task", 200, NULL, 2, NULL);
    if (status != pdPASS) {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }

    /*************** Terminal Control Task ***************/
    //Create Event groups
    event_group = xEventGroupCreate();

    //Create Terminal Control Task
    status = xTaskCreate(terminalControlTask, "terminal control task", 200, (void*) event_group, 3, NULL);
    if (status != pdPASS) {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }

    TimerHandle_t timer_handle = xTimerCreate("Periodic timer", 500 / portTICK_PERIOD_MS,
    pdTRUE,
    NULL, terminalTimerCallback);
}

void setupTerminalPins() {
    //Configure UART pins
    CLOCK_EnableClock(kCLOCK_PortC);

    PORT_SetPinMux(PORTC, 12U, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTC, 13U, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTC, 14U, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTC, 15U, kPORT_MuxAlt3);
}

void sendMessage(const char *format, ...) {
    va_list args;

    char *str = (char*) pvPortMalloc(250 * sizeof(char));

    va_start(args, format);
    vsprintf(str, format, args);

    if (xQueueSendToBack(uart_queue, (void *) &str, portMAX_DELAY) != pdPASS) {
        PRINTF("Send message to uart_queue failed!.\r\n");
        while (1)
            ;
    }

    va_end(args);
}

void setupUART() {
    //Setup UART for sending and receiving
    uart_config_t config;

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = 57600;
    config.enableTx = true;
    config.enableRx = true;
    config.enableRxRTS = true;
    config.enableTxCTS = true;

    UART_Init(TARGET_UART, &config, CLOCK_GetFreq(kCLOCK_BusClk));

    /******** Enable Interrupts *********/
    UART_EnableInterrupts(TARGET_UART, kUART_RxDataRegFullInterruptEnable);

    NVIC_SetPriority(UART4_RX_TX_IRQn, 2);
    EnableIRQ(UART4_RX_TX_IRQn);
}

void uartTask(void *pvParameters) {
    char *welcome_message = "UART task started\n\r";
    char *received_str;
    BaseType_t status;

    UART_WriteBlocking(TARGET_UART, welcome_message, strlen(welcome_message));

    while (1) {
        status = xQueueReceive(uart_queue, (void*) &received_str, portMAX_DELAY);
        if (status != pdPASS) {
            PRINTF("Queue Send failed!.\r\n");
            while (1)
                ;
        }
        UART_WriteBlocking(TARGET_UART, received_str, strlen(received_str));
        vPortFree(received_str);
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void UART4_RX_TX_IRQHandler() {
    //UART ISR
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    UART_GetStatusFlags(TARGET_UART);
    char ch = UART_ReadByte(TARGET_UART);
    switch (ch) {
    case 'a':
        xEventGroupSetBitsFromISR(event_group, LEFT_BIT, &xHigherPriorityTaskWoken);
        break;
    case 's':
        xEventGroupSetBitsFromISR(event_group, DOWN_BIT, &xHigherPriorityTaskWoken);
        break;
    case 'd':
        xEventGroupSetBitsFromISR(event_group, RIGHT_BIT, &xHigherPriorityTaskWoken);
        break;
    case 'w':
        xEventGroupSetBitsFromISR(event_group, UP_BIT, &xHigherPriorityTaskWoken);
        break;
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void terminalTimerCallback(TimerHandle_t timer_handle) {
//    motor_value = 0;
//    angle_value = 0;
//    xSemaphoreGive(rc_hold_semaphore);
//
//    status = xQueueSend(motor_queue, (void* ) &motor_value, portMAX_DELAY);
//    if (status != pdPASS) {
//        PRINTF("Queue Send failed!.\r\n");
//        while (1)
//            ;
//    }
//
//    status = xQueueSend(angle_queue, (void* ) &angle_value, portMAX_DELAY);
//    if (status != pdPASS) {
//        PRINTF("Queue Send failed!.\r\n");
//        while (1)
//            ;
//    }
}

void terminalControlTask(void *pvParameters) {
    // Terminal Control Task implementation
    BaseType_t status;

    EventBits_t bits;

    int motor_value = 0;
    int angle_value = 0;

    while (1) {
        bits = xEventGroupWaitBits(event_group,
        LEFT_BIT | RIGHT_BIT | UP_BIT | DOWN_BIT,
        pdTRUE,
        pdFALSE, portMAX_DELAY);

//        xSemaphoreTake(rc_hold_semaphore, (TickType_t ) 0);
        printf("test2\r\n");

        if (bits) {
            if ((bits & (UP_BIT | DOWN_BIT)) == (UP_BIT | DOWN_BIT)) {
                motor_value = 0;
            } else if ((bits & UP_BIT) == UP_BIT) {
                motor_value = 20;
            } else if ((bits & DOWN_BIT) == DOWN_BIT) {
                motor_value = -20;
            }

            if ((bits & (LEFT_BIT | RIGHT_BIT)) == (LEFT_BIT | RIGHT_BIT)) {
                angle_value = 0;
            } else if ((bits & LEFT_BIT) == LEFT_BIT) {
                angle_value = 45;
            } else if ((bits & RIGHT_BIT) == RIGHT_BIT) {
                angle_value = -45;
            }

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
        }
    }
}
