
#include <avr/io.h>
#include <avr/delay.h>
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "KEY_PAD.h"

u8 array_Switch[4][4] = {
		{'7','4','1','N'},
		{'8','5','2','0'},
		{'9','6','3','='},
        {'/','*','-','+'}
};


static u8 ROWS[4] = {ROW_PIN0,ROW_PIN1,ROW_PIN2,ROW_PIN3};
static u8 CLOMS[4] = {clom_PIN0,clom_PIN1,clom_PIN2,clom_PIN3};

u8 KeyPad_u8ReadInput(void){
u8 inner_counter=0;
u8 outer_counter=0;
	for(outer_counter=0;outer_counter<4;outer_counter++){
		CLR_BIT(KEY_PORT,ROWS[outer_counter]);
		for(inner_counter=0;inner_counter<4;inner_counter++){
			if(GET_BIT(KEY_PORT_PIN,CLOMS[inner_counter])==0){
				//_delay_ms(50); //deb
				while(GET_BIT(KEY_PORT_PIN,CLOMS[inner_counter])==0);
				SET_BIT(KEY_PORT,ROWS[outer_counter]);
				return array_Switch[inner_counter][outer_counter] ;
			}
		}
		SET_BIT(KEY_PORT,ROWS[outer_counter]);

	}
	return '\0';
}

void KeyPad_voidinit(void){
	u8 counter=0;
	for(counter=0;counter<4;counter++){
	//Set ROWS as O/P
		SET_BIT(KEY_PORT_DDR,ROWS[counter]);
	//Set CLOMS as I/P
		CLR_BIT(KEY_PORT_DDR,CLOMS[counter]);
	}
	KEY_PORT=0xFF;
}




