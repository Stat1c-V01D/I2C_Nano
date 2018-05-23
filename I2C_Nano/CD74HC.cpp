#include "Arduino.h"
#include "CD74HC.h"
//#define DEBUG //Serial.print Debug messages
CD74HC::CD74HC(int s0, int s1, int s2, int s3, int common_pin, int en_pin)
{
	pinMode(s0, OUTPUT);
	pinMode(s1, OUTPUT);
	pinMode(s2, OUTPUT);
	pinMode(s3, OUTPUT);
	pinMode(en_pin, OUTPUT);
	_s0 = s0;
	_s1 = s1;
	_s2 = s2;
	_s3 = s3;
	_c_pin = common_pin;
	_en_pin = en_pin;
	enable(0);
#ifdef DEBUG
	Serial.println("[CH74HC] INFO: Initialized with: ");
	Serial.print("Adress Pins: ");
	Serial.print("S0-->");
	Serial.println(_s0);
	Serial.print("S1-->");
	Serial.println(_s1);
	Serial.print("S2-->");
	Serial.println(_s2);
	Serial.print("S3-->");
	Serial.println(_s3);
	Serial.print("Signal Pin: ");
	Serial.println(_c_pin);
	Serial.print("Enable Pin: ");
	Serial.println(_en_pin);
#endif // DEBUG
}

void CD74HC::ch_sel(int ch)
{
#ifdef DEBUG
	Serial.print("[CH74HC] INFO: Selecting Channel: ");
	Serial.println(ch);
#endif // DEBUG
	digitalWrite(_s0, _g_channel_truth_table[ch][0]);
	digitalWrite(_s1, _g_channel_truth_table[ch][1]);
	digitalWrite(_s2, _g_channel_truth_table[ch][2]);
	digitalWrite(_s3, _g_channel_truth_table[ch][3]);
}

void CD74HC::enable(bool mode)
{
#ifdef DEBUG
	Serial.print("[CH74HC] INFO: Setting Mode to: ");
	Serial.println(mode);
#endif // DEBUG
	if (mode == true)
	{
		digitalWrite(_en_pin, LOW);
	}
	else
	{
		digitalWrite(_en_pin, HIGH);
	}
}

void CD74HC::a_write(int ch, int a_value)
{
#ifdef DEBUG
	Serial.print("[CH74HC] INFO: Analog write value: ");
	Serial.print(a_value);
	Serial.print(" to Channel: ");
	Serial.println(ch);
#endif // DEBUG
	pinMode(_c_pin, OUTPUT);
	if (a_value < 0)
	{
		a_value = 0;
	}
	if (a_value > 1023)
	{
		a_value = 1023;
	}
	analogWrite(_c_pin, a_value);
	ch_sel(ch);
}

void CD74HC::d_write(int ch, int d_value)
{
#ifdef DEBUG
	Serial.print("[CH74HC] INFO: Digital write value: ");
	Serial.print(d_value);
	Serial.print(" to Channel: ");
	Serial.println(ch);
#endif // DEBUG
	if (d_value < 0)
	{
		d_value = 0;
	}
	if (d_value > 1)
	{
		d_value = 1;
	}
	pinMode(_c_pin, OUTPUT);
	digitalWrite(_c_pin, d_value);
	ch_sel(ch);
}

int CD74HC::a_read(int ch)
{
#ifdef DEBUG
	Serial.print("[CH74HC] INFO: Analog read value of Channel: ");
	Serial.println(ch);
#endif // DEBUG
	pinMode(_c_pin, INPUT);
	ch_sel(ch);
	int temp = analogRead(_c_pin);
	if (temp < 0)
	{
		temp = 0;
	}
	if (temp > 1023)
	{
		temp = 1023;
	}
	return temp;

}

int CD74HC::d_read(int ch)
{
#ifdef DEBUG
	Serial.print("[CH74HC] INFO: Digital read value of Channel: ");
	Serial.println(ch);
#endif // DEBUG
	pinMode(_c_pin, INPUT);
	ch_sel(ch);
	int temp = digitalRead(_c_pin);
	if (temp < 0)
	{
		temp = 0;
	}
	if (temp > 1)
	{
		temp = 1;
	}
	return temp;
}

CD74HC::~CD74HC()
{
}
