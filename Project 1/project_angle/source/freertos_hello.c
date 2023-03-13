#include "FreeRTOS.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "clock_config.h"
#include "board.h"

#include "Motor_Control_Component.h"
#include "RC_Receiver_Component.h"
#include "Terminal_Component.h"
#include "LED_Component.h"
//#include "Accelerometer_Component.h"

int main(void)
{
    /* Init board hardware. */
    BOARD_InitBootClocks();
//

    setupRCReceiverComponent();

    setupMotorComponent();

//    setupTerminalComponent();
    //setupLEDComponent();
//    setupAccelerometerComponent();

     BaseType_t status;
     /* Init board hardware. */
     BOARD_InitDebugConsole();

     SemaphoreHandle_t hold_sem;
     hold_sem = xSemaphoreCreateBinary(); //Producer semaphore

     status = xTaskCreate(rcTask, "rcTask", 200, (void*)hold_sem, 2, NULL);
     if (status != pdPASS)
     {
     PRINTF("Task creation failed!.\r\n");
     while (1);
     }


     int usr_input;
     printf("enter 1 to start RC control\n");

     scanf("%d",&usr_input);

     if(usr_input == 1){
    	 xSemaphoreGive(hold_sem);
     }

    vTaskStartScheduler();

    while(1)
    {}
}
