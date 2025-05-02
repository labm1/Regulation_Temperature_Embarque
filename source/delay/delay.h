/*
 * delay.h
 *
 *  Created on: Apr. 9, 2021
 *      Author: kameladi
 */

#include "stdint.h"

#ifndef DELAY_DELAY_H_
#define DELAY_DELAY_H_

void SysTick_Handler(void);
void SysTick_DelayTicks(uint32_t n);
void delayMicroseconds(uint32_t);
void delay_ms(uint32_t);


#endif /* DELAY_DELAY_H_ */
