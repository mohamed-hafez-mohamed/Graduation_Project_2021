/*
 * I2C_private.h
 *
 *  Created on: Apr 10, 2021
 *      Author: Omar
 */

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_


/*
 * I2C peripheral register definition structure
 */
typedef struct{
	volatile uint32 CR1  ;
	volatile uint32 CR2  ;
	volatile uint32 OAR1 ;
	volatile uint32 OAR2 ;
	volatile uint32 DR   ;
	volatile uint32 SR1  ;
	volatile uint32 SR2  ;
	volatile uint32 CCR	 ;
	volatile uint32 TRISE;
}I2C_RegDef_t;


/*
 * I2Cx base addresses macros
 */
#define I2C1_BASE_ADDRESS		0x40005400
#define I2C2_BASE_ADDRESS		0x40005800

/*
 * I2Cx peripheral definition macros
 */
#define I2C1_BASE		((I2C_RegDef_t *)I2C1_BASE_ADDRESS)
#define I2C2_BASE		((I2C_RegDef_t *)I2C2_BASE_ADDRESS)

/*
 * Bit position definitions for I2C_CR1
 */
#define I2C_CR1_SWRST		15
#define I2C_CR1_ACK			10
#define I2C_CR1_STOP		9
#define I2C_CR1_START		8
#define I2C_CR1_NOSTRETCH	7
#define I2C_CR1_PE			0

/*
 * Bit position definitions for I2C_CR2
 */
#define I2C_CR2_FREQ		0

/*
 * Bit position definitions for I2C_OAR2
 */
#define I2C_OAR2_ADD2		1
#define I2C_OAR2_ENDUAL		0

/*
 * Bit position definitions for I2C_SR1
 */
#define I2C_SR1_TXE			7
#define I2C_SR1_RXNE		6
#define I2C_SR1_BTF			2
#define I2C_SR1_ADDR		1
#define I2C_SR1_SB			0

/*
 * Bit position definitions for I2C_SR2
 */
#define I2C_SR2_DUALF		7
#define I2C_SR2_GENCALL		4
#define I2C_SR2_TRA			2
#define I2C_SR2_BUSY		1
#define I2C_SR2_MSL			0

/*
 * Bit position definitions for I2C_CCR
 */
#define I2C_CCR_F_S			15
#define I2C_CCR_DUTY		14


/*
 * Private functions
 */

/* I2C_VOID_SEND_START_CONDITION: Sends the start condition through I2Cx peripheral */
#define	I2C_VOID_SEND_START_CONDITION(pI2Cx)	(pI2Cx->CR1 |= 1 << I2C_CR1_START)

/* I2C_VOID_SEND_STOP_CONDITION: Sends the start condition through I2Cx peripheral */
#define	I2C_VOID_SEND_STOP_CONDITION(pI2Cx)	(pI2Cx->CR1 |= 1 << I2C_CR1_STOP)

/* I2C_VOID_DISABLE_ACK: Disables Auto ACKing for I2Cx peripheral */
#define	I2C_VOID_DISABLE_ACK(pI2Cx)	(CLR_BIT(pI2Cx->CR1, I2C_CR1_ACK));

/* I2C_VOID_ENABLE_ACK: Enables Auto ACKing for I2Cx peripheral */
#define	I2C_VOID_ENABLE_ACK(pI2Cx)	(SET_BIT(pI2Cx->CR1, I2C_CR1_ACK));




#endif /* I2C_PRIVATE_H_ */
