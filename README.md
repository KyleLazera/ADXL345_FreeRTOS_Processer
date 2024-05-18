# Summary

This project implements a real-time processing system designed to enhance the testing of the 'stm32f4xx_peripheral_driver' series project in a more robust and practical manner. The system utilizes FreeRTOS to perform concurrent tasks, 
including reading sensor data from an accelerometer and a temperature/pressure sensor. The raw sensor data is then processed using a digital Finite Impulse Response (FIR) filter. The processed data is then output through a series of LEDs using Pulse width modulation
to indicate how much each axis is currently changing visually. Additionally, a command line interface that allows the user to view the data they specify. This could include the x-axis, y-axis, z-axis, temperature or pressure data. 

By leveraging FreeRTOS, the system demonstrates simultaneous execution of tasks while evaluating the performance of the peripheral drivers. This setup provides a comprehensive testbed for assessing the functionality and reliability of 
the peripheral drivers under real-time processing scenarios.

## Filter Design

The FIR filter was designed using MATLAB's filterDesigner application, a part of the DSP Toolbox. I opted for a low-pass filter using a Hanning Window with a cut-off frequency of 5Hz, as it best suited the requirements of this project. For this application, a sharper transition zone was more critical than greater side-lobe attenuation.

The objective of the filter was to remove high-frequency spikes in the accelerometer data while preserving the accuracy and sharpness of the raw data. Therefore, the foutput was not intended to be a smooth curve. 
To validate the effectiveness of the filter, raw data was passed through the filter in MATLAB. The resulting output clearly demonstrated the removal of high-frequency noise spikes while retaining the desired sharpness 
of the accelerometer data.

![Screenshot 2024-05-01 075446](https://github.com/KyleLazera/Real_Time_Processor/assets/122123322/b43bbab5-2a46-4d7a-aade-8558658a1a4a)

#### Frequency Response of Filter:

The depicted frequency response below illustrates the ideal behavior of the filter. However, due to the restriction of the filter order to 16, the actual frequency response exhibits some deviation from the ideal response. As a result, the frequency response may not be as smooth, and the side-lobes may not be as prominent as desired.

The actual frequency response is provided below for reference.

![Screenshot 2024-05-01 081443](https://github.com/KyleLazera/Real_Time_Processor/assets/122123322/85553552-2185-4782-8ac8-87173d09067c)

![Screenshot 2024-05-01 081501](https://github.com/KyleLazera/Real_Time_Processor/assets/122123322/b43db538-abed-4070-80d1-f012f16f741d)

#### Filter Behavior:

Link to video displaying the raw data being filtered: The red line is the raw data and the green line is the filtered data.
To display the outcomes I am using the Serial Oscilliscope application which can be downlaoded here: https://x-io.co.uk/serial-oscilloscope/

https://youtube.com/shorts/gONS1rhD3NI

#### LED Display:

To add a visual component to the project I included a series of 3 LED's that would display how each axis on the accelerometer is changing in real-time. Each LED represents
a single axis and uses pulse width modulation to brighten and dim as each axis gets further away from 0. A link to a video displaying this function is below. In the video, the 
LED's fo from left to right as follows: y-axis, x-axis and z-axis.

https://youtube.com/shorts/mXdzUgcmPYM

Note: The y-axis LED does not start at 0 as  the accelerometer does not sit flat in the breadboard, therefore it is slightly dimmed at the start. 
