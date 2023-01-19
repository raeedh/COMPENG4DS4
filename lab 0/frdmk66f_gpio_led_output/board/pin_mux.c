/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 ,2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MK66FN2M0xxx18
package_id: MK66FN2M0VMD18
mcu_data: ksdk2_0
processor_version: 9.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
	BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: E10, peripheral: UART0, signal: RX, pin_signal: TSI0_CH9/PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0}
  - {pin_num: E9, peripheral: UART0, signal: TX, pin_signal: TSI0_CH10/PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1}
  - {pin_num: D7, peripheral: GPIOC, signal: 'GPIO, 9', pin_signal: ADC1_SE5b/CMP0_IN3/PTC9/FTM3_CH5/I2S0_RX_BCLK/FB_AD6/SDRAM_A14/FTM2_FLT0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
	/* Port B Clock Gate Control: Clock enabled */
	//    CLOCK_EnableClock(kCLOCK_PortB);
	//    /* Port C Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortC);
	/* Port D Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortD);

	//    CLOCK_EnableClock(kCLOCK_PortD);

	//    CLOCK_EnableClock(kCLOCK_PortD);

	//    /* PORTB16 (pin E10) is configured as UART0_RX */
	//    PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt3);
	//
	//    /* PORTB17 (pin E9) is configured as UART0_TX */
	//    PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt3);
	//
	//    /* PORTC9 (pin D7) is configured as PTC9 */
	//    PORT_SetPinMux(PORTC, 9U, kPORT_MuxAsGpio);

	/* PORTC8 is configured as PTC8 */
	PORT_SetPinMux(PORTC, 8U, kPORT_MuxAsGpio);

	/* PORTC9 is configured as PTC9 */
	PORT_SetPinMux(PORTC, 9U, kPORT_MuxAsGpio);

	/* PORTD1 is configured as PTD1 */
	PORT_SetPinMux(PORTD, 1U, kPORT_MuxAsGpio);

	//    SIM->SOPT5 = ((SIM->SOPT5 &
	//                   /* Mask bits to zero which are setting */
	//                   (~(SIM_SOPT5_UART0TXSRC_MASK)))
	//
	//                  /* UART 0 transmit data source select: UART0_TX pin. */
	//                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
