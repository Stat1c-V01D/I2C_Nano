#pragma once
#include "Arduino.h"
#include <Wire.h>

class TCA9548 
{
public:
	TCA9548(int tca_addr = 0x70);
	virtual ~TCA9548();
	//void set_ch(uint8_t ch);  // Deprecated Code --ARTIFACT--
	void select(uint8_t value);
	void disable();
private:
	int addr;
	int _tca_addr;
};
