################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos_kernel/croutine.c \
../freertos/freertos_kernel/event_groups.c \
../freertos/freertos_kernel/list.c \
../freertos/freertos_kernel/queue.c \
../freertos/freertos_kernel/stream_buffer.c \
../freertos/freertos_kernel/tasks.c \
../freertos/freertos_kernel/timers.c 

C_DEPS += \
./freertos/freertos_kernel/croutine.d \
./freertos/freertos_kernel/event_groups.d \
./freertos/freertos_kernel/list.d \
./freertos/freertos_kernel/queue.d \
./freertos/freertos_kernel/stream_buffer.d \
./freertos/freertos_kernel/tasks.d \
./freertos/freertos_kernel/timers.d 

OBJS += \
./freertos/freertos_kernel/croutine.o \
./freertos/freertos_kernel/event_groups.o \
./freertos/freertos_kernel/list.o \
./freertos/freertos_kernel/queue.o \
./freertos/freertos_kernel/stream_buffer.o \
./freertos/freertos_kernel/tasks.o \
./freertos/freertos_kernel/timers.o 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos_kernel/%.o: ../freertos/freertos_kernel/%.c freertos/freertos_kernel/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFRDM_K66F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\drivers" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\device" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\utilities" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\component\uart" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\component\serial_manager" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\component\lists" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\CMSIS" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\freertos\freertos_kernel\include" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\board" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\source" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\accel" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\drivers" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\device" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\utilities" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\component\uart" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\component\serial_manager" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\component\lists" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\CMSIS" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\freertos\freertos_kernel\include" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\board" -I"C:\Users\hassam41.ECE\Documents\COMPENG4DS4\Project 1\frdmk66f_freertos_hello_test\source" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-freertos-2f-freertos_kernel

clean-freertos-2f-freertos_kernel:
	-$(RM) ./freertos/freertos_kernel/croutine.d ./freertos/freertos_kernel/croutine.o ./freertos/freertos_kernel/event_groups.d ./freertos/freertos_kernel/event_groups.o ./freertos/freertos_kernel/list.d ./freertos/freertos_kernel/list.o ./freertos/freertos_kernel/queue.d ./freertos/freertos_kernel/queue.o ./freertos/freertos_kernel/stream_buffer.d ./freertos/freertos_kernel/stream_buffer.o ./freertos/freertos_kernel/tasks.d ./freertos/freertos_kernel/tasks.o ./freertos/freertos_kernel/timers.d ./freertos/freertos_kernel/timers.o

.PHONY: clean-freertos-2f-freertos_kernel

