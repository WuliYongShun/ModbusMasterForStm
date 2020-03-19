#ifndef _MODBUSMASTER_H
#define _MODBUSMASTER_H


#include "stm32f1xx_hal.h"


#define u8	uint8_t
#define u16	uint16_t
#define u32 uint32_t


#define READ_COIL     01
#define READ_DI       02
#define READ_HLD_REG  03
#define READ_AI       04
#define SET_COIL      05
#define SET_HLD_REG   06
#define WRITE_COIL    15
#define WRITE_HLD_REG 16


#define HI( n ) ( ( n ) >> 8 )
#define LOW( n ) ( ( n ) & 0xff )

#define RS485_TX_EN		HAL_GPIO_WritePin( RS485_ENABLE_GPIO_Port, RS485_ENABLE_Pin, GPIO_PIN_SET )
#define RS485_TX_DEN	HAL_GPIO_WritePin( RS485_ENABLE_GPIO_Port, RS485_ENABLE_Pin, GPIO_PIN_RESET )




void Modbus_RegMap( void );
void RS485_TX_Service( void );
void modbus_rtu( void );





#endif

