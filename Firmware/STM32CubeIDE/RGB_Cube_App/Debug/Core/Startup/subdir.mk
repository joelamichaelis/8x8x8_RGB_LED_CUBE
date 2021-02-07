################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/asdf_startup_stm32f103c8tx.s 

S_UPPER_SRCS += \
../Core/Startup/startup_stm32f103xb.S 

OBJS += \
./Core/Startup/asdf_startup_stm32f103c8tx.o \
./Core/Startup/startup_stm32f103xb.o 

S_DEPS += \
./Core/Startup/asdf_startup_stm32f103c8tx.d 

S_UPPER_DEPS += \
./Core/Startup/startup_stm32f103xb.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/asdf_startup_stm32f103c8tx.o: ../Core/Startup/asdf_startup_stm32f103c8tx.s
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Core/Startup/asdf_startup_stm32f103c8tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Core/Startup/startup_stm32f103xb.o: ../Core/Startup/startup_stm32f103xb.S
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32f103xb.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

