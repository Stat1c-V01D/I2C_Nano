#pragma once
#include "Arduino.h"
//TODO: IMPORTANT -- Check for variable range and crank in some limitation and security code
#define CM 1
#define INC 0


class HCSR04
{
public:
	HCSR04(int trig_pin, int echo_pin, int timeout = 3000); // 3000 µs = 50cm // 30000 µs = 5 m
	long measure();
	long calc();
	void range(int runs, int pause);
	virtual ~HCSR04();
private:
	int _trig_pin;
	int _echo_pin;
	int _timeout;
	int _sys;
	long duration;
};

