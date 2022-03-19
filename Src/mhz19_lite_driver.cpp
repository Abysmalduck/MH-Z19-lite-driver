#include "mhz19_lite_driver.h"

mhz19_driver::mhz19_driver(UART_HandleTypeDef* UART_PORT, uint8_t mhz19_addr)
{
	_UART_PORT = UART_PORT;
	_mhz19_addr = mhz19_addr;
}

HAL_StatusTypeDef mhz19_driver::getTemp(uint16_t* temp)
{
	uint8_t command[9] = MHZ19_COMMAND_GAS_CONCENTRARION;
	uint8_t buff[9];
	HAL_StatusTypeDef status;

	status = getData(command, buff);

	if (status == HAL_OK)
	{
		*temp = (uint16_t)(buff[4]);
		return status;
	}
	else
	{
		return status;
	}
}

HAL_StatusTypeDef mhz19_driver::getCO2(uint16_t* co2)
{
	uint8_t command[9] = MHZ19_COMMAND_GAS_CONCENTRARION;
	uint8_t buff[9];
	HAL_StatusTypeDef status;

	status = getData(command, buff);

	if (status == HAL_OK)
	{
		*co2 = (uint16_t)(buff[2] * 256 + buff[3]);
		return status;
	}
	else
	{
		return status;
	}
}

HAL_StatusTypeDef mhz19_driver::getData(uint8_t* command, uint8_t* buff)
{
	HAL_StatusTypeDef status;
	uint8_t _buff[9];
	for (uint8_t j = 0; j < 8; j++)
	{
		_buff[j] = command[j];
	}
	_buff[1] = _mhz19_addr;
	_buff[8] = getChecksum(_buff);

	HAL_UART_Transmit(_UART_PORT, (uint8_t*)_buff, 9, HAL_MAX_DELAY);
	status = HAL_UART_Receive(_UART_PORT, (uint8_t*)_buff, 9, 300);

	if (getChecksum(_buff) != _buff[8] && _buff[0] != 0xFF)
	{
		return HAL_ERROR;
	}
	else
	{
		for (uint8_t i = 0; i < 9; i++) buff[i] = _buff[i];
		return status;
	}
}

uint8_t mhz19_driver::getChecksum(uint8_t* data)
{
	uint8_t checksum = 0;
	for (uint8_t i = 1;i < 8; i++)
	{
		checksum += data[i];
	}

	checksum = 0xff - checksum;
	checksum += 0x01;

	return checksum;
}
