#include <stdio.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "fsl_debug_console.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

#include "ModuleDEL.h"
#include "ModuleLCD.h"
#include "ModuleVentilateur.h"
#include "ModuleTemperature.h"

volatile uint32_t g_systickCounter;

//Constantes de seuil
const int SEUILSUPERIEUR = 26;
const int SEUILINFERIEUR = 25;


int main(void) {

	//Initialiser le matériel
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();

	/* Set systick reload value to generate 1ms interrupt */
	if (SysTick_Config(SystemCoreClock / 1000U))
	{
	 PRINTF("Echec dans l'initialisation du systick\n");
	}

	//initialiser les différents composants
	initDEL();
	initVentilateur();
	initLCD();
	initBMP();

	// Ouvrir le backlight
	backlight();

	//avoir toutes les DELs éteintes sauf la bleue
	eteindreDELverte();
	eteindreVentilateur();
	eteindreDELrouge();
	allumerDELbleue();

	bool etat = 0; //0 = normal, 1=actif

	while(1){
		//récupérer la température
		double temp = getTemp();

		//écrire la température à l'écran LCD
		ecrireTemp(temp);

		//si le seuil est dépassé en état normal
		if (temp >= SEUILSUPERIEUR && !etat){
			eteindreDELbleue();
			allumerDELrouge();
			allumerVentilateur();
			allumerDELverte();
			etat = 1;
		}

		//si la température est sous le seuil inférieur en état activé
		else if (temp < SEUILINFERIEUR && etat){
			eteindreDELverte();
			eteindreVentilateur();
			eteindreDELrouge();
			allumerDELbleue();
			etat = 0;
		}

		//Si la température est sous le seuil mais ne dépasse pas la zone tampon
		else if (temp < SEUILSUPERIEUR && etat){
			eteindreDELrouge();
		}

		//Si la température est au-dessus du seuil
		else if (etat){
			allumerDELrouge();
		}

		delay_ms(1000); //attendre 1s pour permettre à l'écran d'afficher
	}

	return 0 ;
}
