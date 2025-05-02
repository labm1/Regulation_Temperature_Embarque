#include <stdio.h>
#include <math.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL28Z7.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_lpi2c.h"
#include "bmp280.h"
#include "ModuleTemperature.h"
#include "delay/delay.h"

struct bmp280_dev bmp;


void initLPI2C1(){
    //Activer les Horloges
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_Lpi2c1);

	//Activer les ports
	PORT_SetPinMux(PORTC, 1U, kPORT_MuxAlt2); //SCL LPI2C1 -> PTC1
	PORT_SetPinMux(PORTC, 2U, kPORT_MuxAlt2); //SDA LPI2C1 -> PTC2

	//Configuration LPI2C
	lpi2c_master_config_t sConfig;
	LPI2C_MasterGetDefaultConfig(&sConfig);
	sConfig.enableMaster = true;
	sConfig.baudRate_Hz= 100000U;
	LPI2C_MasterInit(LPI2C_BASE_TEMP, &sConfig, CLOCK_GetFreq(kCLOCK_Osc0ErClk));
}

void initBMP(){
	initLPI2C1();

	int8_t rslt;
    struct bmp280_config conf;

	/* Map the delay function pointer with the function responsible for implementing the delay */
	    bmp.delay_ms = delay_ms;

	    /* Assign device I2C address based on the status of SDO pin (GND for PRIMARY(0x76) & VDD for SECONDARY(0x77)) */
	    bmp.dev_id = BMP280_I2C_ADDR_PRIM; //BMP280_I2C_ADDR_PRIM;

	    /* Select the interface mode as I2C */
	    bmp.intf = BMP280_I2C_INTF;

	    /* Map the I2C read & write function pointer with the functions responsible for I2C bus transfer */
	    bmp.read = i2c_reg_read;
	    bmp.write = i2c_reg_write;


	    rslt = bmp280_init(&bmp);// appelez la fonction bmp180_init en lui passant comme paramètre l'adresse de la variable bmp_180;

	    print_rslt(" bmp280_init status", rslt);

	    /* Always read the current settings before writing, especially when
	     * all the configuration is not modified
	     */
	    rslt = bmp280_get_config(&conf, &bmp);
	    print_rslt(" bmp280_get_config status", rslt);

	    /* configuring the temperature oversampling, filter coefficient and output data rate */
	    /* Overwrite the desired settings */
	    conf.filter = BMP280_FILTER_COEFF_2;

	    /* Temperature oversampling set at 4x */
	    conf.os_temp = BMP280_OS_4X;

	    /* Pressure over sampling none (disabling pressure measurement) */
	    conf.os_pres = BMP280_OS_NONE;

	    /* Setting the output data rate as 1HZ(1000ms) */
	    conf.odr = BMP280_ODR_1000_MS;
	    rslt = bmp280_set_config(&conf, &bmp);
	    print_rslt(" bmp280_set_config status", rslt);

	    /* Always set the power mode after setting the configuration */
	    rslt = bmp280_set_power_mode(BMP280_NORMAL_MODE, &bmp);
	    print_rslt(" bmp280_set_power_mode status", rslt);
}

double getTemp(){
    struct bmp280_uncomp_data ucomp_data;
    double temp;

	/* Reading the raw data from sensor */
	bmp280_get_uncomp_data(&ucomp_data, &bmp);// Appeler la fonction bmp280_get_uncomp_data(...) pour lire la valeur de température non compensée.

	/* Getting the compensated temperature as floating point value */
	bmp280_get_comp_temp_double(&temp, ucomp_data.uncomp_temp, &bmp);

	return temp;
}

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[in] reg_data : Pointer to the data buffer whose value is to be written.
 *  @param[in] length   : No of bytes to write.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
		uint32_t iError = 0;
		uint8_t array[I2C_BUFFER_LEN]= {0};
		uint8_t stringpos = 0;
		array[0] = reg_addr;


		lpi2c_master_transfer_t masterXfer;
	    memset(&masterXfer, 0, sizeof(masterXfer));

		masterXfer.slaveAddress   = i2c_addr;
		masterXfer.direction      = kLPI2C_Write;
		masterXfer.subaddress     = reg_addr;
		masterXfer.subaddressSize = 1;
		masterXfer.data           = &array[0];
		masterXfer.dataSize       = length;
		masterXfer.flags          = kLPI2C_TransferDefaultFlag;

		// Appeler la fonction  I2C_MasterTransferBlocking(...) de la librairie fsl_i2c
	    // iError = I2C_MasterTransferBlocking(...)

		// transférer les données de reg_data vers array
		for (stringpos = 0; stringpos < length; stringpos++) {
			array[stringpos] = *(reg_data + stringpos);
		}

		iError = LPI2C_MasterTransferBlocking(LPI2C_BASE_TEMP, &masterXfer);
		return (uint8_t)iError;
}

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : Sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length   : No of bytes to read.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

		uint32_t iError = 0;
		uint8_t array[I2C_BUFFER_LEN] = {0};
		uint8_t stringpos = 0;
		array[0] = reg_addr;
		lpi2c_master_transfer_t masterXfer;

		memset(&masterXfer, 0, sizeof(masterXfer));
		masterXfer.slaveAddress   = i2c_addr;
		masterXfer.direction      = kLPI2C_Read;
		masterXfer.subaddress     = reg_addr;
		masterXfer.subaddressSize = 1;
		masterXfer.data           = &array[0];
		masterXfer.dataSize       = length;
		masterXfer.flags          = kLPI2C_TransferDefaultFlag;

		//iError = I2C_MasterTransferBlocking(......, &masterXfer);
		iError = LPI2C_MasterTransferBlocking(LPI2C_BASE_TEMP, &masterXfer);
		// transférez les données de array vers regdata
		for (stringpos = 0; stringpos < length; stringpos++) {
			*(reg_data + stringpos) = array[stringpos];
		}

		return (uint8_t)iError;
}

/*!
 *  @brief Prints the execution status of the APIs.
 *
 *  @param[in] api_name : name of the API whose execution status has to be printed.
 *  @param[in] rslt     : error code returned by the API whose execution status has to be printed.
 *
 *  @return void.
 */
void print_rslt(const char api_name[], int8_t rslt)
{
    if (rslt != BMP280_OK)
    {
        PRINTF("%s\t", api_name);
        if (rslt == BMP280_E_NULL_PTR)
        {
            PRINTF("Error [%d] : Null pointer error\r\n", rslt);
        }
        else if (rslt == BMP280_E_COMM_FAIL)
        {
            PRINTF("Error [%d] : Bus communication failed\r\n", rslt);
        }
        else if (rslt == BMP280_E_IMPLAUS_TEMP)
        {
            PRINTF("Error [%d] : Invalid Temperature\r\n", rslt);
        }
        else if (rslt == BMP280_E_DEV_NOT_FOUND)
        {
            PRINTF("Error [%d] : Device not found\r\n", rslt);
        }
        else
        {
            /* For more error codes refer "*_defs.h" */
            PRINTF("Error [%d] : Unknown error code\r\n", rslt);
        }
    }
}
