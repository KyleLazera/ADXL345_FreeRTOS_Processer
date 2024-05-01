# Summary

This project implements a real-time processing system designed to enhance the testing of the 'stm32f4xx_peripheral_driver' series project in a more robust and practical manner. The system utilizes FreeRTOS to perform concurrent tasks, 
including reading sensor data from an accelerometer and a temperature/pressure sensor. The raw sensor data is then processed using a digital Finite Impulse Response (FIR) filter. The processed data is then output through a series of LEDs 
for visual indication and via serial communication for further analysis.

By leveraging FreeRTOS, the system demonstrates simultaneous execution of tasks while evaluating the performance of the peripheral drivers. This setup provides a comprehensive testbed for assessing the functionality and reliability of 
the peripheral drivers under real-time processing scenarios.

## Filter Design

The FIR filter was designed using MATLAB's filterDesigner application, a part of the DSP Toolbox. I opted for a low-pass filter using a Hanning Window with a cut-off frequency of 5Hz, as it best suited the requirements of this project. For this application, a sharper transition zone was more critical than greater side-lobe attenuation.

The objective of the filter was to remove high-frequency spikes in the accelerometer data while preserving the accuracy and sharpness of the raw data. Therefore, the foutput was not intended to be a smooth curve. 
To validate the effectiveness of the filter, raw data was passed through the filter in MATLAB. The resulting output clearly demonstrated the removal of high-frequency noise spikes while retaining the desired sharpness 
of the accelerometer data.

![Screenshot 2024-05-01 075446](https://github.com/KyleLazera/Real_Time_Processor/assets/122123322/b43bbab5-2a46-4d7a-aade-8558658a1a4a)

