################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/rtc/subdir.mk
-include system/newlib/subdir.mk
-include system/emwin/emsrc/subdir.mk
-include system/emwin/emWin_Config/subdir.mk
-include system/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
arm7sdram.hex \

SECONDARY_LIST += \
arm7sdram.lst \

SECONDARY_SIZE += \
arm7sdram.siz \


# All Target
all: arm7sdram.elf secondary-outputs

# Tool invocations
arm7sdram.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=arm7tdmi -marm -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "D:\Users\kohill\workspace\arm7sdram\ldscript\libs.ld" -T "D:\Users\kohill\workspace\arm7sdram\ldscript\mem.ld" -T "D:\Users\kohill\workspace\arm7sdram\ldscript\sections.ld" -nostartfiles -Xlinker --gc-sections -L"D:\Users\kohill\workspace\arm7sdram\ldscript" -Wl,-Map,"arm7sdram.map" --specs=rdimon.specs -Wl,--start-group -lgcc -lc -lc -lm -lrdimon -Wl,--end-group -o "arm7sdram.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

arm7sdram.hex: arm7sdram.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "arm7sdram.elf"  "arm7sdram.hex"
	@echo 'Finished building: $@'
	@echo ' '

arm7sdram.lst: arm7sdram.elf
	@echo 'Invoking: Cross ARM GNU Create Listing'
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "arm7sdram.elf" > "arm7sdram.lst"
	@echo 'Finished building: $@'
	@echo ' '

arm7sdram.siz: arm7sdram.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "arm7sdram.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) arm7sdram.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
