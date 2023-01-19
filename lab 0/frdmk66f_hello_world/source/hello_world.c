/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MEM_LOC_CHAR(x)				*((char*)x)
#define MEM_LOC_SHORT(x)			*((short*)x)
#define MEM_LOC_INT(x)				*((int*)x)
#define LOC1			MEM_LOC_CHAR(0x20001000)
#define LOC2			MEM_LOC_INT(0x20001001)
#define LOC3			MEM_LOC_SHORT(0x20001005)
#define LOC4			MEM_LOC_INT(0x20001007)

typedef struct __attribute__((__packed__)){
	int location_1;
	char location_2;
	int location_3;
} ARBITRARY_MODULE;

#define MODULE ((ARBITRARY_MODULE*)0x20001000)

typedef struct
{
	char x2;
	int x1;
} struct1;
typedef struct
{
	short x2;
	int x1;
} struct2;
typedef struct
{
	int x1;
	short x2;
} struct3;
typedef struct
{
	struct inner_struct
	{
		char x1;
		short x2;
		int x3;
	} inner_struct_1;
	int x1;
} struct4;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void testFunction();
void testFunctionB();
void problem1();
void testFunction2();

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
	char ch;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	PRINTF("hello world.\r\n");

	//testFunction();
	//	testFunctionB();
	//	problem1();
	//	testFunction2();

	printf("Struct 1 size: %d\n", sizeof(struct1));
	printf("Struct 2 size: %d\n", sizeof(struct2));
	printf("Struct 3 size: %d\n", sizeof(struct3));
	printf("Struct 4 size: %d\n", sizeof(struct4));

	while (1)
	{
		ch = GETCHAR();
		PUTCHAR(ch);
	}
}

//
//void testFunction(){
//	int x = 0;
//	int *ptr = &x;
//	int *ptr_location = 0x20001000; //Random location in the memory
//
//	*ptr = 10;
//	*ptr_location = 11;
//}
//
//void testFunctionB() {
//	int *ptr_location = (int*)0x20001000;
//	*ptr_location = 11;
//
//	ARBITRARY_LOCATION = 12;
//	int x = ARBITRARY_LOCATION;
//}
//
//void problem1() {
//	LOC1 = 0xAC;
//	LOC2 = 0xAABBCCDD;
//	LOC3 = 0xABCD;
//	LOC4 = 0xAABBCCDD;
//}

void testFunction2() {
	MODULE->location_1 = 0xAAAAAAAA;
	MODULE->location_2 = 0xBB;
	MODULE->location_3 = 0xCCCCCCCC;
}
