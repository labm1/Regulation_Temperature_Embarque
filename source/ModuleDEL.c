/*
 * ModuleDEL.c
 *
 *  Created on: 31 oct. 2024
 *      Author: mlabe
 */
#include "ModuleDEL.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL28Z7.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#define DEL_ROUGE 2U
#define DEL_BLEUE 1U
#define DEL_VERTE 3U

void initDEL() {
	CLOCK_EnableClock(kCLOCK_PortD);	//initialiser l'horloge du port D

	PORT_SetPinMux(PORTD, DEL_ROUGE, kPORT_MuxAsGpio);	//initialiser les GPIO
	PORT_SetPinMux(PORTD, DEL_BLEUE, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, DEL_VERTE, kPORT_MuxAsGpio);

	GPIOD->PDDR |= (1U << DEL_ROUGE);	//initialiser en tant de sortie
	GPIOD->PDDR |= (1U << DEL_BLEUE);
	GPIOD->PDDR |= (1U << DEL_VERTE);

	GPIOD->PCOR |= (1U << DEL_ROUGE);	//mettre les DEL éteintes
	GPIOD->PCOR |= (1U << DEL_BLEUE);
	GPIOD->PCOR |= (1U << DEL_VERTE);
}

void allumerDELrouge(){
	GPIOD->PSOR |= (1U << DEL_ROUGE);
}
void allumerDELverte(){
	GPIOD->PSOR |= (1U << DEL_VERTE);
}
void allumerDELbleue(){
	GPIOD->PSOR |= (1U << DEL_BLEUE);
}

void eteindreDELrouge(){
	GPIOD->PCOR |= (1U << DEL_ROUGE);
}
void eteindreDELverte(){
	GPIOD->PCOR |= (1U << DEL_VERTE);
}
void eteindreDELbleue(){
	GPIOD->PCOR |= (1U << DEL_BLEUE);
}
