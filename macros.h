/*
 * macros.h
 *
 *  Created on: 10 Sep 2022
 *      Author: Hassan Ghandoor
 */

#ifndef MACROS_H_
#define MACROS_H_
#define SET_BIT(VAR,BITNO) ((VAR)|=(1<<(BITNO)))
#define CLR_BIT(VAR,BITNO) ((VAR)&=~(1<<(BITNO)))
#define TOGGLE_BIT(VAR,BITNO) ((VAR)^=(1<<(BITNO)))
#define GET_BIT(VAR,BITNO) (((VAR)>>(BITNO))&0x01)

#endif /* MACROS_H_ */
