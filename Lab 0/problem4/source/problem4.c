/*
 * problem4.c
 *
 *  Created on: Jan. 19, 2023
 *      Author: guoj69
 */
#include "problem4.h"

void initPin(GPIO_Struct *port, uint32_t pin) {
	writePin(port, pin, 1);
	port->GPIO_PDDR |= (1UL << pin);
}

void togglePin(GPIO_Struct *port, uint32_t mask) {
	port->GPIO_PDOR ^= (mask);
}

void writePin(GPIO_Struct *port, uint32_t pin, uint8_t output) {
	if (output == 0U) {
		port->GPIO_PDOR |= (1UL << pin);
	} else {
		port->GPIO_PDOR &= ~(1UL << pin);
	}
}
