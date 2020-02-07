/*
 Name:		VCNL4100.h
 Created:	07.02.2020 18:47:43
 Author:	VSGagarski
 Editor:	http://www.visualmicro.com
*/

#ifndef _VCNL4100_h
#define _VCNL4100_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

#endif
#include"stdint.h"

//Register declarations
#define VCNL4100_I2CADDR 0x60
#define VCNL4100_ALS_CONF_REG 0x00
#define VCNL4100_ALS_THDH_REG 0x01 //Ambient Light Sensor Threshold Data High
#define VCNL4100_ALS_THDL_REG 0x02 //Ambient Light Sensor Threshold Data Low
#define VCNL4100_PS_CONF1_CONF2_REG 0x03
#define VCNL4100_PS_CONF3_MS_REG 0x04 //Conf3 and Mode Select
#define VCNL4100_PS_CANC_REG 0x05
#define VCNL4100_PS_THDL_REG 0x06 //Proximity Sensor Threshold Data Low
#define VCNL4100_PS_THDH_REG 0x07 //Proximity Sensor Threshold Data High
#define VCNL4100_PROXIMITY_REG 0x08
#define VCNL4100_AMBIENT_REG 0x09
#define VCNL4100_WHITE_REG 0x0A
#define VCNL4100_INT_FLAG_REG 0x0B


//Ambient Light Sensor Shut Down
typedef enum {
	VCNL4200_ALS_Shutdown_on = 0,
	VCNL4200_ALS_Shutdown_off = 1
} VCNL4100_ALS_Shutdown;

//Ambient Light Sensor Interrupt
typedef enum {
	VCNL4200_ALS_Interrupt_disable = 0,
	VCNL4200_ALS_Interrupt_enable = 2
} VCNL4100_ALS_Interrupt;

//Ambient Light Persistence Setting
typedef enum {
	VCNL4200_ALS_Pers_one = 0,
	VCNL4200_ALS_Pers_two = 4,
	VCNL4200_ALS_Pers_four = 8,
	VCNL4200_ALS_Pers_eight = 12
} VCNL4100_ALS_Pers;

//Ambient Light Sensor Interrupt
typedef enum {
	VCNL4200_ALS_INT_SWITCH_als = 0,
	VCNL4200_ALS_INT_SWITCH_white = 32
} VCNL4100_ALS_INT_SWITCH;

//Ambient Light Sensor Integration Time in Milliseconds
typedef enum {
	VCNL4200_ALS_IT_ms80 = 0,
	VCNL4200_ALS_IT_ms160 = 64,
	VCNL4200_ALS_IT_ms320 = 128,
	VCNL4200_ALS_IT_ms640 = 192
} VCNL4100_ALS_IT;


class VCNL4100 {
public:
	VCNL4100();
	boolean exists();
	boolean initialize();

	//Edit the binary settings here to change default startup options
	boolean set_ALS_CONF(uint8_t c1 = B00000000);
	boolean set_PS_CONF1_CONF2(uint8_t c1 = B11111100, uint8_t c2 = B11110000);
	boolean set_PS_CONF3_MS(uint8_t c3 = B00000000, uint8_t m = 0xA0);

	uint16_t getProximity();
	uint16_t getAmbient();

	uint16_t getProxInterrupt();
	uint8_t getInterruptFlag();

private:
	uint8_t _i2caddr;
	void write8(uint8_t address, uint8_t data);
	uint8_t write16_LowHigh(uint8_t address, uint8_t low, uint8_t high);
	uint8_t readData8(uint8_t command_code);
	uint16_t readData(uint8_t command_code);
};