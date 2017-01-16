/*
 * board.h
 *
 *  Created on: 2016年1月12日
 *      Author: kohill
 */

#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_
u16 k_INA226_ReadReg(void);
int k_INA226_SetRegPointer(u8 p);
int k_INA226_Fast_Config(void);
int k_INA226_WriteReg(u8 regAddr,u16 data);
float k_read_Voltage(void);
float k_read_current(void);
#define WIFI_RESET "AT+RST\n" //复位wifi模块
void pwm_init(void);


#endif /* BOARD_BOARD_H_ */
