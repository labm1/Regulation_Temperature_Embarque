#ifndef MODULELCD_H
#define MODULELCD_H

#include <stdint.h>
#include "delay/delay.h"
#include <fsl_lpi2c.h>

#define LPI2C_BASE_LCD LPI2C0

#define true 1
#define false 0

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100  // Enable bit
#define Rw 0b00000010  // Read/Write bit
#define Rs 0b00000001  // Register select bit

#define lcd_addr 		0x27  			// I2C slave address of the LCD display. Most likely printed on the
	 									// LCD circuit board, or look in the supplied LCD documentation.
#define lcd_cols 		20   			// Number of columns your LCD display has
#define lcd_rows		4				// Number of rows your LCD display has.
#define charsize		LCD_5x8DOTS 	//The size in dots that the display has, use LCD_5x10DOTS or LCD_5x8DOTS


//commandes d'initialisation
void initLPI2C0();
void initLCD();
void ecrireTemp(double temp);

void clear();
void home();

void noBacklight();
void backlight();
uint8_t getBacklight();
void display();

void setCursor(uint8_t, uint8_t);
int write(uint8_t);
void command(uint8_t);

void send(uint8_t, uint8_t);
void write4bits(uint8_t);
status_t expanderWrite(uint8_t);
void pulseEnable(uint8_t);
uint8_t print(const char *);
int printString(const char *, uint8_t);


#endif // MODULELCD_H
