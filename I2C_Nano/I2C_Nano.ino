/*
 Name:		I2C_Nano.ino
 Created:	22.05.2018 17:03:43
 Author:	Kai
*/

//TODO: IMPORTANT -- Check for variable range and crank in some limitation and security code
#include "TCA9548.h"
#include "BH1750.h"
#include "HCSR04.h"
#include "CD74HC.h"
#include <Wire.h>


const int num_bh1750 = 5;

CD74HC analog_mux(A0, A1, A2, A3, A6, 11);
HCSR04 usonic(10, 9);
BH1750 * sensor[num_bh1750];


void setup()
{
	for (int i = 0; i < num_bh1750; i++)
	{
		sensor[i] = new BH1750(i);
	}
	for (int i = 0; i < num_bh1750; i++)
	{
		sensor[i]->begin();
	}
	Wire.begin(30);                // join i2c bus with address #30
	Wire.onRequest(requestEvent); // register event
	Serial.begin(9600);           // start serial for output
	analog_mux.enable(true);
}

void loop()
{
	for (int i = 0; i < num_bh1750; i++)
	{
		int lux = sensor[i]->read_level();
		if (lux<0)
		{
			lux = 0;
		}
		Serial.print("Sensor: ");
		Serial.println(i);
		Serial.print("Light: ");
		Serial.print(lux);
		Serial.println(" lx");
		Serial.println("----------------------");
	}
	
	
	delay(1000);
	
	/*
	for (size_t i = 0; i < 2; i++)
	{
		int val = analog_mux.a_read(i);
		Serial.println(val);
	}
	Serial.println("------------------");
	delay(1000);
	*/

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






