#pragma once
#include "Arduino.h"
#include <Wire.h>
#include "TCA9548.h"
// #define BH1750_DEBUG //BH1750 API Debug
// No active state
#define BH1750_POWER_DOWN 0x00
// Wating for measurement command
#define BH1750_POWER_ON 0x01
// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_RESET 0x07

class BH1750 :public TCA9548
{
public:
	enum Mode
	{
		UNCONFIGURED = 0,
		// Measurement at 1lx resolution. Measurement time is approx 120ms.
		CONTINUOUS_HIGH_RES_MODE = 0x10,
		// Measurement at 0.5lx resolution. Measurement time is approx 120ms.
		CONTINUOUS_HIGH_RES_MODE_2 = 0x11,
		// Measurement at 4lx resolution. Measurement time is approx 16ms.
		CONTINUOUS_LOW_RES_MODE = 0x13,
		// Measurement at 1lx resolution. Measurement time is approx 120ms.
		ONE_TIME_HIGH_RES_MODE = 0x20,
		// Measurement at 0.5lx resolution. Measurement time is approx 120ms.
		ONE_TIME_HIGH_RES_MODE_2 = 0x21,
		// Measurement at 1lx resolution. Measurement time is approx 120ms.
		ONE_TIME_LOW_RES_MODE = 0x23
	};
	BH1750(uint8_t device_id,byte addr = 0x23);
	bool begin(Mode mode = CONTINUOUS_HIGH_RES_MODE);
	bool configure(Mode mode);
	uint16_t read_level(bool maxWait = false);
	virtual ~BH1750();
	TCA9548 * tca_com = new TCA9548;
private:
	uint8_t _dev_id;
	uint8_t _dev_ch;
	int BH1750_I2CADDR;
	Mode BH1750_MODE = UNCONFIGURED;
};

