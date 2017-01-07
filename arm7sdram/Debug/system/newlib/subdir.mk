################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/newlib/_exit.c \
../system/newlib/_sbrk.c \
../system/newlib/_startup.c \
../system/newlib/_syscalls.c \
../system/newlib/assert.c 

OBJS += \
./system/newlib/_exit.o \
./system/newlib/_sbrk.o \
./system/newlib/_startup.o \
./system/newlib/_syscalls.o \
./system/newlib/assert.o 

C_DEPS += \
./system/newlib/_exit.d \
./system/newlib/_sbrk.d \
./system/newlib/_startup.d \
./system/newlib/_syscalls.d \
./system/newlib/assert.d 


# Each subdirectory must supply rules for building sources it contributes
system/newlib/%.o: ../system/newlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=arm7tdmi -marm -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__WB_EVB__ -I"D:\Users\kohill\workspace\arm7sdram\system\Inc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emsrc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_Config" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_header" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


