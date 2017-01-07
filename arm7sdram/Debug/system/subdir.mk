################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/audio_test.c \
../system/rtc_test.c 

OBJS += \
./system/audio_test.o \
./system/rtc_test.o 

C_DEPS += \
./system/audio_test.d \
./system/rtc_test.d 


# Each subdirectory must supply rules for building sources it contributes
system/%.o: ../system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=arm7tdmi -marm -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__WB_EVB__ -I"D:\Users\kohill\workspace\arm7sdram\system\Inc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emsrc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_Config" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_header" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


