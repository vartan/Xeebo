################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MotorDriver.c \
../cr_startup_lpc11u.c \
../main.c \
../timers.c 

OBJS += \
./MotorDriver.o \
./cr_startup_lpc11u.o \
./main.o \
./timers.o 

C_DEPS += \
./MotorDriver.d \
./cr_startup_lpc11u.d \
./main.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"/Users/vartan/LPCXpresso/workspace/CMSISv2p00_LPC11Uxx/inc" -I"/Users/vartan/LPCXpresso/workspace/CMSISv2p00_LPC11Uxx/inc" -I"/Users/vartan/LPCXpresso/workspace/BB-LPC11U24_Drivers_lib/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cr_startup_lpc11u.o: ../cr_startup_lpc11u.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"/Users/vartan/LPCXpresso/workspace/CMSISv2p00_LPC11Uxx/inc" -I"/Users/vartan/LPCXpresso/workspace/BB-LPC11U24_Drivers_lib/inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"cr_startup_lpc11u.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


