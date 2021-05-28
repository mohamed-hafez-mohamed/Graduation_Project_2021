/*
 * I2C_program.c
 *
 *  Created on: Apr 10, 2021
 *      Author: Omar
 */

#include "BIT_MATH.h"
#include "Std_Types.h"

#include "I2c_Private.h"
#include "I2c_Config.h"
#include "I2c_Interface.h"

/*
 * I2C_voidExcuteSendAddress: Sends the 7-bit slave address after adding the LSB representing whether the master wants to transmit or receive data from the slave
 * parameters:	pI2Cx:  (pointer to I2C_RegDef_t type) The base address Macros for which I2c to be enabled Values: I2C1, I2C2.
 * 				T_RState: (uint8) Action needed to be executed (options: I2C_TRANSMIT, I2C_RECEIVE)
 * 				SlaveAdd: (uint8) Address of slave to which data is to be sent.
 *
 */
static void I2C_voidExicuteSendAddress(I2C_RegDef_t *pI2Cx, uint8 SlaveAdd, uint8 T_RState)
{
	pI2Cx->DR = (( SlaveAdd & 0x7F ) << 1) | T_RState;
}

/*
 * I2C_voidExcuteSendAddress: Sends the 7-bit slave address after adding the LSB representing whether the master wants to transmit or receive data from the slave
 * parameters:	pI2Cx:  (pointer to I2C_RegDef_t type) The base address Macros for which I2c to be enabled Values: I2C1, I2C2.
 * 				T_RState: (uint8) Action needed to be executed (options: I2C_TRANSMIT, I2C_RECEIVE)
 * 				SlaveAdd: (uint8) Address of slave to which data is to be sent.
 *
 */
static I2C_RegDef_t * I2C_GetBaseAdd(uint8 val)
{
	switch(val)
		{
		case I2C1:
			return (I2C_RegDef_t *)I2C1_BASE;
			break;
		case I2C2:
			return (I2C_RegDef_t *)I2C2_BASE;
			break;
		default:
			return (I2C_RegDef_t *)0;
		break;
		}
}

/*
 * I2C_Init: Initializes I2Cx peripheral with the configuration set by the user.
 * Parameters: I2CHandler (I2C_Handle_t type) Carries the base address Macros for which I2c to be enabled Values: I2C1, I2C2 and configurations.
 * Return type: void.
 */
void I2C_voidInit(uint8 I2Cx)
{
	I2C_RegDef_t * pI2Cx = I2C_GetBaseAdd(I2Cx);

	uint32 TempFreq = SYSTEM_CLK_MHZ/(AHB_PRE*AHB1_PRE);

	/* Setting the Auto Acking value */
	pI2Cx->CR1 |= (I2C1_ACKControl << I2C_CR1_ACK);

	/* Writing Peripheral clock frequency (APB1 freq) in Freq bits of CR2 */
	pI2Cx->CR2 = TempFreq & 0b11111;

	/* Calculating and setting CCR Value to configure SCLSpeed */
	if(I2C1_SCLSpeed <= I2C_SCL_Speed_SM)
	{
		pI2Cx->CCR = (0x7FF & ((TempFreq * 1000000)/(2 * I2C1_SCLSpeed)));
		pI2Cx->TRISE = (TempFreq + 1) & 0x3F ;
	}
	else if(I2C1_SCLSpeed <= I2C_SCL_Speed_FM)
	{
		switch(I2C1_FMDutyCycle)
		{
		case I2C_FM_DUTY_2:
			pI2Cx->TRISE = ( (TempFreq * 300 /1000) + 1) & 0x3F ;
			pI2Cx->CCR = (1<<I2C_CCR_F_S) |(0x7FF & (TempFreq * 1000000)/(3 * I2C1_SCLSpeed));
			break;
		case I2C_FM_DUTY_16_9:
			pI2Cx->TRISE = ( (TempFreq * 120 /1000) + 1) & 0x3F ;
			pI2Cx->CCR = (1<<I2C_CCR_DUTY) |(1<<I2C_CCR_F_S) |(0x7FF & (TempFreq * 1000000)/(25 * I2C1_SCLSpeed));
			break;
		}

	}

	/* Setting Own Address */
	pI2Cx->OAR1 = (1<<14) | (I2C1_DeviceAddress << 1);
}



