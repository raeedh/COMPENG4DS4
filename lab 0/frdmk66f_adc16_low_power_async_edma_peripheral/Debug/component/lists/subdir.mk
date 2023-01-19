################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/lists/fsl_component_generic_list.c 

C_DEPS += \
./component/lists/fsl_component_generic_list.d 

OBJS += \
./component/lists/fsl_component_generic_list.o 


# Each subdirectory must supply rules for building sources it contributes
component/lists/%.o: ../component/lists/%.c component/lists/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MK66FN2M0VMD18 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DCPU_MK66FN2M0VMD18_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\source" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\utilities" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\drivers" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\device" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\component\uart" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\component\lists" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\CMSIS" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\board" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\frdmk66f\demo_apps\adc16_low_power_async_edma_peripheral" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-lists

clean-component-2f-lists:
	-$(RM) ./component/lists/fsl_component_generic_list.d ./component/lists/fsl_component_generic_list.o

.PHONY: clean-component-2f-lists

