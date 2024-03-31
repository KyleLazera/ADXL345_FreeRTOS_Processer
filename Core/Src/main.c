#include "cmsis_os.h"
#include "stm32f401_spi.h"

SPI_Handle_t SPI1_Example;
GPIO_Config_t ADXL, BME;

typedef enum
{
	x_axis,
	y_axis,
	z_axis
}AxisOfRotation;

typedef struct
{
	AxisOfRotation axis;
	int16_t value;
}AccelerometerData;


int16_t x, y, z, _x, _y, _z;
double xg, yg, zg;
uint8_t adxl_data_rec[7];
uint8_t	bme_data_rec[9];

int counter, counterFail, datasent, datafailed;

void SPI_Specs_Init();
void SPI1_IRQHandler();

void ReadADXLData(void *pvParameters);
void DummyTask(void *pvParameters);

QueueHandle_t x_axis_queue;

int main()
{

	x_axis_queue = xQueueCreate(6, sizeof(AccelerometerData));  //Create queue to hold read data

	xTaskCreate(ReadADXLData, "Read ADXL Task", 1000, NULL, 1, NULL);
	xTaskCreate(DummyTask, "Data Processing Task", 500, NULL, 1, NULL);

	vTaskStartScheduler();

}

void DummyTask(void *pvParameters)
{
	BaseType_t queue_status;
	AccelerometerData rec_data;

	while(1)
	{
		queue_status = xQueueReceive(x_axis_queue, &rec_data, 0);

		switch(rec_data.axis)
		{
		case x_axis:
			_x = rec_data.value;
			break;
		case y_axis:
			_y = rec_data.value;
			break;
		case z_axis:
			_z = rec_data.value;
			break;
		}

		if(queue_status == pdPASS)
		{
			counter++;
		}
		else
		{
			counterFail++;
		}
	}
}

void ReadADXLData(void *pvParameters)
{
	AccelerometerData data;
	/*
	 * Data that holds the address of the data registers of the ADXL - this is where data will be read
	 * from (Not the address of the device).
	 */
	uint8_t adxl_address[1] = {0xF2};

	/*
	 * Variables to initialize the ADXL registers to set range to +- 4g, to allow
	 * continous reading of the data registers and set the transfer rate to 100Hz.
	 */
	uint8_t adxl_set_data_format[2] = {0x31, 0x01};
	uint8_t adxl_clear_powerctl_reg[2] = {0x2D, 0x00};
	uint8_t adxl_set_powerctl_reg[2] = {0x2D, 0x08};
	uint8_t adxl_set_bw_rate_reg[2] = {0x2C, 0x0A};

	//Create and initialze a slave pin with the desired port and pin
	GPIO_Config(&ADXL, GPIOA, Pin8, GPIO_Output, GPIO_PushPull, GPIO_LowSpeed, GPIO_PullUp);
	GPIO_Init(&ADXL, 0x0);
	GPIOA->ODR |= (1U << 8); //Used to enable the P-MOS and ensure CS is active high

	SPI_Specs_Init();

	SPI_Init(&SPI1_Example);

	/*
	 * Initial Transmission to send to the ADXL. Sets the ADXL to specified settings.
	 */
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_clear_powerctl_reg, 2);
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_set_data_format, 2);
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_set_bw_rate_reg, 2);
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_set_powerctl_reg, 2);

	while(1)
	{
		//Reading data from the SPI
		SPI_MultiSlave_RecieveIT(&SPI1_Example, &ADXL, adxl_data_rec, 7, *adxl_address);

		x = ((adxl_data_rec[2] << 8) | adxl_data_rec[1]);
		data.axis = x_axis;
		data.value = x;
		xQueueSend(x_axis_queue, &data, 0);

		y = ((adxl_data_rec[4] << 8) | adxl_data_rec[3]);
		data.axis = y_axis;
		data.value = y;
		xQueueSend(x_axis_queue, &data, 0);

		z = ((adxl_data_rec[6] << 8) | adxl_data_rec[5]);
		data.axis = z_axis;
		data.value = z;
		xQueueSend(x_axis_queue, &data, 0);

		xg = (x * 0.0078);
		yg = (y * 0.0078);
		zg = (z * 0.0078);
	}

}

/*
 * Function to serve interrupts
 */
void SPI1_IRQHandler()
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	SPI_IRQ_Handler(&SPI1_Example);

	//Causes a context switch for the CPU
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*
 * Function to set the SPI specs
 */
void SPI_Specs_Init()
{
	//Set desired pins
	SPI1_Example.SPI_Config.cs_gpio = GPIOA;
	SPI1_Example.SPI_Config.pin_clk = Pin5;
	SPI1_Example.SPI_Config.pin_miso = Pin6;
	SPI1_Example.SPI_Config.pin_mosi = Pin7;

	//Set desired transfer methods
	SPI1_Example.ssm = SSM_Enable;
	SPI1_Example.SPIx = SPI1;
	SPI1_Example.SPI_Config.baudrate_ctrl = DIV4;
	SPI1_Example.SPI_Config.cpha = Falling_Edge;
	SPI1_Example.SPI_Config.cpol = Even_Polarity;
	SPI1_Example.SPI_Config.data_format = MSB_First;
	SPI1_Example.data_frame = Data_8_Bits;
}
