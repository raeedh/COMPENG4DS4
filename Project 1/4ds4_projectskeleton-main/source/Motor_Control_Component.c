#include "Motor_Control_Component.h"

QueueHandle_t motor_queue;
QueueHandle_t angle_queue;

void setupMotorComponent()
{
    BaseType_t status;
    setupMotorPins();

    setupDCMotor();
    setupServo();

    /*************** Motor Task ***************/
    //Create Motor Queue
    motor_queue = xQueueCreate(10, sizeof(int)); // generic int queue for now, figure out exact size and type later

    //Create Motor Task
	status = xTaskCreate(motorTask, "motor task", 200, (void*) motor_queue, 2, NULL); // check priority for this
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

    /*************** Position Task ***************/
    //Create Angle Queue
    angle_queue = xQueueCreate(10, sizeof(int)); // generic int queue for now, figure out exact size and type later

    //Create Position Task
    status = xTaskCreate(positionTask, "position task", 200, (void*) angle_queue, 2, NULL); // check priority for this
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
}

void setupMotorPins()
{
    //Configure PWM pins for DC and Servo motors
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortA);

    PORT_SetPinMux(PORTC, 1U, kPORT_MuxAlt4);
    PORT_SetPinMux(PORTA, 6U, kPORT_MuxAlt3);
}

void setupDCMotor()
{
    //Initialize PWM for DC motor
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;
    ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;

    ftmParam.chnlNumber = FTM_CHANNEL_DC_MOTOR;
    ftmParam.level = pwmLevel;
    ftmParam.dutyCyclePercent = 7;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary = false;
    ftmParam.enableDeadtime = false;

    FTM_GetDefaultConfig(&ftmInfo);

    ftmInfo.prescale = kFTM_Prescale_Divide_128;
    FTM_Init(FTM_MOTOR, &ftmInfo);
    FTM_SetupPwm(FTM_MOTOR, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 50U, CLOCK_GetFreq(kCLOCK_BusClk));
    FTM_StartTimer(FTM_MOTOR, kFTM_SystemClock);
}

void setupServo()
{
    //Initialize PWM for Servo motor
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;
    ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;

    ftmParam.chnlNumber = FTM_CHANNEL_SERVO_MOTOR;
    ftmParam.level = pwmLevel;
    ftmParam.dutyCyclePercent = 7;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary = false;
    ftmParam.enableDeadtime = false;

    FTM_GetDefaultConfig(&ftmInfo);

    ftmInfo.prescale = kFTM_Prescale_Divide_128;
    FTM_Init(FTM_MOTOR, &ftmInfo);
    FTM_SetupPwm(FTM_MOTOR, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 50U, CLOCK_GetFreq(kCLOCK_BusClk));
    FTM_StartTimer(FTM_MOTOR, kFTM_SystemClock);
}

void updatePWM_dutyCycle(ftm_chnl_t channel, float dutyCycle)
{
    uint32_t cnv, cnvFirstEdge = 0, mod;

    /* The CHANNEL_COUNT macro returns -1 if it cannot match the FTM instance */
    assert(-1 != FSL_FEATURE_FTM_CHANNEL_COUNTn(FTM_MOTOR));

    mod = FTM_MOTOR->MOD;
    if(dutyCycle == 0U)
    {
        /* Signal stays low */
        cnv = 0;
    }
    else
    {
        cnv = mod * dutyCycle;
        /* For 100% duty cycle */
        if (cnv >= mod)
        {
            cnv = mod + 1U;
        }
    }

    FTM_MOTOR->CONTROLS[channel].CnV = cnv;
}

void motorTask(void* pvParameters)
{
    //Motor task implementation
    BaseType_t status;
    int *motorInput;
    float motorDutyCycle;

    while (1) {
		status = xQueueReceive(motor_queue, (void*) &motorInput, portMAX_DELAY);

		if (status != pdPASS) {
			PRINTF("Queue Receive failed!.\r\n");

			while (1)
				;
		}

		motorDutyCycle = *motorInput * 0.025f / 100.0f + 0.070745;

	updatePWM_dutyCycle(FTM_CHANNEL_DC_MOTOR, motorDutyCycle);
	}
}

void positionTask(void* pvParameters)
{
    //Position task implementation
    BaseType_t status;
    int *servoInput;
    float servoDutyCycle;

    while (1) {
		status = xQueueReceive(motor_queue, (void*) &servoInput, portMAX_DELAY);

		if (status != pdPASS) {
			PRINTF("Queue Receive failed!.\r\n");

			while (1)
				;
		}

		servoDutyCycle = *servoInput * 0.025f / 45.0f + 0.078;

	updatePWM_dutyCycle(FTM_CHANNEL_SERVO_MOTOR, servoDutyCycle);
	}
}
