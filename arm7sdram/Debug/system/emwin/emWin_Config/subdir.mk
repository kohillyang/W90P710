################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/emwin/emWin_Config/GUIConf.c \
../system/emwin/emWin_Config/GUIDRV_Template.c \
../system/emwin/emWin_Config/GUI_X.c \
../system/emwin/emWin_Config/LCDConf.c \
../system/emwin/emWin_Config/SIMConf.c 

OBJS += \
./system/emwin/emWin_Config/GUIConf.o \
./system/emwin/emWin_Config/GUIDRV_Template.o \
./system/emwin/emWin_Config/GUI_X.o \
./system/emwin/emWin_Config/LCDConf.o \
./system/emwin/emWin_Config/SIMConf.o 

C_DEPS += \
./system/emwin/emWin_Config/GUIConf.d \
./system/emwin/emWin_Config/GUIDRV_Template.d \
./system/emwin/emWin_Config/GUI_X.d \
./system/emwin/emWin_Config/LCDConf.d \
./system/emwin/emWin_Config/SIMConf.d 


# Each subdirectory must supply rules for building sources it contributes
system/emwin/emWin_Config/%.o: ../system/emwin/emWin_Config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=arm7tdmi -marm -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__WB_EVB__ -I"D:\Users\kohill\workspace\arm7sdram\system\Inc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emsrc" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_Config" -I"D:\Users\kohill\workspace\arm7sdram\system\emwin\emWin_header" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


