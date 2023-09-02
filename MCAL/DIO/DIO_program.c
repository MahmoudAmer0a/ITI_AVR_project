/*
 * DIO_program.c
 *
 * Author: Modern Computer
 * Layer : MCAL
 * SWC   : DIO/GPIO
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

void DIO_SetPinDir 	(u8 Copy_u8PORT,u8 Copy_u8PIN,u8 Copy_u8Dir){
	if(Copy_u8Dir == DIO_PIN_OUTPUT){
		switch (Copy_u8PORT){
			case DIO_PORTA :SET_BIT(DDRA,Copy_u8PIN);break;
			case DIO_PORTB :SET_BIT(DDRB,Copy_u8PIN);break;
			case DIO_PORTC :SET_BIT(DDRC,Copy_u8PIN);break;
			case DIO_PORTD :SET_BIT(DDRD,Copy_u8PIN);break;
		}
	}
	else if(Copy_u8Dir == DIO_PIN_INPUT){
		switch (Copy_u8PORT){
			case DIO_PORTA :CLR_BIT(DDRA,Copy_u8PIN);break;
			case DIO_PORTB :CLR_BIT(DDRB,Copy_u8PIN);break;
			case DIO_PORTC :CLR_BIT(DDRC,Copy_u8PIN);break;
			case DIO_PORTD :CLR_BIT(DDRD,Copy_u8PIN);break;
		}
	}
}

void DIO_SetPinValue(u8 Copy_u8PORT,u8 Copy_u8PIN,u8 Copy_u8Value){
	if(Copy_u8Value == DIO_PIN_HIGH){
		switch (Copy_u8PORT){
			case DIO_PORTA :SET_BIT(PORTA,Copy_u8PIN);break;
			case DIO_PORTB :SET_BIT(PORTB,Copy_u8PIN);break;
			case DIO_PORTC :SET_BIT(PORTC,Copy_u8PIN);break;
			case DIO_PORTD :SET_BIT(PORTD,Copy_u8PIN);break;
		}
	}
	else if(Copy_u8Value == DIO_PIN_LOW){
		switch (Copy_u8PORT){
			case DIO_PORTA :CLR_BIT(PORTA,Copy_u8PIN);break;
			case DIO_PORTB :CLR_BIT(PORTB,Copy_u8PIN);break;
			case DIO_PORTC :CLR_BIT(PORTC,Copy_u8PIN);break;
			case DIO_PORTD :CLR_BIT(PORTD,Copy_u8PIN);break;
		}
	}
}

u8   DIO_GetPinValue	(u8 Copy_u8PORT,u8 Copy_u8PIN){
		u8 Value = 0 ;
		switch (Copy_u8PORT){
			case DIO_PORTA :Value = GET_BIT(PINA,Copy_u8PIN);break;
			case DIO_PORTB :Value = GET_BIT(PINB,Copy_u8PIN);break;
			case DIO_PORTC :Value = GET_BIT(PINC,Copy_u8PIN);break;
			case DIO_PORTD :Value = GET_BIT(PIND,Copy_u8PIN);break;
		}
return Value ;
}
