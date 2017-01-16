################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/_syscall.c \
../system/startup_gcc.c 

OBJS += \
./system/_syscall.o \
./system/startup_gcc.o 

C_DEPS += \
./system/_syscall.d \
./system/startup_gcc.d 


# Each subdirectory must supply rules for building sources it contributes
system/%.o: ../system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:\Program Files (Green)\Texas Instruments\lib\inc" -I"D:\Program Files (Green)\Texas Instruments\lib" -I"I:\ArmWorks\My_OS_3\inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


