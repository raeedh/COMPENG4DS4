################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_MK66F18.c 

C_DEPS += \
./device/system_MK66F18.d 

OBJS += \
./device/system_MK66F18.o 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DCPU_MK66FN2M0VMD18_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 0\experiment2\source" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 0\experiment2\utilities" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 0\experiment2\drivers" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 0\experiment2\device" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 0\experiment2\component\uart" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 0\experiment2\component\lists" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 0\experiment2\CMSIS" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 0\experiment2\board" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-device

clean-device:
	-$(RM) ./device/system_MK66F18.d ./device/system_MK66F18.o

.PHONY: clean-device
