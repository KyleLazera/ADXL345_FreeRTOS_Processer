################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tasks/Src/CLI_Interface.c \
../Tasks/Src/DataProcessing.c \
../Tasks/Src/PulseWidthMod_Output.c \
../Tasks/Src/ReadSPIData.c \
../Tasks/Src/UART_Gatekeeper.c 

OBJS += \
./Tasks/Src/CLI_Interface.o \
./Tasks/Src/DataProcessing.o \
./Tasks/Src/PulseWidthMod_Output.o \
./Tasks/Src/ReadSPIData.o \
./Tasks/Src/UART_Gatekeeper.o 

C_DEPS += \
./Tasks/Src/CLI_Interface.d \
./Tasks/Src/DataProcessing.d \
./Tasks/Src/PulseWidthMod_Output.d \
./Tasks/Src/ReadSPIData.d \
./Tasks/Src/UART_Gatekeeper.d 


# Each subdirectory must supply rules for building sources it contributes
Tasks/Src/%.o Tasks/Src/%.su Tasks/Src/%.cyclo: ../Tasks/Src/%.c Tasks/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Drivers/stm32f4xx_periphDrivers/Inc" -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Tasks/Inc" -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Tasks-2f-Src

clean-Tasks-2f-Src:
	-$(RM) ./Tasks/Src/CLI_Interface.cyclo ./Tasks/Src/CLI_Interface.d ./Tasks/Src/CLI_Interface.o ./Tasks/Src/CLI_Interface.su ./Tasks/Src/DataProcessing.cyclo ./Tasks/Src/DataProcessing.d ./Tasks/Src/DataProcessing.o ./Tasks/Src/DataProcessing.su ./Tasks/Src/PulseWidthMod_Output.cyclo ./Tasks/Src/PulseWidthMod_Output.d ./Tasks/Src/PulseWidthMod_Output.o ./Tasks/Src/PulseWidthMod_Output.su ./Tasks/Src/ReadSPIData.cyclo ./Tasks/Src/ReadSPIData.d ./Tasks/Src/ReadSPIData.o ./Tasks/Src/ReadSPIData.su ./Tasks/Src/UART_Gatekeeper.cyclo ./Tasks/Src/UART_Gatekeeper.d ./Tasks/Src/UART_Gatekeeper.o ./Tasks/Src/UART_Gatekeeper.su

.PHONY: clean-Tasks-2f-Src