/*
 * I2C_voidMasterSendData: Sends data from the buffer as a master through I2C.
 * Parameters:  pI2Cx:  (pointer to I2C_RegDef_t type) The base address Macros for which I2c to be enabled Values: I2C1, I2C2.
 * 				pTxBuffer: (pointer to uint8) The address of the buffer from which data is to be sent.
 * 				Len: (uint8) Length of data to be sent from the buffer.
 * 				SlaveAdd: (uint8) Address of slave to which data is to be sent.
 * 				RepeatedState: (uint8) Status of using repeated start or not.
 * Return type: void.
 */
void I2C_voidMasterSendData(uint8 I2Cx, uint8 * pTxBuffer, uint8 Len, uint8 SlaveAdd, uint8 RepeatedState)
{
	I2C_RegDef_t * pI2Cx = I2C_GetBaseAdd(I2Cx);

//	pI2Cx->SR1 = 0;
	/* wait until the shift register , data register are empty after transmitting all the data (BTF = 1) */
	while(GET_BIT(pI2Cx->SR1, I2C_SR2_BUSY));

	/* Start generation condition */
	I2C_VOID_SEND_START_CONDITION(pI2Cx);

	/* Wait until start condition is generated successfully (until SB bit in SR1 register = 1) */
	while(! GET_BIT(pI2Cx->SR1, I2C_SR1_SB));

	/* Writing DR register with slave Address with LSB reset (Bit 0 = 0) */
	I2C_voidExicuteSendAddress(pI2Cx, SlaveAdd, I2C_TRANSMIT);

	/* Wait until address transmission is done successfully (until ADDR bit in SR1 register = 1) */
	while(! GET_BIT(pI2Cx->SR1, I2C_SR1_ADDR));

	/* Reset ADDR by reading SR2 register (SR1 was already read in the previous step)*/
	(void)GET_BIT(pI2Cx->SR2, I2C_SR2_MSL);

	/*********		Loop this part until the needed bytes are sent  		*********/
	for(uint8 i = 0; i < Len; i++)
	{
	/* Check if data register is empty (TxE bit in SR1 register = 1) */
	while(! GET_BIT(pI2Cx->SR1, I2C_SR1_TXE));
	/* Write Data1 in DR register */
	pI2Cx->DR = pTxBuffer[i];
	}
	/*********************************************************************************/

	/* wait until the shift register , data register are empty after transmitting all the data (BTF = 1) */
	while(! GET_BIT(pI2Cx->SR1, I2C_SR1_BTF));

	switch(RepeatedState)
	{
	case I2C_NO_REPEAT_S:
		/* send the stop condition */
		I2C_VOID_SEND_STOP_CONDITION(pI2Cx);
		break;
	default:
		break;
	}
	__asm("NOP");
}


/*
 * I2C_voidMasterReceiveData: Receives data from the slave and stores it in the buffer as a master through I2C.
 * Parameters:  pI2Cx:  (pointer to I2C_RegDef_t type) The base address Macros for which I2c to be enabled Values: I2C1, I2C2.
 * 				pTxBuffer: (pointer to uint8) The address of the buffer in which data is to be received.
 * 				Len: (uint8) Length of data to be received from the slave.
 * 				SlaveAdd: (uint8) Address of slave from which data is to be received.
 * Return type: void.
 */
