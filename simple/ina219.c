#include "ina219.h"

static void INA219_WriteRegister(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t value) {
    uint8_t data[3];
    data[0] = reg;
    data[1] = value >> 8;
    data[2] = value & 0xFF;
    HAL_I2C_Master_Transmit(hi2c, INA219_ADDR, data, 3, HAL_MAX_DELAY);
}

static uint16_t INA219_ReadRegister(I2C_HandleTypeDef *hi2c, uint8_t reg) {
    uint8_t data[2];
    HAL_I2C_Master_Transmit(hi2c, INA219_ADDR, &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(hi2c, INA219_ADDR, data, 2, HAL_MAX_DELAY);
    return (data[0] << 8) | data[1];
}

void INA219_Init(I2C_HandleTypeDef *hi2c){
	// Configuration: 32V range, 320mV shunt, 12-bit ADC, continuous mode
	    INA219_WriteRegister(hi2c, INA219_REG_CONFIG, 0x399F);

	    // Calibration value (for ~0.1 ohm shunt, ~3.2A max)
	    INA219_WriteRegister(hi2c, INA219_REG_CALIBRATION, 4096);
}

int16_t INA219_ReadShuntVoltage(I2C_HandleTypeDef *hi2c) {
    return (int16_t)INA219_ReadRegister(hi2c, INA219_REG_SHUNT_VOLTAGE);
}

uint16_t INA219_ReadBusVoltage(I2C_HandleTypeDef *hi2c) {
    uint16_t raw = INA219_ReadRegister(hi2c, INA219_REG_BUS_VOLTAGE);
    return (raw >> 3) * 4;  // in mV
}

int16_t INA219_ReadCurrent(I2C_HandleTypeDef *hi2c) {
    return (int16_t)INA219_ReadRegister(hi2c, INA219_REG_CURRENT);
}

