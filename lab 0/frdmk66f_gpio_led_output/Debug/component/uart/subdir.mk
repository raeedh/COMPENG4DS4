################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_uart.c 

C_DEPS += \
./component/uart/fsl_adapter_uart.d 

OBJS += \
./component/uart/fsl_adapter_uart.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_gpio_led_output\source" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_gpio_led_output\utilities" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_gpio_led_output\drivers" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_gpio_led_output\device" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_gpio_led_output\component\uart" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_gpio_led_output\component\lists" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_gpio_led_output\CMSIS" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_gpio_led_output\board" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_gpio_led_output\frdmk66f\driver_examples\gpio\led_output" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/fsl_adapter_uart.d ./component/uart/fsl_adapter_uart.o

.PHONY: clean-component-2f-uart

