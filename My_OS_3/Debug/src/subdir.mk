################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/getSp.c \
../src/led.c \
../src/systick.c \
../src/task.c \
../src/task_add.c \
../src/task_judege.c 

S_UPPER_SRCS += \
../src/interrupt_timer.S \
../src/resetHandler.S 

OBJS += \
./src/getSp.o \
./src/interrupt_timer.o \
./src/led.o \
./src/resetHandler.o \
./src/systick.o \
./src/task.o \
./src/task_add.o \
./src/task_judege.o 

S_UPPER_DEPS += \
./src/interrupt_timer.d \
./src/resetHandler.d 

C_DEPS += \
./src/getSp.d \
./src/led.d \
./src/systick.d \
./src/task.d \
./src/task_add.d \
./src/task_judege.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:\Program Files (Green)\Texas Instruments\lib\inc" -I"D:\Program Files (Green)\Texas Instruments\lib" -I"I:\ArmWorks\My_OS_3\inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -I"D:\Program Files (Green)\Texas Instruments\lib\inc" -I"D:\Program Files (Green)\Texas Instruments\lib" -I"I:\ArmWorks\My_OS_3\inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


