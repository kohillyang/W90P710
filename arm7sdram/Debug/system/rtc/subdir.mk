################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/rtc/mktime.c \
../system/rtc/rtc.c 

OBJS += \
./system/rtc/mktime.o \
./system/rtc/rtc.o 

C_DEPS += \
./system/rtc/mktime.d \
./system/rtc/rtc.d 


# Each subdirectory must supply rules for building sources it contributes
system/rtc/%.o: ../system/rtc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=arm7tdmi -marm -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__WB_EVB__ -I"D:\Users\kohill\workspace\arm7sdram\system\Inc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emsrc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_Config" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_header" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


