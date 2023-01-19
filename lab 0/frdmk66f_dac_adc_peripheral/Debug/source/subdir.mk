################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/dac_adc_peripheral.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/dac_adc_peripheral.d \
./source/semihost_hardfault.d 

OBJS += \
./source/dac_adc_peripheral.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DPRINTF_FLOAT_ENABLE=1 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DCPU_MK66FN2M0VMD18_cm4 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_dac_adc_peripheral\source" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_dac_adc_peripheral\utilities" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_dac_adc_peripheral\drivers" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_dac_adc_peripheral\device" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_dac_adc_peripheral\component\uart" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_dac_adc_peripheral\component\lists" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_dac_adc_peripheral\CMSIS" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_dac_adc_peripheral\board" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_dac_adc_peripheral\frdmk66f\demo_apps\dac_adc_peripheral" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/dac_adc_peripheral.d ./source/dac_adc_peripheral.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

