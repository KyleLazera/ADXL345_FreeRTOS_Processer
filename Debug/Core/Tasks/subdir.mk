################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Tasks/DataProcessing.c \
../Core/Tasks/ReadSPIData.c \
../Core/Tasks/UART_Gatekeeper.c 

OBJS += \
./Core/Tasks/DataProcessing.o \
./Core/Tasks/ReadSPIData.o \
./Core/Tasks/UART_Gatekeeper.o 

C_DEPS += \
./Core/Tasks/DataProcessing.d \
./Core/Tasks/ReadSPIData.d \
./Core/Tasks/UART_Gatekeeper.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Tasks/%.o Core/Tasks/%.su Core/Tasks/%.cyclo: ../Core/Tasks/%.c Core/Tasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Drivers/stm32f4xx_periphDrivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Tasks

clean-Core-2f-Tasks:
	-$(RM) ./Core/Tasks/DataProcessing.cyclo ./Core/Tasks/DataProcessing.d ./Core/Tasks/DataProcessing.o ./Core/Tasks/DataProcessing.su ./Core/Tasks/ReadSPIData.cyclo ./Core/Tasks/ReadSPIData.d ./Core/Tasks/ReadSPIData.o ./Core/Tasks/ReadSPIData.su ./Core/Tasks/UART_Gatekeeper.cyclo ./Core/Tasks/UART_Gatekeeper.d ./Core/Tasks/UART_Gatekeeper.o ./Core/Tasks/UART_Gatekeeper.su

.PHONY: clean-Core-2f-Tasks

