#include "ModuleLCD.h"
#include "string.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"

uint8_t _displayfunction;
uint8_t _displaycontrol;
uint8_t _displaymode;
uint8_t backlightval = LCD_BACKLIGHT;

//Initialiser le LPI2C
void initLPI2C0(){
	//Activer les Horloges
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_Lpi2c0);

	//Activer les ports
	PORT_SetPinMux(PORTC, 8U, kPORT_MuxAlt2); //SCL LPI2C0 -> PTC8
	PORT_SetPinMux(PORTC, 9U, kPORT_MuxAlt2); //SDA LPI2C0 -> PTC9

	//Configuration LPI2C
	lpi2c_master_config_t sConfig;
	LPI2C_MasterGetDefaultConfig(&sConfig);
	sConfig.enableMaster = true;
	sConfig.baudRate_Hz= 100000U;
	LPI2C_MasterInit(LPI2C_BASE_LCD, &sConfig, CLOCK_GetFreq(kCLOCK_Osc0ErClk));

}

//Initialiser l'écran LCD
void initLCD() {
	initLPI2C0(); //initialiser la communication LPI2C

	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

	if (lcd_rows > 1) {
		_displayfunction |= LCD_2LINE;
	}

	// for some 1 line displays you can select a 10 pixel high font
	if ((charsize != 0) && (lcd_rows == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delay_ms(50);

	// Now we pull both RS and R/W low to begin commands
	expanderWrite(backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
	delay_ms(100);

	//put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46

	// we start in 8bit mode, try to set 4 bit mode
	write4bits(0x03 << 4);
	delay_ms(5); // wait min 4.1ms

	// second try
	write4bits(0x03 << 4);
	delay_ms(5); // wait min 4.1ms

	// third go!
	write4bits(0x03 << 4);
	delay_ms(2);

	// finally, set to 4-bit interface
	write4bits(0x02 << 4);

	// set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);

	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();

	// clear it off
	clear();

	// Initialize to default text direction (for roman languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);

	home();

	print("Temperature:");
	setCursor(2,1);
	print(".");
}

//Fonction pour écrire la température sur l'écran LCD
void ecrireTemp(double temp){
	char strTemp[3];

	//La fonction pour écrire sur l'écran LCD est seulement pour des type char.
	//convertir la température double en char, avant et après la virgule
	strTemp[0] = '0' + ((int) temp / 10);
	strTemp[1] = '0' + ((int) temp) % 10;
	strTemp[2] = '\0';

	char strVirgule[3];
	int virgule = ((int)(temp * 100))%100;

	if (virgule < 10) {	//Pour 1 chiffre après la virgule
		strVirgule[0] = '0';
		strVirgule[1] = '0' + virgule;
		strVirgule[2] = '\0';
	} else {			//Pour 2 chiffres après la virgule
		strVirgule[0] = '0' + virgule / 10;
		strVirgule[1] = '0' + virgule % 10;
		strVirgule[2] = '\0';
	}

	//imprimer la température avant la virgule
	setCursor(0,1);
	print(strTemp);

	//imprimer la température après la virgule
	setCursor(3, 1);
	print(strVirgule);
}

//Effacer tout ce qui est sur l'écran lcd
void clear(){
	command(LCD_CLEARDISPLAY);
	delayMicroseconds(2000);
}

//mettre la position du curseur à zéro
void home(){
	command(LCD_RETURNHOME);
	delayMicroseconds(2000);
}

//mettre le curseur à la position désirée
void setCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40};
	if (row > lcd_rows) {
		row = lcd_rows-1;
	}
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

//activer le display
void display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Fermer le backlight
void noBacklight(void) {
	backlightval = LCD_NOBACKLIGHT;
	expanderWrite(0);
}

// Ouvrir le backlight
void backlight(void) {
	backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}

//Avoir l'état du backlight
uint8_t getBacklight() {
  return backlightval == LCD_BACKLIGHT;
}

//envoyer une commande
void command(uint8_t value) {
	send(value, 0);
}

//envoyer des données
int write(uint8_t value) {
	send(value, Rs);
	return 1;
}

// envoyer une commande ou des données
void send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
	write4bits((highnib)|mode);
	write4bits((lownib)|mode);
}

void write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

//envoyer une commande ou données
status_t expanderWrite(uint8_t _data){

	uint8_t txBuff[1];
	uint8_t status;

	//commencer la communication
	status = LPI2C_MasterStart(LPI2C_BASE_LCD, lcd_addr, kLPI2C_Write);

	/* Wait address sent out. */
	delayMicroseconds(5);

	if(status != kStatus_Success)
	{
	    return status;
	}

	txBuff[0]=(_data | backlightval);

	//données à transférer
	lpi2c_master_transfer_t transfer;
	transfer.slaveAddress = lcd_addr;
	transfer.direction = kLPI2C_Write;
	transfer.subaddress = 0;
	transfer.subaddressSize = 0;
	transfer.data = &txBuff[0];
	transfer.dataSize = sizeof(_data);

	//transférer les données au LCD (Esclave)
	status = LPI2C_MasterTransferBlocking(LPI2C_BASE_LCD, &transfer);

	if(status != kStatus_Success)
		{
		    return status;
		}

		return status;
}

//pour écrire 4 bits
void pulseEnable(uint8_t _data){
	expanderWrite(_data | En);	// En high
	delayMicroseconds(1);		// enable pulse must be >450ns

	expanderWrite(_data & ~En);	// En low
	delayMicroseconds(50);		// commands need > 37us to settle
}


//imprimer une chaine de caractères
uint8_t print(const char * str)
{
 if (str == 0) return 0;
 else return printString((const char *)str, strlen(str));
}


int printString(const char * buffer, uint8_t size)
{
  uint8_t n = 0;
  while (size--)
  {
	  if (write(*buffer++)) n++;
	  else break;
  }
  return n;
}


