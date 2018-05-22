#pragma once
#include "Arduino.h"
#include <Wire.h>
//TODO: IMPORTANT -- Check for variable range and crank in some limitation and security code
class TCA9548 
{
public:
	TCA9548(int tca_addr = 0x70);
	virtual ~TCA9548();
	void set_ch(int ch);
	void disable();
private:
	void select(int value);
protected:
	int addr;
	int _tca_addr;
};
