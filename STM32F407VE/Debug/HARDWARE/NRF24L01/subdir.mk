################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/NRF24L01/24l01.c 

OBJS += \
./HARDWARE/NRF24L01/24l01.o 

C_DEPS += \
./HARDWARE/NRF24L01/24l01.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/NRF24L01/%.o: ../HARDWARE/NRF24L01/%.c HARDWARE/NRF24L01/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32CubeIDE/STM32F407VE/HARDWARE/sys" -I"D:/STM32CubeIDE/STM32F407VE/HARDWARE/CAN" -I"D:/STM32CubeIDE/STM32F407VE/HARDWARE/NRF24L01" -I"D:/STM32CubeIDE/STM32F407VE/HARDWARE/SPI" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

