#include "TCA9548.h"
#include "Arduino.h"
#include <Wire.h>
//TODO: IMPORTANT -- Check for variable range and crank in some limitation and security code
TCA9548::TCA9548(int addr)
{
	_tca_addr = addr;
	disable();
}

TCA9548::~TCA9548()
{
}

void TCA9548::set_ch(int ch)
{
	select(1 << ch);
}

void TCA9548::disable()
{
	select(0);
}

void TCA9548::select(int value)
{
	Wire.beginTransmission(_tca_addr);
	Wire.write(value);
	Wire.endTransmission(true);
}
