/*
 * BIT_MATH.h
 *
 *  Created on: Jul 18, 2022
 *      Author: Youssef
 */

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)

#define SET_REG(reg) 		((reg) =0xFF)
#define CLR_REG(reg) 		((reg) =0x00)
#define TOG_REG(reg) 		((reg) ^=0xFF)
#define GET_REG(reg)		(reg)
#define ASSIGN_REG(reg,vlue) ((reg)=vlue)


#endif /*BIT_MATH_H_ */
