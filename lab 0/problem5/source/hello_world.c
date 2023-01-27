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
    unsigned int duty_cycle_red = 0;
    unsigned int duty_cycle_green = 0;
    unsigned int duty_cycle_blue = 0;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    pwm_setup();

    scanf("%2x%2x%2x", &duty_cycle_red, &duty_cycle_green, &duty_cycle_blue);

    printf("red = %x\n", duty_cycle_red);
    printf("green = %x\n", duty_cycle_green);
    printf("blue = %x\n", duty_cycle_blue);

    float red = (duty_cycle_red / 255.0) * 100;
    float green = (duty_cycle_green / 255.0) * 100;
    float blue = (duty_cycle_blue / 255.0) * 100;

    FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, (uint8_t)red);
    FTM_SetSoftwareTrigger(FTM3, true);

    FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_5, kFTM_EdgeAlignedPwm, (uint8_t)green);
    FTM_SetSoftwareTrigger(FTM3, true);

    FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_4, kFTM_EdgeAlignedPwm, (uint8_t)blue);
    FTM_SetSoftwareTrigger(FTM3, true);

    while (1) {
    }
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