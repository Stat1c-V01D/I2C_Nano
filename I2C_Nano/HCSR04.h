#pragma once
#include "Arduino.h"
#define CM 1
#define INC 0


class HCSR04
{
public:
	HCSR04(int trig_pin, int echo_pin, int timeout = 3000); // 3000 µs = 50cm // 30000 µs = 5 m
	void range(int runs, int pause);
	virtual ~HCSR04();
private:
	int _trig_pin;
	int _echo_pin;
	int _timeout;
	int _sys;
	long duration;
	long measure();
	long calc();
};

