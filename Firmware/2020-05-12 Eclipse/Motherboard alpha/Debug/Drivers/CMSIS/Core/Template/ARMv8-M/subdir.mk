################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Core/Template/ARMv8-M/main_s.c \
../Drivers/CMSIS/Core/Template/ARMv8-M/tz_context.c 

OBJS += \
./Drivers/CMSIS/Core/Template/ARMv8-M/main_s.o \
./Drivers/CMSIS/Core/Template/ARMv8-M/tz_context.o 

C_DEPS += \
./Drivers/CMSIS/Core/Template/ARMv8-M/main_s.d \
./Drivers/CMSIS/Core/Template/ARMv8-M/tz_context.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Core/Template/ARMv8-M/%.o: ../Drivers/CMSIS/Core/Template/ARMv8-M/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F103xB -I"C:\Users\jmichael\OneDrive - Itron\Documents\8x8x8_RGB_LED_CUBE_MOTHERBOARD_FW\2020-05-12 Eclipse\Motherboard\Drivers\CMSIS\Device\ST\STM32F1xx\Include" -I"C:\Users\jmichael\OneDrive - Itron\Documents\8x8x8_RGB_LED_CUBE_MOTHERBOARD_FW\2020-05-12 Eclipse\Motherboard\Drivers\CMSIS\Include" -I"C:\Users\jmichael\OneDrive - Itron\Documents\8x8x8_RGB_LED_CUBE_MOTHERBOARD_FW\2020-05-12 Eclipse\Motherboard\Drivers\STM32F1xx_HAL_Driver\Inc" -I"C:\Users\jmichael\OneDrive - Itron\Documents\8x8x8_RGB_LED_CUBE_MOTHERBOARD_FW\2020-05-12 Eclipse\Motherboard\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


