#include <avr/io.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "ADC.h"

void ADC_init(){
	ADMUX = 0;
	SET_BIT(ADCSRA, ADEN);
}

u16 ADC_read(u8 bit_num){
	ADMUX = (ADMUX & 0xF8) | (bit_num & 0x07);
	SET_BIT(ADCSRA,ADSC);
	while(GET_BIT(ADCSRA,ADIF)==0);
	return ADCL | (ADCH << 8);
}
