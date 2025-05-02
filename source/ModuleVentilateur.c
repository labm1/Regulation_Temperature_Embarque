/*
 * ModuleVentilateur.c
 *
 *  Created on: 10 nov. 2024
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

#define VENTILATEUR 7U

void initVentilateur(){
	CLOCK_EnableClock(kCLOCK_PortD);	//initialiser l'horloge du port D

	PORT_SetPinMux(PORTD, VENTILATEUR, kPORT_MuxAsGpio);	//initialiser les GPIO

	GPIOD->PDDR |= (1U << VENTILATEUR);	//initialiser en tant de sortie

	GPIOD->PCOR |= (1U << VENTILATEUR);	//eteindre le ventilateur
}

void allumerVentilateur(){
	GPIOD->PSOR |= (1U << VENTILATEUR);
}

void eteindreVentilateur(){
	GPIOD->PCOR |= (1U << VENTILATEUR);
}
