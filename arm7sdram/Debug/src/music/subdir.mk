################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/music/HB_it.c \
../src/music/music.c 

OBJS += \
./src/music/HB_it.o \
./src/music/music.o 

C_DEPS += \
./src/music/HB_it.d \
./src/music/music.d 


# Each subdirectory must supply rules for building sources it contributes
src/music/%.o: ../src/music/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=arm7tdmi -marm -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__WB_EVB__ -I"D:\Users\kohill\workspace\arm7sdram\system\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


