/*
 Name:		I2C_Nano.ino
 Created:	22.05.2018 17:03:43
 Author:	Kai
*/

#include "TCA9548.h"
#include "BH1750.h"
#include "HCSR04.h"
#include "CD74HC.h"
#include <Wire.h>

//#define DEBUG //Serial.print Debug messages
const int num_bh1750 = 2;

CD74HC analog_mux(A0, A1, A2, A3, A6, 11);
HCSR04 usonic(10, 9);
BH1750 * sensor[num_bh1750];

uint16_t lux[num_bh1750];
long dist_cm[8];
int a_mux[2][16];
int d_LF[5];

#ifdef DEBUG
int runs = 1;
#endif // DEBUG

void setup()
{
	Wire.begin(30);					// join i2c bus with address #30
	Wire.onRequest(requestEvent);	// register event
	Serial.begin(9600);				// start serial for output
#ifdef DEBUG
	Serial.println("[SYSTEM] INFO: Setting up I2C Address 30 and Serial on 9600BAUD");
#endif // DEBUG

	for (int i = 0; i < num_bh1750; i++)
	{
#ifdef DEBUG
		Serial.print("[SYSTEM] INFO: Creating BH1750 Object with ID: ");
		Serial.println(i);
#endif // DEBUG
		sensor[i] = new BH1750(i);
	}
	for (int i = 0; i < num_bh1750; i++)
	{
#ifdef DEBUG
		Serial.print("[SYSTEM] INFO: Setting up BH1750 Object with ID: ");
		Serial.println(i);
#endif // DEBUG
		sensor[i]->begin();
	}
#ifdef DEBUG
	Serial.println("[SYSTEM] INFO: Enabling CD74HC");
#endif // DEBUG
	analog_mux.enable(true);
}

void loop()
{
#ifdef DEBUG
	Serial.println(runs);
	runs++;
#endif // DEBUG
	for (int i = 0; i < num_bh1750; i++)
	{
		lux[i] = sensor[i]->read_level();
		Serial.print("Sensor: ");
		Serial.print(i);
		Serial.print(" --- Light: ");
		Serial.print(lux[i]);
		Serial.println(" lx");
	}
	Serial.println("+++++++++++++++++++++++++++++");

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

//TODO: Communication to RPi
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void requestEvent()
{
#ifdef DEBUG
	Serial.println("[SYSTEM] INFO: I2C Request received");
#endif // DEBUG

	static char c = '0';

	Wire.write
	(c++);
	if (c > 'z')
		c = '0';
}






