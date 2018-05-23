#include "HCSR04.h"
#include "Arduino.h"
//#define DEBUG //Serial.print Debug messages
HCSR04::HCSR04(int trig_pin, int echo_pin, int timeout)
{
	pinMode(trig_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
	_trig_pin = trig_pin;
	_echo_pin = echo_pin;
	_timeout = timeout;
#ifdef DEBUG
	Serial.println("[HCSR04] INFO: Initialized with: ");
	Serial.print("Trigger Pin: ");
	Serial.println(_trig_pin);
	Serial.print("Echo Pin: ");
	Serial.println(_echo_pin);
#endif // DEBUG
}

long HCSR04::measure()
{
#ifdef DEBUG
	Serial.println("[HCSR04] INFO: Starting measurement");
#endif // DEBUG
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
	measure();
#ifdef DEBUG
	Serial.println("[HCSR04] INFO: Calculating Distance");
#endif // DEBUG

	long distance_cm = duration / 29 / 2;
	return distance_cm;
}

void HCSR04::range(int runs, int pause)
{
	if (pause > 10000) //this might be temporary!
	{
		pause = 5000;
	}
	if (pause < 1)
	{
		pause = 1;
	}
	if (runs < -1)
	{
		runs = -1;
	}
	if (runs > 10000) //this might be temporary!
	{
		runs = 1000;
	}
	if (runs==0)
	{
#ifdef DEBUG
		Serial.print("[HCSR04] INFO: Start Ranging in Continuos Mode ");
		Serial.print(" with inbetween-delay of ");
		Serial.println(pause);
#endif // DEBUG
		while (1)
			calc();
			delay(pause);
	}
	else if (runs==-1)
	{
#ifdef DEBUG
		Serial.print("[HCSR04] INFO: Stop Ranging");
#endif // DEBUG
		return;
	}
	else
	{
		for (size_t i = 0; i <= runs; i++)
		{
#ifdef DEBUG
			Serial.print("[HCSR04] INFO: Start Ranging over ");
			Serial.print(runs);
			Serial.print(" runs with inbetween-delay of ");
			Serial.println(pause);
			Serial.print("Current  Run: ");
			Serial.println(i);
#endif // DEBUG
			calc();
			delay(pause);
		}
	}
	
}

HCSR04::~HCSR04()
{
}
