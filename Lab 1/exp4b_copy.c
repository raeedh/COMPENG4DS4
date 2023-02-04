typedef status_t (*SPI_WriteFunc_t)(uint8_t regAddress, uint8_t value);
typedef status_t (*SPI_ReadFunc_t)(uint8_t regAddress, uint8_t *rxBuff, uint8_t rxBuffSize);

typedef struct _fxos_handle
{
	/* Pointer to the user-defined I2C Send Data function. */
	I2C_SendFunc_t I2C_SendFunc;
	/* Pointer to the user-defined I2C Receive Data function. */
	I2C_ReceiveFunc_t I2C_ReceiveFunc;
	/* The I2C slave address . */
	uint8_t slaveAddress;
	/* Pointer to the user-defined SPI write Data function. */
	SPI_WriteFunc_t SPI_writeFunc;
	/* Pointer to the user-defined SPI read Data function. */
	SPI_ReadFunc_t SPI_readFunc;
} fxos_handle_t;

typedef struct _fxos_config
{
	/* Pointer to the user-defined I2C Send Data function. */
	I2C_SendFunc_t I2C_SendFunc;
	/* Pointer to the user-defined I2C Receive Data function. */
	I2C_ReceiveFunc_t I2C_ReceiveFunc;
	/* The I2C slave address . */
	uint8_t slaveAddress;
	/* Pointer to the user-defined SPI write Data function. */
	SPI_WriteFunc_t SPI_writeFunc;
	/* Pointer to the user-defined SPI read Data function. */
	SPI_ReadFunc_t SPI_readFunc;
} fxos_config_t;

status_t FXOS_ReadReg(fxos_handle_t *handle, uint8_t reg, uint8_t *val, uint8_t bytesNumber)
{
	assert(handle);
	assert(val);
	if ((handle->SPI_readFunc) == NULL)
	{
		return kStatus_Fail;
	}
	return handle->SPI_readFunc(reg, val, bytesNumber);
}

status_t FXOS_WriteReg(fxos_handle_t *handle, uint8_t reg, uint8_t val)
{
	assert(handle);
	if ((handle->SPI_writeFunc) == NULL)
	{
		return kStatus_Fail;
	}
	return handle->SPI_writeFunc(reg, val);
}

int main(void)
{
	fxos_handle_t fxosHandle = {0};
	fxos_data_t sensorData = {0};
	fxos_config_t config = {0};
	uint8_t sensorRange = 0;
	uint8_t dataScale = 0;
	int16_t xData = 0;
	int16_t yData = 0;
	uint8_t i = 0;
	uint8_t array_addr_size = 0;
	status_t result = kStatus_Fail;
	volatile int16_t xAngle = 0;
	volatile int16_t yAngle = 0;
	/* Board pin, clock, debug console init */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	voltageRegulatorEnable();
	accelerometerEnable();
	setupSPI();
	/***** Delay *****/
	for (volatile uint32_t i = 0; i < 4000000; i++)
		__asm("NOP");
	/* Configure the SPI function */
	config.SPI_writeFunc = SPI_write;
	config.SPI_readFunc = SPI_read;
	result = FXOS_Init(&fxosHandle, &config);
	if (result != kStatus_Success)
	{
		PRINTF("\r\nSensor device initialize failed!\r\n");
		return -1;
	}
	/* Get sensor range */
	if (FXOS_ReadReg(&fxosHandle, XYZ_DATA_CFG_REG, &sensorRange, 1) != kStatus_Success)
	{
		return -1;
	}
	if (sensorRange == 0x00)
	{
		dataScale = 2U;
	}
	else if (sensorRange == 0x01)
	{
		dataScale = 4U;
	}
	else if (sensorRange == 0x10)
	{
		dataScale = 8U;
	}
	else
	{
	}
	/* Print a note to terminal */
	PRINTF("\r\nWelcome to the BUBBLE example\r\n");
	PRINTF("\r\nYou will see the change of angle data\r\n");
	/* Main loop. Get sensor data and update duty cycle */
	while (1)
	{
		/* Get new accelerometer data. */
		if (FXOS_ReadSensorData(&fxosHandle, &sensorData) != kStatus_Success)
		{
			return -1;
		}
		/* Get the X and Y data from the sensor data structure in 14 bit left format
		data*/
		xData = ((int16_t)((uint16_t)((uint16_t)sensorData.accelXMSB << 8) | (uint16_t)
																				 sensorData.accelXLSB)) /
				4U;
		yData = ((int16_t)((uint16_t)((uint16_t)sensorData.accelYMSB << 8) | (uint16_t)
																				 sensorData.accelYLSB)) /
				4U;
		/* Convert raw data to angle (normalize to 0-90 degrees). No negative angles. */
		xAngle = (int16_t)floor((double)xData * (double)dataScale * 90 / 8192);
		yAngle = (int16_t)floor((double)yData * (double)dataScale * 90 / 8192);
		/* Print out the angle data. */
		PRINTF("x= %2d y = %2d\r\n", xAngle, yAngle);
		/***** Delay *****/
		for (volatile uint32_t i = 0; i < 500000; i++)
			__asm("NOP");
	}
}