#include "TCA9548.h"
#include "Arduino.h"
#include <Wire.h>

//#define DEBUG //Serial.print Debug messages
TCA9548::TCA9548(int addr)
{
#ifdef DEBUG
	Serial.print("[TCA] INFO: Initialized with Address: ");
	Serial.print(addr);
#endif // DEBUG
	_tca_addr = addr;
	//disable();
}

TCA9548::~TCA9548()
{
}

/*
void TCA9548::set_ch(uint8_t ch) // Deprecated Code --ARTIFACT--
{
	select(ch);
}
*/
void TCA9548::disable()
{
#ifdef DEBUG
	Serial.println("[TCA] INFO: Disabling all Channels! ");
#endif // DEBUG
	Wire.beginTransmission(_tca_addr);
	Wire.write(0);
	Wire.endTransmission();
}

void TCA9548::select(uint8_t value)
{
	if (value > 7)
	{
		value = 7;
	}
	if (value < 0)
	{
		value = 0;
	}
#ifdef DEBUG
	Serial.print("[TCA] INFO: Trying to set Channel: ");
	Serial.print(value);
	Serial.println(" to TCA");
#endif // DEBUG
	Wire.beginTransmission(_tca_addr);
	Wire.write(0);
	Wire.write(1<<value);
	Wire.endTransmission();
#ifdef DEBUG
	byte ack = Wire.endTransmission();
	switch (ack) {
	case 0:
		Serial.print("[TCA] SUCCESS: Successfully set Channel: ");
		Serial.println(value);
		return;
	case 1: // too long for transmit buffer
		Serial.println("[TCA] ERROR: too long for transmit buffer");
	case 2: // received NACK on transmit of address
		Serial.println("[TCA] ERROR: received NACK on transmit of address");
	case 3: // received NACK on transmit of data
		Serial.println("[TCA] ERROR: received NACK on transmit of data");
	case 4: // other error
		Serial.println("[TCA] ERROR: other error");
		break;
	default:
		Serial.println("[TCA] ERROR: undefined error");
		break;
	}
#endif // DEBUG

}
