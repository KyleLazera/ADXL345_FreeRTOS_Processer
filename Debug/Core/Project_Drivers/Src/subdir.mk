################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Project_Drivers/Src/DataHandles.c \
../Core/Project_Drivers/Src/FIFO_Buffer.c \
../Core/Project_Drivers/Src/ProgramInit.c \
../Core/Project_Drivers/Src/TIM3_Driver.c \
../Core/Project_Drivers/Src/bme280.c 

OBJS += \
./Core/Project_Drivers/Src/DataHandles.o \
./Core/Project_Drivers/Src/FIFO_Buffer.o \
./Core/Project_Drivers/Src/ProgramInit.o \
./Core/Project_Drivers/Src/TIM3_Driver.o \
./Core/Project_Drivers/Src/bme280.o 

C_DEPS += \
./Core/Project_Drivers/Src/DataHandles.d \
./Core/Project_Drivers/Src/FIFO_Buffer.d \
./Core/Project_Drivers/Src/ProgramInit.d \
./Core/Project_Drivers/Src/TIM3_Driver.d \
./Core/Project_Drivers/Src/bme280.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Project_Drivers/Src/%.o Core/Project_Drivers/Src/%.su Core/Project_Drivers/Src/%.cyclo: ../Core/Project_Drivers/Src/%.c Core/Project_Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Drivers/stm32f4xx_periphDrivers/Inc" -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Tasks/Inc" -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Core/Inc" -I"C:/Users/klaze/STM32Cube_Projects/DataProcessing_ADXL/Core/Project_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Project_Drivers-2f-Src

clean-Core-2f-Project_Drivers-2f-Src:
	-$(RM) ./Core/Project_Drivers/Src/DataHandles.cyclo ./Core/Project_Drivers/Src/DataHandles.d ./Core/Project_Drivers/Src/DataHandles.o ./Core/Project_Drivers/Src/DataHandles.su ./Core/Project_Drivers/Src/FIFO_Buffer.cyclo ./Core/Project_Drivers/Src/FIFO_Buffer.d ./Core/Project_Drivers/Src/FIFO_Buffer.o ./Core/Project_Drivers/Src/FIFO_Buffer.su ./Core/Project_Drivers/Src/ProgramInit.cyclo ./Core/Project_Drivers/Src/ProgramInit.d ./Core/Project_Drivers/Src/ProgramInit.o ./Core/Project_Drivers/Src/ProgramInit.su ./Core/Project_Drivers/Src/TIM3_Driver.cyclo ./Core/Project_Drivers/Src/TIM3_Driver.d ./Core/Project_Drivers/Src/TIM3_Driver.o ./Core/Project_Drivers/Src/TIM3_Driver.su ./Core/Project_Drivers/Src/bme280.cyclo ./Core/Project_Drivers/Src/bme280.d ./Core/Project_Drivers/Src/bme280.o ./Core/Project_Drivers/Src/bme280.su

.PHONY: clean-Core-2f-Project_Drivers-2f-Src

