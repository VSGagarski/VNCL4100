/*
 Name:		VCNL4100.cpp
 Created:	07.02.2020 18:47:43
 Author:	VSGagarski
 Editor:	http://www.visualmicro.com
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include <binary.h>
#include <Wire.h>


#include "VCNL4100.h"

VCNL4100::VCNL4100() {
	_i2caddr = VCNL4100_I2CADDR;
}

boolean VCNL4100::initialize() {
	Wire.begin();

	set_ALS_CONF();
	set_PS_CONF1_CONF2();
	set_PS_CONF3_MS();

	//Set the PS interrupt levels
	write16_LowHigh(VCNL4100_PS_THDL_REG, B00010000, B11110000);

	return true;
}

boolean VCNL4100::set_ALS_CONF(uint8_t settingTotal) {
	write16_LowHigh(VCNL4100_ALS_CONF_REG, settingTotal, B00000000);
	return true;
}

boolean VCNL4100::set_PS_CONF1_CONF2(uint8_t conf1, uint8_t conf2) {
	write16_LowHigh(VCNL4100_PS_CONF1_CONF2_REG, conf1, conf2);
	return true;
}

boolean VCNL4100::set_PS_CONF3_MS(uint8_t conf3, uint8_t ms) {
	write16_LowHigh(VCNL4100_PS_CONF3_MS_REG, conf3, ms);
	return true;
}

uint16_t VCNL4100::getProximity() {
	return readData(VCNL4100_PROXIMITY_REG);
}

uint16_t VCNL4100::getProxInterrupt() {
	return readData(VCNL4100_PS_THDL_REG);
}



uint8_t VCNL4100::getInterruptFlag() {
	uint8_t reading;
	reading = readData(VCNL4100_INT_FLAG_REG);
	return reading;
}

uint16_t VCNL4100::getAmbient() {
	return readData(VCNL4100_AMBIENT_REG);
}

uint16_t VCNL4100::readData(uint8_t command_code)
{
	uint16_t reading;

	uint8_t byteLow;
	uint16_t byteHigh;

	Wire.beginTransmission(_i2caddr);
	Wire.write(command_code);
	Wire.endTransmission(false);
	Wire.requestFrom(_i2caddr, uint8_t(2));
	while (Wire.available())
	{
		byteLow = Wire.read();
		//while (!Wire.available());
		byteHigh = Wire.read();
	}
	reading = (byteHigh <<= 8) + byteLow;
	return reading;
}


void VCNL4100::write8(uint8_t address, uint8_t data) //Original
{
	Wire.beginTransmission(_i2caddr);
	Wire.write(address);
	Wire.write(data);
	Wire.endTransmission();
}

uint8_t VCNL4100::write16_LowHigh(uint8_t address, uint8_t low, uint8_t high)
{
	Wire.beginTransmission(_i2caddr);
	Wire.write(address);
	Wire.write(low);
	Wire.write(high);
	Wire.endTransmission();
}
