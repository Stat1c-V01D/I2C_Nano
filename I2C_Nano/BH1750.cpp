#include "BH1750.h"
#include "Arduino.h"
#include <Wire.h>
//TODO: IMPORTANT -- Check for variable range and crank in some limitation and security code
BH1750::BH1750(int device_id, byte addr)
{
	BH1750_I2CADDR = addr;
	_dev_id = device_id;
}


bool BH1750::begin(Mode mode)
{
	// I2C is expected to be initialized outside this library
	// Configure sensor in specified mode
	return configure(mode);
}

bool BH1750::configure(Mode mode)
{
	// default transmission result to a value out of normal range
	byte ack = 0; //TODO: currently set to 0 cause of incomplete code -- see further down
	
	// Check measurement mode is valid
	switch (mode) {

	case BH1750::CONTINUOUS_HIGH_RES_MODE:
	case BH1750::CONTINUOUS_HIGH_RES_MODE_2:
	case BH1750::CONTINUOUS_LOW_RES_MODE:
	case BH1750::ONE_TIME_HIGH_RES_MODE:
	case BH1750::ONE_TIME_HIGH_RES_MODE_2:
	case BH1750::ONE_TIME_LOW_RES_MODE:

		// Send mode to sensor
		tca_com->set_ch(_dev_id);
		_delay_ms(10);
		Wire.beginTransmission(BH1750_I2CADDR);
		Wire.write((uint8_t)BH1750_MODE);
		//TODO: enable ack check on Wire.endTransmission
		Wire.endTransmission();
		tca_com->disable();

		// Wait a few moments to wake up
		_delay_ms(10);
		break;

	default:
		// Invalid measurement mode
		Serial.println(F("[BH1750] ERROR: Invalid mode"));
		break;

	}

	// Check result code
	switch (ack) {
	case 0:
		BH1750_MODE = mode;
		return true;
	case 1: // too long for transmit buffer
		Serial.println(F("[BH1750] ERROR: too long for transmit buffer"));
	case 2: // received NACK on transmit of address
		Serial.println(F("[BH1750] ERROR: received NACK on transmit of address"));
	case 3: // received NACK on transmit of data
		Serial.println(F("[BH1750] ERROR: received NACK on transmit of data"));
	case 4: // other error
		Serial.println(F("[BH1750] ERROR: other error"));
	default:
		Serial.println(F("[BH1750] ERROR: undefined error"));
		break;
	}

	return false;

}

uint16_t BH1750::read_level(bool maxWait)
{
	if (BH1750_MODE == UNCONFIGURED) {
		Serial.println(F("[BH1750] Device is not configured!"));
		return 0;
	}

	// Measurement result will be stored here
	uint16_t level = 65535;

	// Send mode to sensor
	tca_com->set_ch(_dev_id);
	Wire.beginTransmission(BH1750_I2CADDR);
	Wire.write((uint8_t)BH1750_MODE);
	Wire.endTransmission();
	tca_com->disable();

	// Wait for measurement to be taken.
	// Measurements have a maximum measurement time and a typical measurement
	// time. The maxWait argument determines which measurement wait time is
	// used when a one-time mode is being used. The typical (shorter)
	// measurement time is used by default and if maxWait is set to True then
	// the maximum measurement time will be used. See data sheet pages 2, 5
	// and 7 for more details.
	// A continuous mode measurement can be read immediately after re-sending
	// the mode command.

	switch (BH1750_MODE) {

	case BH1750::ONE_TIME_LOW_RES_MODE:
	case BH1750::ONE_TIME_HIGH_RES_MODE:
	case BH1750::ONE_TIME_HIGH_RES_MODE_2:

		if (BH1750_MODE == BH1750::ONE_TIME_LOW_RES_MODE) {
			maxWait ? _delay_ms(24) : _delay_ms(16);
		}
		else {
			maxWait ? _delay_ms(180) : _delay_ms(120);
		}
		break;
	default: 
		break;
	}

	// Read two bytes from the sensor, which are low and high parts of the sensor
	// value
	tca_com->set_ch(_dev_id);
	Wire.requestFrom(BH1750_I2CADDR, 2);
	if (Wire.available() == 2) {
		level = Wire.read();
		level <<= 8;
		level |= Wire.read();
	}
	// Convert raw value to lux
	level /= 1.2;
	//TODO: add if level<0 --> level = 0 or device not present function maybe fixed/combined with ack-todo further up
	return level;

}

BH1750::~BH1750()
{
}
