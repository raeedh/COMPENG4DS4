#ifndef MOTOR_CONTROL_COMPONENT_H
#define MOTOR_CONTROL_COMPONENT_H

#include "pin_mux.h"
#include "fsl_port.h"
#include "fsl_ftm.h"
#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Terminal_Component.h"


#include "fsl_device_registers.h"
#include "clock_config.h"


#define FTM_MOTOR FTM0
#define FTM_CHANNEL_DC_MOTOR kFTM_Chnl_0

#define FTM_CHANNEL_SERVO_MOTOR kFTM_Chnl_3     //Define servo PWM channel

extern QueueHandle_t motor_queue, angle_queue;

void setupMotorComponent();
void setupPWM();
void setupMotorPins();

void updatePWM_dutyCycle(ftm_chnl_t channel, float dutyCycle);

void motorTask(void* pvParameters);
void positionTask(void* pvParameters);


#endif /* MOTOR_CONTROL_COMPONENT_H */
