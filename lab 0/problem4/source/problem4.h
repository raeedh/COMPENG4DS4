#ifndef _problem4_
#define _problem4_

#include <stdint.h>

typedef struct {
	uint32_t GPIO_PDOR;
	uint32_t GPIO_PSOR;
	uint32_t GPIO_PCOR;
	uint32_t GPIO_PTOR;
	uint32_t GPIO_PDIR;
	uint32_t GPIO_PDDR;
} GPIO_Struct;

void initPin(GPIO_Struct *port, uint32_t pin);

void togglePin(GPIO_Struct *port, uint32_t mask);

void writePin(GPIO_Struct *port, uint32_t pin, uint8_t output);

#endif
