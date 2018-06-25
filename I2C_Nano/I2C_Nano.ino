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
//TODO: RPi Implementation
//#define DEBUG //Serial.print Debug messages

const int num_bh1750 = 2;
const int num_cd74HC = 5;
const int num_lf = 5;

CD74HC * analog_mux = new CD74HC(A0, A1, A2, A3, A6, 11);
HCSR04 * usonic = new HCSR04(10, 9);
BH1750 * sensor[num_bh1750];

uint16_t lux[num_bh1750];
long dist_cm;
int a_mux[num_cd74HC];
int d_LF[num_lf];

int CMD;

#ifdef DEBUG
int runs = 1;
#endif // DEBUG

void setup()
{
	Wire.begin(30);					// join i2c bus with address #30
	Wire.onRequest(requestEvent);	// register event
	Wire.onReceive(receiveEvent);
	Serial.begin(9600);				// start serial for output
	LF_setup();
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
	analog_mux->enable(true);

}

void loop()
{
#ifdef DEBUG
	Serial.println(runs);
	runs++;
#endif // DEBUG


	delay(1000);



}

void CD74HC_handler()
{
	//TODO: Communication to RPi + sensor readout
	for (size_t i = 0; i < num_cd74HC; i++)
	{
		a_mux[i] = analog_mux->a_read(i);
		Wire.write(a_mux[i]);
#ifdef DEBUG
		Serial.print("CD74HC Channel: ");
		Serial.print(i);
		Serial.print(" --- Value: ");
		Serial.println(a_mux[i]);
#endif // DEBUG
	}
#ifdef DEBUG
	Serial.println("+++++++++++++++++++++++++++++");
#endif // DEBUG
}

void HCSR04_handler()
{
	//TODO: Communication to RPi + sensor readout
#ifdef DEBUG
	Serial.println("+++++++++++++++++++++++++++++");
#endif // DEBUG
}

void BH1750_handler()
{
	//TODO: Communication to RPi + sensor readout
	for (int i = 0; i < num_bh1750; i++)
	{
		lux[i] = sensor[i]->read_level();
		Wire.write(lux[i]);
#ifdef DEBUG
		Serial.print("Sensor: ");
		Serial.print(i);
		Serial.print(" --- Light: ");
		Serial.print(lux[i]);
		Serial.println(" lx");
#endif // DEBUG
	}
#ifdef DEBUG
	Serial.println("+++++++++++++++++++++++++++++");
#endif // DEBUG
}

void LF_handler()
{
	//TODO: Communication to RPi + sensor readout
	for (int i = 0; i < num_lf; i++)
	{
		int pin = 2;
		d_LF[i] = digitalRead(pin);
		Wire.write(d_LF[i]);
		pin++;
#ifdef DEBUG
		Serial.print("Light Sensor: ");
		Serial.print(i);
		Serial.print(" --- Value: ");
		Serial.println(d_LF[i]);
#endif // DEBUG
	}
#ifdef DEBUG
	Serial.println("+++++++++++++++++++++++++++++");
#endif // DEBUG
	
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void requestEvent()
{
#ifdef DEBUG
	Serial.println("[SYSTEM] INFO: I2C Request Event");
#endif // DEBUG
	switch (CMD)
	{
	case 0x01:
		HCSR04_handler();
		CMD = 0x00;
		break;
	case 0x02:
		LF_handler();
		CMD = 0x00;
		break;
	case 0x03:
		CD74HC_handler();
		CMD = 0x00;
		break;
	case 0x04:
		BH1750_handler();
		CMD = 0x00;
		break;
	default:
		break;
	}
	CMD = 0x00;
}


void receiveEvent(int how_many)
{
#ifdef DEBUG
	Serial.print("[SYSTEM] INFO: I2C Receive Event with ");
	Serial.print(how_many);
	Serial.println("Byte(s)");
#endif // DEBUG
	if (Wire.available() > 0)
	{
		CMD = Wire.read();
	}
}

void LF_setup()
{
	pinMode(2, INPUT);
	pinMode(3, INPUT);
	pinMode(4, INPUT);
	pinMode(5, INPUT);
	pinMode(6, INPUT);
}