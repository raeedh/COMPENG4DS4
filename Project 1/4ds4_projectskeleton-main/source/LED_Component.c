#include "LED_Component.h"

QueueHandle_t led_queue;

void setupLEDComponent()
{
    BaseType_t status;
    setupLEDPins();

    setupLEDs();

    /*************** LED Task ***************/
    //Create LED Queue
    led_queue = xQueueCreate(10, sizeof(uint8_t*)); // generic int queue for now, figure out exact size and type later

    //Create LED Task
    status = xTaskCreate(ledTask, "LED task", 200, (void*) led_queue, 2, NULL); // check priority for this
}

void setupLEDPins()
{
    //Configure LED pins

    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    /* PORTD1 is configured as PTD1 */
    PORT_SetPinMux(PORTD, 1U, kPORT_MuxAlt4);

    /* PORTC8 is configured as PTC8 */
    PORT_SetPinMux(PORTC, 8U, kPORT_MuxAlt3);

    /* PORTC9 is configured as PTC9 */
    PORT_SetPinMux(PORTC, 9U, kPORT_MuxAlt3);
}

void setupLEDs()
{
    //Initialize PWM for the LEDs
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;

    ftmParam.chnlNumber = FTM_RED_CHANNEL;
    ftmParam.level = kFTM_HighTrue;
    ftmParam.dutyCyclePercent = 0;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary = false;
    ftmParam.enableDeadtime = false;

    FTM_GetDefaultConfig(&ftmInfo);

    FTM_Init(FTM_LED, &ftmInfo);
    FTM_SetupPwm(FTM_LED, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
    FTM_StartTimer(FTM_LED, kFTM_SystemClock);

    ftmParam.chnlNumber = FTM_BLUE_CHANNEL;
    ftmParam.level = kFTM_HighTrue;
    ftmParam.dutyCyclePercent = 0;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary = false;
    ftmParam.enableDeadtime = false;

    FTM_GetDefaultConfig(&ftmInfo);

    FTM_Init(FTM_LED, &ftmInfo);
    FTM_SetupPwm(FTM_LED, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
    FTM_StartTimer(FTM_LED, kFTM_SystemClock);

    ftmParam.chnlNumber = FTM_GREEN_CHANNEL;
    ftmParam.level = kFTM_HighTrue;
    ftmParam.dutyCyclePercent = 0;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary = false;
    ftmParam.enableDeadtime = false;

    FTM_GetDefaultConfig(&ftmInfo);

    FTM_Init(FTM_LED, &ftmInfo);
    FTM_SetupPwm(FTM_LED, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
    FTM_StartTimer(FTM_LED, kFTM_SystemClock);
}

void ledTask(void* pvParameters)
{
    //LED task implementation
    BaseType_t status;
    float red;
    float green;
    float blue;

    uint8_t *led_input;
    led_input = malloc(sizeof(uint8_t) * 3);

    while (1) {
        status = xQueueReceive(led_queue, (void*) &led_input, portMAX_DELAY);

        if (status != pdPASS) {
            PRINTF("Queue Receive failed!.\r\n");

            while (1)
                ;
        }

        printf("Received LED values from queue: %d %d %d\r\n", led_input[0], led_input[1], led_input[2]);

        red = (led_input[0] / 255.0) * 100;
        green = (led_input[1] / 255.0) * 100;
        blue = (led_input[2] / 255.0) * 100;

        FTM_UpdatePwmDutycycle(FTM_LED, FTM_RED_CHANNEL, kFTM_EdgeAlignedPwm, (uint8_t)red);
        FTM_SetSoftwareTrigger(FTM_LED, true);

        FTM_UpdatePwmDutycycle(FTM_LED, FTM_GREEN_CHANNEL, kFTM_EdgeAlignedPwm, (uint8_t)green);
        FTM_SetSoftwareTrigger(FTM_LED, true);

        FTM_UpdatePwmDutycycle(FTM_LED, FTM_BLUE_CHANNEL, kFTM_EdgeAlignedPwm, (uint8_t)blue);
        FTM_SetSoftwareTrigger(FTM_LED, true);
    }
}
