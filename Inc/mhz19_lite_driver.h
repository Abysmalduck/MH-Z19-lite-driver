#ifndef INC_MHZ19_LITE_DRIVER_CPP_
#define INC_MHZ19_LITE_DRIVER_CPP_

#include "main.h"

#define MHZ19_COMMAND_GAS_CONCENTRARION		{0XFF, 0x00, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00}
#define MHZ19_COMMAND_CALIBRATE_ZERO		{0XFF, 0x00, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00}
#define MHZ19_COMMAND_CALIBRATE_SPAN		{0XFF, 0x00, 0x88, 0x07, 0xD0, 0x00, 0x00, 0x00}


class mhz19_driver
{
private:
	uint8_t _mhz19_addr;
	UART_HandleTypeDef* _UART_PORT;
	HAL_StatusTypeDef getData(uint8_t* command, uint8_t* buff);
	uint8_t getChecksum(uint8_t* data);
public:

	mhz19_driver(UART_HandleTypeDef* UART_PORT, uint8_t mhz19_addr);
	HAL_StatusTypeDef getTemp(uint16_t* temp);
	HAL_StatusTypeDef getCO2(uint16_t* co2);
};


#endif /* INC_MH_Z19_LITE_DRIVER_CPP_ */
