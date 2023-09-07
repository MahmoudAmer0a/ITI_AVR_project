
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

void vLDRTaskCode (void * pvParameters);
void vTempTaskCode(void * pvParameters);
void vGasTaskCode (void * pvParameters);

BaseType_t xLDRTask,xTempTask,xGasTask;

TaskHandle_t LDR_Handle 	= NULL ;
TaskHandle_t Temp_Handle 	= NULL ;
TaskHandle_t Gas_Handle 	= NULL ;
TaskHandle_t BUZ1_Handle 	= NULL ;

//ADC Settings
u32 LED_Digital_value = 0;
u8 Current_Temp = 0;
u32 analog_value = 0;

u8 Data = 0; // SPI

u8 vref = 5;
const f32 step_size = 4.8828125 ; //vref * 1000 / 1024.0;

void main(){

	SPI_voidInit(Slave);

	ADC_init();

	//APP
	while(Data == 0){
		Data = SPI_u8transcieve(1);
	}
	if(Data != 0 ){
		BUZ_Enable = 0 ;
	}

	xTempTask = xTaskCreate(vTempTaskCode ,"Temperature",configMINIMAL_STACK_SIZE,NULL,1,&Temp_Handle);
	xLDRTask = xTaskCreate(vLDRTaskCode ,"LDR",configMINIMAL_STACK_SIZE,NULL,1,&LDR_Handle);

	vTaskStartScheduler();

	while(1);
}

void vTempTaskCode(void * pvParameters){

    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    SET_BIT(DDRB,PIN0); // BUZZER 1
    SET_BIT(DDRA,PIN5); // Air conditioner

    for( ;; )
    {
    	analog_value = ADC_read(0) * step_size;
    	Current_Temp = analog_value /10;
    	if (Current_Temp > 29 && Current_Temp < 50){
    		SET_BIT(PORTA,PIN5); // Start air conditioner
    		CLR_BIT(PORTB, PIN0); // Stop BUZZER
    	}
    	else if (Current_Temp >= 50) {
    		CLR_BIT(PORTA,PIN5); // Stop air conditioner
        	SET_BIT(PORTB , PIN0); // Start BUZZER
    	}
    	else{
    		CLR_BIT(PORTA,PIN5); // Stop air conditioner
    	}
    	vTaskDelay(250);
    	}

    }


void vLDRTaskCode (void * pvParameters){

    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    CLR_BIT(DDRA, PIN4); // ADC

	SET_BIT(DDRD , PIN3);
	SET_BIT(DDRD , PIN4);
	SET_BIT(DDRD , PIN5);

    for( ;; )
    {
    	// LDR condition
    	LED_Digital_value = ADC_read(4);
    	if (LED_Digital_value > 1000){
    		CLR_BIT(PORTD, PIN3);
    		CLR_BIT(PORTD, PIN4);
   			CLR_BIT(PORTD, PIN5);
    	}else if (LED_Digital_value > 800){
    		CLR_BIT(PORTD, PIN3);
   			CLR_BIT(PORTD, PIN4);
   			SET_BIT(PORTD, PIN5);
    	}else if (LED_Digital_value > 300){
    		CLR_BIT(PORTD, PIN3);
    		SET_BIT(PORTD, PIN4);
    		SET_BIT(PORTD, PIN5);
   		}else{
    		SET_BIT(PORTD, PIN3);
    		SET_BIT(PORTD, PIN4);
    		SET_BIT(PORTD, PIN5);
   		}
    vTaskDelay(250);
    }

}

void vGasTaskCode (void * pvParameters){
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    CLR_BIT(DDRA, PIN1);
	SET_BIT(DDRA, PIN2);

	for( ;; )
    {
    	if (GET_BIT(PINA, PIN1) == 1){
    		SET_BIT(PORTA , PIN2);
    	}
    	else{
    		CLR_BIT(PORTA , PIN2);
    	}
    vTaskDelay(250);
    }

}






