void I2C_voidMasterReceiveData(uint8 I2Cx, uint8 * pTxBuffer, uint8 Len, uint8 SlaveAdd)
{

	I2C_RegDef_t * pI2Cx = I2C_GetBaseAdd(I2Cx);


//	pI2Cx->SR1 = 0;
	/* wait until the shift register , data register are empty after transmitting all the data (BTF = 1) */
	//while(GET_BIT(pI2Cx->SR1, I2C_SR2_BUSY));

	/* Start generation condition */
	I2C_VOID_SEND_START_CONDITION(pI2Cx);

	/* Wait until start condition is generated successfully (until SB bit in SR1 register = 1) */
	while(! GET_BIT(pI2Cx->SR1, I2C_SR1_SB));

	/* Writing DR register with slave Address with LSB set (Bit 0 = 1) */
	I2C_voidExicuteSendAddress(pI2Cx, SlaveAdd, I2C_RECEIVE);

	/* Wait until address transmission is done successfully (until ADDR bit in SR1 register = 1) */
	while(! GET_BIT(pI2Cx->SR1, I2C_SR1_ADDR));

	switch(Len)
	{
	case 1:
		I2C_VOID_DISABLE_ACK(pI2Cx);

		/* Reset ADDR by reading SR2 register (SR1 was already read in the previous step)*/
		(void)GET_BIT(pI2Cx->SR2, I2C_SR2_MSL);

		I2C_VOID_SEND_STOP_CONDITION(pI2Cx);

		/* Check if data register is not empty (RxNE bit in SR1 register = 1) */
		while(! GET_BIT(pI2Cx->SR1, I2C_SR1_RXNE));


		/* Read Data from DR register */
		pTxBuffer[0] = pI2Cx->DR;
		break;
	default:
		I2C_VOID_ENABLE_ACK(pI2Cx);
		/* Reset ADDR by reading SR2 register (SR1 was already read in the previous step)*/
		(void)GET_BIT(pI2Cx->SR2, I2C_SR2_MSL);

		/*********		Loop this part until the needed bytes are sent  		*********/
		for(uint8 i = 0; i < Len-1; i++)
		{
		/* Check if data register is not empty (RxNE bit in SR1 register = 1) */
		while( (! GET_BIT(pI2Cx->SR1, I2C_SR1_RXNE)) && (! GET_BIT(pI2Cx->SR1, I2C_SR1_BTF)));
		/* Read Data from DR register */
		pTxBuffer[i] = pI2Cx->DR;
		}
		/*********************************************************************************/

		I2C_VOID_DISABLE_ACK(pI2Cx);
		I2C_VOID_SEND_STOP_CONDITION(pI2Cx);

		/* Check if data register is not empty (RxNE bit in SR1 register = 1) */
		while( (! GET_BIT(pI2Cx->SR1, I2C_SR1_RXNE)) && (! GET_BIT(pI2Cx->SR1, I2C_SR1_BTF)));

		/* Read Data from DR register */
		pTxBuffer[Len-1] = pI2Cx->DR;
		break;
	}

	__asm("NOP");
}

/*
 * I2C_PeripheralControl: Enables or disables I2Cx peripheral.
 * Parameters:  pI2Cx:  (pointer to I2C_RegDef_t type) The base address Macros for which I2c to be enabled Values: I2C1, I2C2.
 * 				EnOrDi: (uint8) The state needed to set set for the peripheral values I2C_Enable, I2C_Disable.
 * Return type: void.
 */
void I2C_voidPeripheralControl(uint8 I2Cx, uint8 EnOrDi)
{
	I2C_RegDef_t * pI2Cx = I2C_GetBaseAdd(I2Cx);
	switch(EnOrDi)
	{
	case I2C_ENABLE:
		/* Enabling the peripheral */
		SET_BIT(pI2Cx->CR1, I2C_CR1_PE);
		break;
	case I2C_DISABLE:
		/* Disabling the peripheral */
		CLR_BIT(pI2Cx->CR1, I2C_CR1_PE);
		break;
	}
}
