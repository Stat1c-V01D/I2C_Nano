/*
 Name:		I2C_Nano.ino
 Created:	22.05.2018 17:03:43
 Author:	Kai
*/


#include <Ultrasonic.h>
#include <TI_TCA9548A.h>
#include "CD74HC.h"
#include <Wire.h>


CD74HC analog_mux(A0, A1, A2, A3, A4, 11);

void setup()
{
	Wire.begin(30);                // join i2c bus with address #2
	Wire.onRequest(requestEvent); // register event
	Serial.begin(9600);           // start serial for output
	analog_mux.enable(true);
}

void loop()
{
	for (size_t i = 0; i < 2; i++)
	{
		int val = analog_mux.a_read(i);
		Serial.println(val);
	}
	Serial.println("------------------");
	delay(1000);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void requestEvent()
{
	static char c = '0';

	Wire.write
	(c++);
	if (c > 'z')
		c = '0';
}

