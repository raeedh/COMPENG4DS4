/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_ftm.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void) {
	char ch;
	unsigned int duty_cycle = 0;
	unsigned int duty_cycle0 = 0;
	unsigned int duty_cycle1 = 0;
	unsigned int duty_cycle2= 0;
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	pwm_setup();

	//scanf("%x", &duty_cycle);

	//printf("%x\n", duty_cycle % 0xFF);
	scanf("%2x%2x%2x",  &duty_cycle2 , &duty_cycle1 , &duty_cycle0);

	printf("red = %x\n", duty_cycle2);
	printf("blue = %x\n", duty_cycle0);
	printf("green = %x\n", duty_cycle1);

	/*duty_cycle = duty_cycle / 0xFF;
	duty_cycle0 = duty_cycle << 24;
	duty_cycle0 = duty_cycle0 >> 24;
	printf("%x\n", duty_cycle0);


	duty_cycle1 = duty_cycle >> 8;
	duty_cycle1 = duty_cycle1 << 24;
	duty_cycle1 = duty_cycle1 >> 24;
	printf("%x\n", duty_cycle1);

	duty_cycle2 = duty_cycle >> 16;
	printf("%x\n", duty_cycle2);*/




	FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_1, kFTM_EdgeAlignedPwm,  (double)(duty_cycle2 / 0xFF) * 100);
	FTM_SetSoftwareTrigger(FTM3, true);

	FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_4, kFTM_EdgeAlignedPwm,  (double)(duty_cycle0 / 0xFF) * 100);
	FTM_SetSoftwareTrigger(FTM3, true);

	FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_5, kFTM_EdgeAlignedPwm,  (double)(duty_cycle1 / 0xFF) * 100);
	FTM_SetSoftwareTrigger(FTM3, true);

	while (1) {}
}

void pwm_setup() {
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;

	ftmParam.chnlNumber = kFTM_Chnl_1;
	ftmParam.level = kFTM_HighTrue;
	ftmParam.dutyCyclePercent = 0;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;

	FTM_GetDefaultConfig(&ftmInfo);

	FTM_Init(FTM3, &ftmInfo);
	FTM_SetupPwm(FTM3, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM3, kFTM_SystemClock);

	ftmParam.chnlNumber = kFTM_Chnl_4;
	ftmParam.level = kFTM_HighTrue;
	ftmParam.dutyCyclePercent = 0;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;

	FTM_GetDefaultConfig(&ftmInfo);

	FTM_Init(FTM3, &ftmInfo);
	FTM_SetupPwm(FTM3, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM3, kFTM_SystemClock);

	ftmParam.chnlNumber = kFTM_Chnl_5;
	ftmParam.level = kFTM_HighTrue;
	ftmParam.dutyCyclePercent = 0;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;

	FTM_GetDefaultConfig(&ftmInfo);

	FTM_Init(FTM3, &ftmInfo);
	FTM_SetupPwm(FTM3, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM3, kFTM_SystemClock);
}
