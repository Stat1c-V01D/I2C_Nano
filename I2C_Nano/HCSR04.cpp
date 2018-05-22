#include "HCSR04.h"
#include "Arduino.h"
//TODO: IMPORTANT -- Check for variable range and crank in some limitation and security code
HCSR04::HCSR04(int trig_pin, int echo_pin, int timeout)
{
	pinMode(trig_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
	_trig_pin = trig_pin;
	_echo_pin = echo_pin;
	_timeout = timeout;
}

long HCSR04::measure()
{
	digitalWrite(_trig_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(_trig_pin, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trig_pin, LOW);
	duration = pulseIn(_echo_pin, HIGH, _timeout);
	if (duration == 0) {
		duration = _timeout;
	}
	return duration;
}

long HCSR04::calc()
{
	long distance_cm = duration / 29 / 2;
	return distance_cm;
}

void HCSR04::range(int runs, int pause)
{
	for (size_t i = 0; i <= runs; i++)
	{
		calc();
		delay(pause);
	}
}

HCSR04::~HCSR04()
{
}
