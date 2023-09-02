/*
 * KEY_PAD.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Modern Computer
 */

#ifndef KEY_PAD_H_
#define KEY_PAD_H_


#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7

#define KEY_PORT 		PORTC
#define KEY_PORT_PIN	PINC
#define KEY_PORT_DDR	DDRC
/*
 * P0->R0
 * P1->R1
 * P2->R2
 * P3->R3
 * P4->C0
 * P5->C1
 * P6->C2
 * P7->C3
 *
 */
#define ROW_PIN0 	PIN0
#define ROW_PIN1 	PIN1
#define ROW_PIN2 	PIN2
#define ROW_PIN3 	PIN3
#define clom_PIN0 	PIN4
#define clom_PIN1 	PIN5
#define clom_PIN2 	PIN6
#define clom_PIN3 	PIN7


u8 KeyPad_u8ReadInput(void);
void KeyPad_voidinit(void);

#endif /* KEY_PAD_H_ */
