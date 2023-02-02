/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_ftm.h"
#include "fsl_uart.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TARGET_UART UART4
#define FTM_MOTOR FTM0
#define FTM_CHANNEL_DC_MOTOR kFTM_Chnl_0
#define FTM_CHANNEL_SERVO_MOTOR kFTM_Chnl_3

volatile char ch;
volatile int new_char = 0;
volatile char buffer[7];
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void setupUART();
void UART4_RX_TX_IRQHandler();
void setupPWM();
void updatePWM_dutyCycle(ftm_chnl_t channel, float dutyCycle);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void) {
//	char buffer[] = { 0, 0, 0, 0, 0, 0, 0 };
//
//	int motorInput;
//	int servoInput;
//	float motorDutyCycle;
//	float servoDutyCycle;
//
//	/* Init board hardware. */
//	BOARD_InitBootPins();
//	BOARD_InitBootClocks();
//	BOARD_InitDebugConsole();
//
//	setupUART();
//	setupPWM();
//
//	/******* Delay *******/
//	for (volatile int i = 0U; i < 10000000; i++)
//		__asm("NOP");
//
//	char txbuff[] = "Hello World aaron\r\n";
//	UART_WriteBlocking(TARGET_UART, txbuff, sizeof(txbuff) - 1);
//
//	while (1) {
//		UART_ReadBlocking(TARGET_UART, &buffer[0], 7);
//
//		sscanf(buffer, "%4d%3d", &motorInput, &servoInput);
//
//		motorDutyCycle = motorInput * 0.025f / 100.0f + 0.070745;
//		servoDutyCycle = servoInput * 0.025f / 45.0f + 0.078;
//
//		updatePWM_dutyCycle(FTM_CHANNEL_SERVO_MOTOR, servoDutyCycle);
//		updatePWM_dutyCycle(FTM_CHANNEL_DC_MOTOR, motorDutyCycle);
//
//		FTM_SetSoftwareTrigger(FTM_MOTOR, true);
//		FTM_SetSoftwareTrigger(FTM_MOTOR, true);
//	}
	char txbuff[] = "Hello World\r\n";

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	setupUART();

	/******* Delay *******/
	for (volatile int i = 0U; i < 10000000; i++)
		__asm("NOP");

	PRINTF("%s", txbuff);

	UART_WriteBlocking(TARGET_UART, txbuff, sizeof(txbuff) - 1);

	while (1) {
		if (new_char == 7) {
			new_char = 0;

			sscanf(buffer, "%4d%3d", &motorInput, &servoInput);

					motorDutyCycle = motorInput * 0.025f / 100.0f + 0.070745;
					servoDutyCycle = servoInput * 0.025f / 45.0f + 0.078;

					updatePWM_dutyCycle(FTM_CHANNEL_SERVO_MOTOR, servoDutyCycle);
					updatePWM_dutyCycle(FTM_CHANNEL_DC_MOTOR, motorDutyCycle);

					FTM_SetSoftwareTrigger(FTM_MOTOR, true);
					FTM_SetSoftwareTrigger(FTM_MOTOR, true);
		}
	}
}

void setupUART() {
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
	EnableIRQ(UART4_RX_TX_IRQn);
}

void UART4_RX_TX_IRQHandler() {
	UART_GetStatusFlags(TARGET_UART);
	ch = UART_ReadByte(TARGET_UART);

	if (new_char == 7) {
		return;
	}
	buffer[new_char] = ch;
	new_char += 1;
}

void setupPWM() {
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
	FTM_SetupPwm(FTM_MOTOR, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 50U,
			CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM_MOTOR, kFTM_SystemClock);

	ftmParam.chnlNumber = FTM_CHANNEL_SERVO_MOTOR;
	ftmParam.level = pwmLevel;
	ftmParam.dutyCyclePercent = 7;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;

	FTM_GetDefaultConfig(&ftmInfo);

	ftmInfo.prescale = kFTM_Prescale_Divide_128;
	FTM_Init(FTM_MOTOR, &ftmInfo);
	FTM_SetupPwm(FTM_MOTOR, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 50U,
			CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM_MOTOR, kFTM_SystemClock);
}

void updatePWM_dutyCycle(ftm_chnl_t channel, float dutyCycle) {
	uint32_t cnv, cnvFirstEdge = 0, mod;
	/* The CHANNEL_COUNT macro returns -1 if it cannot match the FTM instance */
	assert(-1 != FSL_FEATURE_FTM_CHANNEL_COUNTn(FTM_MOTOR));
	mod = FTM_MOTOR->MOD;
	if (dutyCycle == 0U) {
		/* Signal stays low */
		cnv = 0;
	} else {
		cnv = mod * dutyCycle;
		/* For 100% duty cycle */
		if (cnv >= mod) {
			cnv = mod + 1U;
		}
	}
	FTM_MOTOR->CONTROLS[channel].CnV = cnv;
}
