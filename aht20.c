/*
 * aht20.c
 *
 *  Created on: Dec 21, 2024
 *      Author: Vladimir
 */

#include "aht20.h"
#define AHT_ADDR    (0x38 << 1)  // AHT20 I2C address
#define HI2C         hi2c1        // I2C handle

void AHT20_Read(float* Temp, float* Humid)
{
    uint8_t dum[6];

    // Check if the sensor is ready for operation
    HAL_I2C_Mem_Read(&HI2C, AHT_ADDR, 0x71, 1, dum, 1, 100);

    // If the sensor is not initialized, initialize it
    if (!(dum[0] & (1 << 3)))
    {
        dum[0] = 0xBE;  // Command to initialize the sensor
        dum[1] = 0x08;  // Command to configure the sensor
        dum[2] = 0x00;  // No options
        HAL_I2C_Master_Transmit(&HI2C, AHT_ADDR, dum, 3, 100);
        HAL_Delay(10);   // Wait for initialization to complete
    }

    // Trigger the measurement
    dum[0] = 0xAC;  // Command to start measurement
    dum[1] = 0x33;  // Argument for the command
    dum[2] = 0x00;  // No options
    HAL_I2C_Master_Transmit(&HI2C, AHT_ADDR, dum, 3, 100);
    HAL_Delay(80);   // Wait for the measurement to be completed

    // Wait for measurement to be ready
    do {
        HAL_I2C_Mem_Read(&HI2C, AHT_ADDR, 0x71, 1, dum, 1, 100);
        HAL_Delay(1);
    } while (dum[0] & (1 << 7));  // Check the sensor status

    // Read the measurement data
    HAL_I2C_Master_Receive(&HI2C, AHT_ADDR, dum, 6, 100);

    // Parse the humidity and temperature data
    uint32_t h20 = (dum[1] << 12) | (dum[2] << 4) | (dum[3] >> 4);
    uint32_t t20 = ((dum[3] & 0x0F) << 16) | (dum[4] << 8) | dum[5];

    // Calculate temperature and humidity
    *Temp = (t20 / 1048576.0) * 200.0 - 50.0;
    *Humid = h20 / 10485.76;
}

