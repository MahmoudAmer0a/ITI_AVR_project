/*
 * SPI.c
 *
 *  Created on: Sep 4, 2023
 *      Author: Modern Computer
 */
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../HAL/LCD/LCD.h"
#include "SPI.h"



void SPI_voidInit(u8 Copy_u8SPIType){
	//switch on Mode
	switch(Copy_u8SPIType){
	case Master:
		//select master
		SET_BIT(SPCR,MSTR);
		//select speed
		SPCR &= (0b11111100)|(fosc_8%4);
		#if Clock_Rate_mode < 3
			CLR_BIT(SPSR,SPI2X);
		#else
			SET_BIT(SPSR,SPI2X);
		#endif
		SET_BIT(DDRB,PIN5);// set MOSI as Out
		CLR_BIT(DDRB,PIN6);// set MISO as In
		SET_BIT(DDRB,PIN7);// set SCLK as Out
		SET_BIT(DDRB,PIN4);// set ss as Out
		break;
	case Slave :
		//select slave
		CLR_BIT(SPCR,MSTR);
		SET_BIT(DDRB,PIN6);// set MISO as Out
		break;
	default:
		break;
	}
	//select Data Order (MSB frist)
	CLR_BIT(SPCR,DORD);
	//select clock polarity active
	CLR_BIT(SPCR,CPOL);
	//select clock phase  1-setup 2-sample
	SET_BIT(SPCR,CPHA);
	//enable SPI Periphral
	SET_BIT(SPCR,SPE);
}

u8   SPI_u8transcieve	(u8 Copy_u8TransmitByte){
	//put Data to begin transmition
	SPDR = Copy_u8TransmitByte ;
	//wait until transmition ends
	while(GET_BIT(SPSR,SPIF) == 0);
	//return the data
	return SPDR ;
}






