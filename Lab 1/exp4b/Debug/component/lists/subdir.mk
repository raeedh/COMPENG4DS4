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
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DPRINTF_ADVANCED_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_BAREMETAL -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\drivers" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\accel" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\utilities" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\device" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\component\uart" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\component\lists" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\CMSIS" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\board" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\source" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\drivers" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\accel" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\utilities" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\device" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\component\uart" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\component\lists" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\CMSIS" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\board" -I"C:\Users\pintoa9\Documents\COMPENG4DS4\lab 1\exp4b\frdmk66f\demo_apps\bubble_peripheral" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-lists

clean-component-2f-lists:
	-$(RM) ./component/lists/fsl_component_generic_list.d ./component/lists/fsl_component_generic_list.o

.PHONY: clean-component-2f-lists

