# Summary

This project implements a real-time processing system designed to enhance the testing of the 'stm32f4xx_peripheral_driver' series project in a more robust and practical manner. The system utilizes FreeRTOS to perform concurrent tasks, 
including reading sensor data from an accelerometer and a temperature/pressure sensor. The raw sensor data is then processed using a digital Finite Impulse Response (FIR) filter. The processed data is then output through a series of LEDs 
for visual indication and via serial communication for further analysis.

By leveraging FreeRTOS, the system demonstrates simultaneous execution of tasks while evaluating the performance of the peripheral drivers. This setup provides a comprehensive testbed for assessing the functionality and reliability of 
the peripheral drivers under real-time processing scenarios.

## Filter Design

The FIR filter was designed using MATLAB's filterDesigner application part of the DSP toolbox. I implemented a Hanning Window with a cut-off frequency of 5Hz. I felt the Hanning window best suited my needs for this project
as a sharper transition zone would be more important than greater side-lobe attenuation. Overall, the output of the accelerometer duid not need to be a perfectly smooth curve, in fact, I wanted to keep the accuracy and
sharpness of the raw data, the filter was just supposed to remove any high frequnecy spikes in the data.

To ensure this filter would also serve its purpose I did pass raw data through this filter in MATLAB which produced the following output.

![Screenshot 2024-05-01 075446](https://github.com/KyleLazera/Real_Time_Processor/assets/122123322/b43bbab5-2a46-4d7a-aade-8558658a1a4a)

