################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/stm32f4xx_periphDrivers/Src/stm32f401_gpio.c \
../Drivers/stm32f4xx_periphDrivers/Src/stm32f401_i2c.c \
../Drivers/stm32f4xx_periphDrivers/Src/stm32f401_rcc.c \
../Drivers/stm32f4xx_periphDrivers/Src/stm32f401_spi.c \
../Drivers/stm32f4xx_periphDrivers/Src/stm32f401_uart.c 

OBJS += \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_gpio.o \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_i2c.o \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_rcc.o \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_spi.o \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_uart.o 

C_DEPS += \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_gpio.d \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_i2c.d \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_rcc.d \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_spi.d \
./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/stm32f4xx_periphDrivers/Src/%.o Drivers/stm32f4xx_periphDrivers/Src/%.su Drivers/stm32f4xx_periphDrivers/Src/%.cyclo: ../Drivers/stm32f4xx_periphDrivers/Src/%.c Drivers/stm32f4xx_periphDrivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Drivers/stm32f4xx_periphDrivers/Inc" -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Tasks/Inc" -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-stm32f4xx_periphDrivers-2f-Src

clean-Drivers-2f-stm32f4xx_periphDrivers-2f-Src:
	-$(RM) ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_gpio.cyclo ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_gpio.d ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_gpio.o ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_gpio.su ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_i2c.cyclo ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_i2c.d ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_i2c.o ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_i2c.su ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_rcc.cyclo ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_rcc.d ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_rcc.o ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_rcc.su ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_spi.cyclo ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_spi.d ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_spi.o ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_spi.su ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_uart.cyclo ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_uart.d ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_uart.o ./Drivers/stm32f4xx_periphDrivers/Src/stm32f401_uart.su

.PHONY: clean-Drivers-2f-stm32f4xx_periphDrivers-2f-Src

