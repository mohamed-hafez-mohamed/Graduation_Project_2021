/*
 * interface.h
 *
 *  Created on: Apr 10, 2021
 *      Author: Omar
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

/* I2Cx names macros */
#define I2C1				0x40	/* random value */
#define I2C2				0x41	/* random value */

/*
 * I2C_SCLSpeed
 */
#define I2C_SCL_Speed_SM	100000
#define I2C_SCL_Speed_FM	400000

/*
 * I2C_ACKControl
 */
#define I2C_ACK_ENABLE		1
#define I2C_ACK_DISNABLE	0

/*
 * I2C_FMDutyCycle
 */
#define I2C_FM_DUTY_2		0
#define I2C_FM_DUTY_16_9	1

/*
 * Peripheral Enable & Disable
 */
#define I2C_ENABLE			1
#define I2C_DISABLE			0

/*
 * Repeated start Enable & Disable
 */
#define I2C_REPEAT_S		1
#define I2C_NO_REPEAT_S		0

/*
 * Transmit & Receive options
 */
#define I2C_RECEIVE			1
#define I2C_TRANSMIT		0

/********************************************************/
/*					API prototypes						*/
/********************************************************/

/*
 * I2C_Init: Initializes I2Cx peripheral with the configuration set by the user.
 * Parameters: I2CHandler (I2C_Handle_t type) Carries the base address Macros for which I2c to be enabled Values: I2C1, I2C2 and configurations.
 * Return type: void.
 */
void I2C_voidInit(uint8 I2Cx);

/*
 * I2C_PeripheralControl: Enables or disables I2Cx peripheral.
 * Parameters:  pI2Cx:  (pointer to I2C_RegDef_t type) The base address Macros for which I2c to be enabled Values: I2C1, I2C2.
 * 				EnOrDi: (uint8) The state needed to set set for the peripheral values I2C_Enable, I2C_Disable.
 * Return type: void.
 */
void I2C_voidPeripheralControl(uint8 I2Cx, uint8 EnOrDi);

/*
 * I2C_voidMasterSendData: Sends data from the buffer as a master through I2C.
 * Parameters:  pI2Cx:  (pointer to I2C_RegDef_t type) The base address Macros for which I2c to be enabled Values: I2C1, I2C2.
 * 				pTxBuffer: (pointer to uint8) The address of the buffer from which data is to be sent.
 * 				Len: (uint8) Length of data to be sent from the buffer.
 * 				SlaveAdd: (uint8) Address of slave to which data is to be sent.
 * 				RepeatedState: (uint8) Status of using repeated start or not.
 * Return type: void.
 */
void I2C_voidMasterSendData(uint8 I2Cx, uint8 * pTxBuffer, uint8 Len, uint8 SlaveAdd, uint8 RepeatedState);

/*
 * I2C_voidMasterReceiveData: Receives data from the slave and stores it in the buffer as a master through I2C.
 * Parameters:  pI2Cx:  (pointer to I2C_RegDef_t type) The base address Macros for which I2c to be enabled Values: I2C1, I2C2.
 * 				pTxBuffer: (pointer to uint8) The address of the buffer in which data is to be received.
 * 				Len: (uint8) Length of data to be received from the slave.
 * 				SlaveAdd: (uint8) Address of slave from which data is to be received.
 * Return type: void.
 */
void I2C_voidMasterReceiveData(uint8 I2Cx, uint8 * pTxBuffer, uint8 Len, uint8 SlaveAdd);

/*
 * Application callback
 */
void I2C_voidApplicationEventCallBack(uint8 I2Cx, uint8 AppEv);


#endif /* INTERFACE_H_ */
