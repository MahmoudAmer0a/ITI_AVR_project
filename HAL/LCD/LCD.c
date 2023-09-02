/*
 * LCD.c
 *
 *  Created on: Aug 13, 2023
 *      Author: eng_youssef_goher
 */
#include<avr/io.h>
#include<avr/delay.h>
#include"00-LIB/STD_TYPES.h"
#include"00-LIB/BIT_MATH.h"
#include "LCD.h"
/*
 * 	#define LCD_Data_PORT		PORTA
	#define LCD_CONTROL_PORT 	PORTB
	#define LCD_Data_PORT_DDR		DDRA
	#define LCD_CONTROL_PORT_DDR	DDRB

	#define RS_pin				PIN0
	#define RW_pin				PIN1
	#define E_pin				PIN2
	#define Clear_display 				 0x01
	#define Return_home 				 0x02
	#define Entry_mode_set 				 0x06
	#define Display_OFF_Control		     0x08
	#define Display_ON_Control		     0x0C
	#define Cursor_or_Display_Shift		 0x80
	#define lcd_FunctionReset  			 0x30
	#define lcd_FunctionSet8bit 		 0x38
*/
void void_LCDWriteData	(u8 copy_Data){
	/* Set RS to HIGH */
	SET_BIT(LCD_CONTROL_PORT,RS_pin);
	/* Set R/W to LOW */
	CLR_BIT(LCD_CONTROL_PORT,RW_pin);
	/* Set E to HIGH */
	SET_BIT(LCD_CONTROL_PORT,E_pin);
	/*set data*/
	LCD_Data_PORT=copy_Data;
	_delay_ms(5);
	/* Set E to LOW */
	CLR_BIT(LCD_CONTROL_PORT,E_pin);
	/* Delay for 10ms to save data*/
	_delay_ms(10);


}
/***************************************************************************************/
/* Description! Interface to send the configuration commands to the LCD Driver         */
/* Input      ! Command number                                                         */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void void_LCDWriteCmd	(u8 copy_command){
	/* Set RS to HIGH */
	CLR_BIT(LCD_CONTROL_PORT,RS_pin);
	/* Set R/W to LOW */
	CLR_BIT(LCD_CONTROL_PORT,RW_pin);
	/* Set E to HIGH */
	SET_BIT(LCD_CONTROL_PORT,E_pin);
	/*set data*/
	LCD_Data_PORT= copy_command;
	_delay_ms(5);
	/* Set E to LOW */
	CLR_BIT(LCD_CONTROL_PORT,E_pin);
	/* Delay for 10ms to do command*/
	_delay_ms(10);
}
void void_LCDini	(void){
	 LCD_Data_PORT_DDR=0xFF;
	 SET_BIT(LCD_CONTROL_PORT_DDR,RS_pin);
	 SET_BIT(LCD_CONTROL_PORT_DDR,RW_pin);
	 SET_BIT(LCD_CONTROL_PORT_DDR,E_pin);
	 //inti:
	 _delay_ms(30);
	 void_LCDWriteCmd(lcd_FunctionSet8bit);
	 _delay_ms(1);
	 void_LCDWriteCmd(Display_ON_Control);
	 _delay_ms(1);
	 void_LCDWriteCmd(Clear_display);
	 _delay_ms(2);
	 void_LCDWriteCmd(Entry_mode_set);
}
void void_LCDSetCursorLocation(u8 copy_u8Row,u8 copy_u8column){

	u8 command=127;
	if(copy_u8column>=1&&copy_u8column<=16){
		switch(copy_u8Row){
		case 1:
			command+=copy_u8column;
			break;
		case 2:
			command+=copy_u8column+64;
			break;
		default:break;
		}
		void_LCDWriteCmd(command);
	}
	else{

	}
}
 void void_LCDWriteString(u8 * string){
	 u8 counter=0;
	 for(counter=0;string[counter]!='\0';counter++){
		 void_LCDWriteData(string[counter]);
		 _delay_ms(2);
	 }
 }
 void void_LCDSaveCustomChar(u8 arr_data[],u8 copy_location){
	 u8 address=0;
	 u8 counter;
	 if(copy_location>=1&&copy_location<=8){
		 address=(copy_location-1)*8;
		 SET_BIT(address,6);
		 void_LCDWriteCmd(address);
		 for(counter=0;counter<8;counter++){
			 void_LCDWriteData(arr_data[counter]);
			 _delay_ms(2);
		 }
		 void_LCDSetCursorLocation(1,1);
	 }

 }
