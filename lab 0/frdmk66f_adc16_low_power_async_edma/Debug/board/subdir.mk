################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DCPU_MK66FN2M0VMD18_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma\source" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma\utilities" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma\drivers" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma\device" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma\component\uart" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma\component\lists" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma\CMSIS" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma\board" -I"C:\Users\guoj69\Desktop\lab 0\frdmk66f_adc16_low_power_async_edma\frdmk66f\demo_apps\adc16_low_power_async_edma" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

