/*
 * ModuleTemperature.h
 *
 *  Created on: 23 nov. 2024
 *      Author: mlabe
 */

#ifndef MODULETEMPERATURE_H_
#define MODULETEMPERATURE_H_

#define LPI2C_BASE_TEMP LPI2C1
#define	I2C_BUFFER_LEN 25

void initLPI2C1();
void initBMP();
double getTemp();
int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t spi_reg_write(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t spi_reg_read(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
void print_rslt(const char api_name[], int8_t rslt);

#endif /* MODULETEMPERATURE_H_ */
