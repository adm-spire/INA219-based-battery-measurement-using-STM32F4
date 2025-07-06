#ifndef INA219_H
#define INA219_H

#include "stm32f4xx_hal.h"

#define INA219_ADDR (0x40 << 1)  // Default I2C address shifted for HAL
#define INA219_REG_CALIBRATION 0x05
#define INA219_REG_CONFIG 0x00
#define INA219_REG_SHUNT_VOLTAGE 0x01
#define INA219_REG_BUS_VOLTAGE 0x02
#define INA219_REG_CURRENT 0x04
#define INA219_REG_POWER 0x03

void INA219_Init(I2C_HandleTypeDef *hi2c);
float INA219_ReadShuntVoltage(I2C_HandleTypeDef *hi2c);
uint16_t INA219_ReadBusVoltage(I2C_HandleTypeDef *hi2c);
float INA219_ReadCurrent(I2C_HandleTypeDef *hi2c);
float INA219_ReadPower(I2C_HandleTypeDef *hi2c);

#endif