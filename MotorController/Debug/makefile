################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MotorController.axf

# Tool invocations
MotorController.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/Users/vartan/LPCXpresso/workspace/CMSISv2p00_LPC11Uxx/Debug" -Xlinker -Map="MotorController.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "MotorController_Debug.ld" -o "MotorController.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) MotorController.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size MotorController.axf; arm-none-eabi-objcopy -O ihex MotorController.axf MotorController.hex ; arm-none-eabi-objcopy -O binary MotorController.axf MotorController.bin ; checksum -p LPC11U24_401 -d MotorController.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
