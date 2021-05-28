/*
 * I2C_config.h
 *
 *  Created on: Apr 10, 2021
 *      Author: Omar
 */

#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#define SYSTEM_CLK_MHZ		8
#define AHB_PRE				1
#define AHB1_PRE			4

/* Configuring I2C1 */
#define I2C1_ACKControl  	I2C_ACK_ENABLE
#define I2C1_FMDutyCycle 	I2C_FM_DUTY_2
#define I2C1_SCLSpeed 		100000
#define I2C1_DeviceAddress 	0x7E



#endif /* I2C_CONFIG_H_ */
