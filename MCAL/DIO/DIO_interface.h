/*
 * DIO_interface.h
 *
 * Author: Modern Computer
 * Layer : MCAL
 * SWC   : DIO/GPIO
 * 
 */
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_PIN_INPUT  	0
#define DIO_PIN_OUTPUT 	1

#define DIO_PIN_LOW 	0
#define DIO_PIN_HIGH 	1

#define DIO_PORTA		0
#define DIO_PORTB		1
#define DIO_PORTC		2
#define DIO_PORTD		3

#define DIO_PIN0		0
#define DIO_PIN1		1
#define DIO_PIN2		2
#define DIO_PIN3		3
#define DIO_PIN4		4
#define DIO_PIN5		5
#define DIO_PIN6		6
#define DIO_PIN7		7

void DIO_SetPinDir 		(u8 Copy_u8PORT,u8 Copy_u8PIN,u8 Copy_u8Dir);
void DIO_SetPinValue	(u8 Copy_u8PORT,u8 Copy_u8PIN,u8 Copy_u8Value);
u8   DIO_GetPinValue	(u8 Copy_u8PORT,u8 Copy_u8PIN);

#enfif 