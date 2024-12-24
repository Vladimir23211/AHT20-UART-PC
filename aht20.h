/*
 * aht20.h
 *
 *  Created on: Dec 21, 2024
 *      Author: Vladimir
 */

#ifndef INC_AHT20_H_
#define INC_AHT20_H_

#include "stm32f4xx_hal.h"

// AHT20 constants
#define AHT_ADDR       (0x38 << 1) // AHT20 I2C address in 8-bit format
#define I2C_TIMEOUT    100         // Timeout for I2C operations in ms
#define AHT_INIT_CMD1  0xBE        // Initialization command part 1
#define AHT_INIT_CMD2  0x08        // Initialization command part 2
#define AHT_MEAS_CMD   0xAC        // Command to trigger measurement
#define AHT_MEAS_ARG1  0x33        // Argument for the measurement command

// I2C handle declaration
extern I2C_HandleTypeDef hi2c1;    // Use the I2C handle configured in CubeMX

// Function prototype
void AHT20_Read(float* Temp, float* Humid);


#endif /* INC_AHT20_H_ */
