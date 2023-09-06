
#include <avr/io.h>
#include<avr/delay.h>
#include <avr/interrupt.h>

#include "HAL/LCD/LCD.h"
#include "HAL/KEY_PAD/KEY_PAD.h"
#include "MCAL/SPI/SPI.h"
#include "MCAL/ADC/ADC.h"

#include "FreeRTOS.h"
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "task.h"
#include "FreeRTOSConfig.h"


u8 Door_counter = 0 ;
u8 BUZ_Enable 	= 0 ;
u8 BUZ_Count	= 0 ;

u8 Gas_Value 	= 0 ;

//void BUZ1(void * pvParameters);
void LDR (void * pvParameters);
void Temp(void * pvParameters);
void Gas (void * pvParameters);

BaseType_t xReturnedLDRTask,xReturnedTempTask,xReturnedGasTask,xReturnedBUZ1Task;

TaskHandle_t LDR_Handle 	= NULL ;
TaskHandle_t Temp_Handle 	= NULL ;
TaskHandle_t Gas_Handle 	= NULL ;
TaskHandle_t BUZ1_Handle 	= NULL ;

//ADC Settings
u32 LED_Digital_value = 0;
u8 temp = 0;
u32 analog_value = 0;

u8 vref = 5;
const f32 step_size = 4.8828125 ; //vref * 1000 / 1024.0;

//Slave MC


void main(){

	//SPI
	u8 Data = 0 ;
	SPI_voidInit(Slave);
	SET_BIT(DDRB,0);
	//ADC Setting


	//ADC PINS
	CLR_BIT(DDRA, 1);
	SET_BIT(DDRA, 2);
	CLR_BIT(DDRA, 4);
	SET_BIT(DDRA, 5);
	DDRC = 0xFF;
	DDRD = 0xFF;
	ADC_init();

	//APP

	while(Data == 0){
		Data = SPI_u8transcieve(1);
	}
	if(Data != 0 ){
		BUZ_Enable = 0 ;
	}


	xReturnedTempTask = xTaskCreate(Temp ,"Temp",configMINIMAL_STACK_SIZE,NULL,1	,&Temp_Handle);
	xReturnedLDRTask = xTaskCreate(LDR ,"LDR",configMINIMAL_STACK_SIZE,NULL,1	,&LDR_Handle);
	//xReturnedGasTask = xTaskCreate(Gas  ,"Gas",configMINIMAL_STACK_SIZE,NULL,1		,&Gas_Handle);
	//xReturnedBUZ1Task = xTaskCreate(BUZ1 ,"BUZ1",configMINIMAL_STACK_SIZE,NULL,1	,&BUZ1_Handle);

	vTaskStartScheduler();

	while(1){}
}

//void BUZ1(void * pvParameters){
//
//    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
//	SET_BIT(DDRB,0);
//    for( ;; )
//    {
//
//    	if(BUZ_Enable != 0){
//    		TOG_BIT(PORTB , PIN0);
//			vTaskDelay(1000);
//    	}
//	}
//}




void Temp(void * pvParameters){
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	SET_BIT(DDRA, 5);
	SET_BIT(DDRB,0);
    for( ;; )
    {
    	Gas_Value		= ADC_read(1);
    	LED_Digital_value = ADC_read(4);
    	analog_value = ADC_read(0) * step_size;
    	temp = analog_value /10;
    	if (temp > 29 && temp < 50){
    		SET_BIT(PORTA, 5); // air cond.
    		CLR_BIT(PORTB, 0); //BUZZER
    	}else if(temp >= 50){

        	SET_BIT(PORTB , PIN0);

    		CLR_BIT(PORTA, 5);
    	}
    	else{
    		CLR_BIT(PORTA, 5);

    	}

    	}
    vTaskDelay(250);
    }


void LDR (void * pvParameters){
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	SET_BIT(DDRD , PIN3);
	SET_BIT(DDRD , PIN4);
	SET_BIT(DDRD , PIN5);

    for( ;; )
    {
    	// LDR condition

    	if (LED_Digital_value > 1000){
    		CLR_BIT(PORTD, 3);
    		CLR_BIT(PORTD, 4);
   			CLR_BIT(PORTD, 5);
    	}else if (LED_Digital_value > 800){
    		CLR_BIT(PORTD, 3);
   			CLR_BIT(PORTD, 4);
   			SET_BIT(PORTD, 5);
    	}else if (LED_Digital_value > 300){
    		CLR_BIT(PORTD, 3);
    		SET_BIT(PORTD, 4);
    		SET_BIT(PORTD, 5);
   		}else{
    		SET_BIT(PORTD, 3);
    		SET_BIT(PORTD, 4);
    		SET_BIT(PORTD, 5);
   		}
    vTaskDelay(250);
    }

}


void Gas (void * pvParameters){
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	SET_BIT(DDRC , PIN2);//output
	CLR_BIT(DDRA , PIN1);//input
	SET_BIT(DDRC, PIN0);

	for( ;; )
    {
		//
    	if (GET_BIT(PINA, 1) == 1){
    		SET_BIT(PORTC , 2);
    		//SET_BIT(PORTA, 2);
    	}
    	else{
    		CLR_BIT(PORTC , 2);
    		//CLR_BIT(PORTA, 2);
    		TOG_BIT(PORTC,PIN0);
    	}
    vTaskDelay(250);
    }

}






















