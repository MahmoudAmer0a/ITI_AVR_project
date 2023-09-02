/*
 * LCD.h
 *
 *  Created on: Aug 13, 2023
 *      Author: eng_youssef_goher
 */

#ifndef LCD_H_
#define LCD_H_

#define Clear_display 				 0x01
#define Return_home 				 0x02
#define Entry_mode_set 				 0x06
#define Display_OFF_Control		     0x08
#define Display_ON_Control		     0x0C
#define Cursor_or_Display_Shift		 0x80
#define lcd_FunctionReset  			 0x30
#define lcd_FunctionSet8bit 		 0x38

#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7

#define LCD_Data_PORT			PORTA
#define LCD_CONTROL_PORT 		PORTB
#define LCD_Data_PORT_DDR		DDRA
#define LCD_CONTROL_PORT_DDR	DDRB

#define RS_pin				PIN0
#define RW_pin				PIN1
#define E_pin				PIN2

void void_LCDWriteData	(u8 copy_Data);
void void_LCDWriteCmd	(u8 copy_command);
void void_LCDini	(void);
void void_LCDSetCursorLocation(u8 copy_u8Row,u8 copy_u8column);
void void_LCDWriteString(u8 * string);
void void_LCDSaveCustomChar(u8 arr_data[],u8 copy_location);

#endif /* LCD_H_ */
