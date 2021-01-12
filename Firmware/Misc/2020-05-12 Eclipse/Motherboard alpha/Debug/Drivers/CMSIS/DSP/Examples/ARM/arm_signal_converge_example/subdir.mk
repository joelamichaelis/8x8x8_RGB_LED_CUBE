################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/arm_signal_converge_data.c \
../Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/arm_signal_converge_example_f32.c \
../Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/math_helper.c 

OBJS += \
./Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/arm_signal_converge_data.o \
./Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/arm_signal_converge_example_f32.o \
./Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/math_helper.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/arm_signal_converge_data.d \
./Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/arm_signal_converge_example_f32.d \
./Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/math_helper.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/%.o: ../Drivers/CMSIS/DSP/Examples/ARM/arm_signal_converge_example/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F103xB -I"C:\Users\jmichael\OneDrive - Itron\Documents\8x8x8_RGB_LED_CUBE_MOTHERBOARD_FW\2020-05-12 Eclipse\Motherboard\Drivers\CMSIS\Device\ST\STM32F1xx\Include" -I"C:\Users\jmichael\OneDrive - Itron\Documents\8x8x8_RGB_LED_CUBE_MOTHERBOARD_FW\2020-05-12 Eclipse\Motherboard\Drivers\CMSIS\Include" -I"C:\Users\jmichael\OneDrive - Itron\Documents\8x8x8_RGB_LED_CUBE_MOTHERBOARD_FW\2020-05-12 Eclipse\Motherboard\Drivers\STM32F1xx_HAL_Driver\Inc" -I"C:\Users\jmichael\OneDrive - Itron\Documents\8x8x8_RGB_LED_CUBE_MOTHERBOARD_FW\2020-05-12 Eclipse\Motherboard\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


