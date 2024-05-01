# Summary

This project implements a real-time processing system designed to enhance the testing of the 'stm32f4xx_peripheral_driver' series project in a more robust and practical manner. The system utilizes FreeRTOS to perform concurrent tasks, 
including reading sensor data from an accelerometer and a temperature/pressure sensor. The raw sensor data is then processed using a digital Finite Impulse Response (FIR) filter. The processed data is then output through a series of LEDs 
for visual indication and via serial communication for further analysis.

By leveraging FreeRTOS, the system demonstrates simultaneous execution of tasks while evaluating the performance of the peripheral drivers. This setup provides a comprehensive testbed for assessing the functionality and reliability of 
the peripheral drivers under real-time processing scenarios.
