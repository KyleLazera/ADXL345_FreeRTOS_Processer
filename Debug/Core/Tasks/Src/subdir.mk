################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Tasks/Src/DataProcessing.c \
../Core/Tasks/Src/ReadSPIData.c \
../Core/Tasks/Src/UART_Gatekeeper.c 

OBJS += \
./Core/Tasks/Src/DataProcessing.o \
./Core/Tasks/Src/ReadSPIData.o \
./Core/Tasks/Src/UART_Gatekeeper.o 

C_DEPS += \
./Core/Tasks/Src/DataProcessing.d \
./Core/Tasks/Src/ReadSPIData.d \
./Core/Tasks/Src/UART_Gatekeeper.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Tasks/Src/%.o Core/Tasks/Src/%.su Core/Tasks/Src/%.cyclo: ../Core/Tasks/Src/%.c Core/Tasks/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Drivers/stm32f4xx_periphDrivers/Inc" -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Core/Tasks/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Tasks-2f-Src

clean-Core-2f-Tasks-2f-Src:
	-$(RM) ./Core/Tasks/Src/DataProcessing.cyclo ./Core/Tasks/Src/DataProcessing.d ./Core/Tasks/Src/DataProcessing.o ./Core/Tasks/Src/DataProcessing.su ./Core/Tasks/Src/ReadSPIData.cyclo ./Core/Tasks/Src/ReadSPIData.d ./Core/Tasks/Src/ReadSPIData.o ./Core/Tasks/Src/ReadSPIData.su ./Core/Tasks/Src/UART_Gatekeeper.cyclo ./Core/Tasks/Src/UART_Gatekeeper.d ./Core/Tasks/Src/UART_Gatekeeper.o ./Core/Tasks/Src/UART_Gatekeeper.su

.PHONY: clean-Core-2f-Tasks-2f-Src

