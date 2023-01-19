################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/adc16_low_power_async_edma_peripheral.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/adc16_low_power_async_edma_peripheral.d \
./source/semihost_hardfault.d 

OBJS += \
./source/adc16_low_power_async_edma_peripheral.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MK66FN2M0VMD18 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DCPU_MK66FN2M0VMD18_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\source" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\utilities" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\drivers" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\device" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\component\uart" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\component\lists" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\CMSIS" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\board" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma_peripheral\frdmk66f\demo_apps\adc16_low_power_async_edma_peripheral" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/adc16_low_power_async_edma_peripheral.d ./source/adc16_low_power_async_edma_peripheral.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

