################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/emwin/emsrc/FramewinDLG.c \
../system/emwin/emsrc/bmp_calculator.c \
../system/emwin/emsrc/bmp_calendar.c \
../system/emwin/emsrc/bmp_music.c \
../system/emwin/emsrc/mainMenuDLG.c 

OBJS += \
./system/emwin/emsrc/FramewinDLG.o \
./system/emwin/emsrc/bmp_calculator.o \
./system/emwin/emsrc/bmp_calendar.o \
./system/emwin/emsrc/bmp_music.o \
./system/emwin/emsrc/mainMenuDLG.o 

C_DEPS += \
./system/emwin/emsrc/FramewinDLG.d \
./system/emwin/emsrc/bmp_calculator.d \
./system/emwin/emsrc/bmp_calendar.d \
./system/emwin/emsrc/bmp_music.d \
./system/emwin/emsrc/mainMenuDLG.d 


# Each subdirectory must supply rules for building sources it contributes
system/emwin/emsrc/%.o: ../system/emwin/emsrc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=arm7tdmi -marm -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__WB_EVB__ -I"D:\Users\kohill\workspace\arm7sdram\system\Inc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emsrc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_Config" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_header" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


