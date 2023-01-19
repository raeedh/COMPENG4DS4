/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v5.0
processor: MK66FN2M0xxx18
package_id: MK66FN2M0VMD18
mcu_data: ksdk2_0
processor_version: 0.0.19
board: FRDM-K66F
functionalGroups:
- name: BOARD_InitPeripherals
  called_from_default_init: true
  id_prefix: DEMO_
  selectedCore: core0
- name: BOARD_InitADCPeripheral
  id_prefix: DEMO_
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LPTMR initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPTMR'
- type: 'lptmr'
- mode: 'LPTMR_GENERAL'
- type_id: 'lptmr_2eeab91a1a42f8238f9ac768f18c65ae'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPTMR0'
- config_sets:
  - fsl_lptmr:
    - enableInterrupt: 'false'
    - interrupt:
      - IRQn: 'LPTMR0_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - lptmr_config:
      - timerMode: 'kLPTMR_TimerModeTimeCounter'
      - pinSelect: 'ALT.0'
      - pinPolarity: 'kLPTMR_PinPolarityActiveHigh'
      - enableFreeRunning: 'false'
      - bypassPrescaler: 'true'
      - prescalerClockSource: 'kLPTMR_PrescalerClock_1'
      - clockSource: 'BOARD_BootClockVLPR'
      - value: 'kLPTMR_Prescale_Glitch_0'
      - timerPeriod: '1000000 us'
    - quick_selection: 'QS_LPTMR_1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lptmr_config_t DEMO_LPTMR_config = {.timerMode            = kLPTMR_TimerModeTimeCounter,
                                          .pinSelect            = kLPTMR_PinSelectInput_0,
                                          .pinPolarity          = kLPTMR_PinPolarityActiveHigh,
                                          .enableFreeRunning    = false,
                                          .bypassPrescaler      = true,
                                          .prescalerClockSource = kLPTMR_PrescalerClock_1,
                                          .value                = kLPTMR_Prescale_Glitch_0};

void DEMO_LPTMR_init(void)
{
    /* Initialize the LPTMR */
    LPTMR_Init(DEMO_LPTMR_PERIPHERAL, &DEMO_LPTMR_config);
    /* Set LPTMR period to 1000000us */
    LPTMR_SetTimerPeriod(DEMO_LPTMR_PERIPHERAL, DEMO_LPTMR_TICKS);
}

/***********************************************************************************************************************
 * BOARD_InitADCPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * ADC16 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'ADC16'
- type: 'adc16'
- mode: 'ADC'
- type_id: 'adc16_7d827be2dc433dc756d94a7ce88cbcc5'
- functional_group: 'BOARD_InitADCPeripheral'
- peripheral: 'ADC0'
- config_sets:
  - fsl_adc16:
    - adc16_config:
      - referenceVoltageSource: 'kADC16_ReferenceVoltageSourceVref'
      - clockSource: 'kADC16_ClockSourceAsynchronousClock'
      - enableAsynchronousClock: 'true'
      - clockDivider: 'kADC16_ClockDivider8'
      - resolution: 'kADC16_ResolutionSE16Bit'
      - longSampleMode: 'kADC16_LongSampleCycle24'
      - enableHighSpeed: 'false'
      - enableLowPower: 'true'
      - enableContinuousConversion: 'false'
    - adc16_channel_mux_mode: 'kADC16_ChannelMuxA'
    - adc16_hardware_compare_config:
      - hardwareCompareModeEnable: 'false'
    - doAutoCalibration: 'false'
    - trigger: 'false'
    - hardwareAverageConfiguration: 'kADC16_HardwareAverageCount32'
    - enable_irq: 'true'
    - adc_interrupt:
      - IRQn: 'ADC0_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - adc16_channels_config:
      - 0:
        - enableDifferentialConversion: 'false'
        - channelNumber: 'SE.26'
        - enableInterruptOnConversionCompleted: 'true'
      - 1:
        - enableDifferentialConversion: 'false'
        - channelNumber: 'SE.27'
        - enableInterruptOnConversionCompleted: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
adc16_channel_config_t DEMO_ADC16_channelsConfig[2] = {
    {.channelNumber = 26U, .enableDifferentialConversion = false, .enableInterruptOnConversionCompleted = true},
    {.channelNumber = 27U, .enableDifferentialConversion = false, .enableInterruptOnConversionCompleted = false}};
const adc16_config_t DEMO_ADC16_config            = {.referenceVoltageSource     = kADC16_ReferenceVoltageSourceVref,
                                          .clockSource                = kADC16_ClockSourceAsynchronousClock,
                                          .enableAsynchronousClock    = true,
                                          .clockDivider               = kADC16_ClockDivider8,
                                          .resolution                 = kADC16_ResolutionSE16Bit,
                                          .longSampleMode             = kADC16_LongSampleCycle24,
                                          .enableHighSpeed            = false,
                                          .enableLowPower             = true,
                                          .enableContinuousConversion = false};
const adc16_channel_mux_mode_t DEMO_ADC16_muxMode = kADC16_ChannelMuxA;
const adc16_hardware_average_mode_t DEMO_ADC16_hardwareAverageMode = kADC16_HardwareAverageCount32;

void DEMO_ADC16_init(void)
{
    /* Enable interrupt ADC0_IRQn request in the NVIC */
    EnableIRQ(ADC0_IRQn);
    /* Initialize ADC16 converter */
    ADC16_Init(DEMO_ADC16_PERIPHERAL, &DEMO_ADC16_config);
    /* Make sure, that software trigger is used */
    ADC16_EnableHardwareTrigger(DEMO_ADC16_PERIPHERAL, false);
    /* Configure hardware average mode */
    ADC16_SetHardwareAverage(DEMO_ADC16_PERIPHERAL, DEMO_ADC16_hardwareAverageMode);
    /* Configure channel multiplexing mode */
    ADC16_SetChannelMuxMode(DEMO_ADC16_PERIPHERAL, DEMO_ADC16_muxMode);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
    /* Initialize components */
    DEMO_LPTMR_init();
}

void BOARD_InitADCPeripheral(void)
{
    /* Initialize components */
    DEMO_ADC16_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
    BOARD_InitPeripherals();
}
