#include "Arduino.h"
#include "CD74HC.h"
//TODO: IMPORTANT -- Check for variable range and crank in some limitation and security code
int _g_channel_truth_table[16][4] = {
	// s0, s1, s2, s3     channel
	{ 0,  0,  0,  0 }, // 0
	{ 1,  0,  0,  0 }, // 1
	{ 0,  1,  0,  0 }, // 2
	{ 1,  1,  0,  0 }, // 3
	{ 0,  0,  1,  0 }, // 4
	{ 1,  0,  1,  0 }, // 5
	{ 0,  1,  1,  0 }, // 6
	{ 1,  1,  1,  0 }, // 7
	{ 0,  0,  0,  1 }, // 8
	{ 1,  0,  0,  1 }, // 9
	{ 0,  1,  0,  1 }, // 10
	{ 1,  1,  0,  1 }, // 11
	{ 0,  0,  1,  1 }, // 12
	{ 1,  0,  1,  1 }, // 13
	{ 0,  1,  1,  1 }, // 14
	{ 1,  1,  1,  1 }  // 15
};

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
}

void CD74HC::ch_sel(int ch)
{
	digitalWrite(_s0, _g_channel_truth_table[ch][0]);
	digitalWrite(_s1, _g_channel_truth_table[ch][1]);
	digitalWrite(_s2, _g_channel_truth_table[ch][2]);
	digitalWrite(_s3, _g_channel_truth_table[ch][3]);
}

void CD74HC::enable(bool mode)
{
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
	pinMode(_c_pin, OUTPUT);
	analogWrite(_c_pin, a_value);
	ch_sel(ch);
}

void CD74HC::d_write(int ch, int d_value)
{
	pinMode(_c_pin, OUTPUT);
	digitalWrite(_c_pin, d_value);
	ch_sel(ch);
}

int CD74HC::a_read(int ch)
{
	pinMode(_c_pin, INPUT);
	ch_sel(ch);
	return analogRead(_c_pin);

}

int CD74HC::d_read(int ch)
{
	pinMode(_c_pin, INPUT);
	ch_sel(ch);
	return digitalRead(_c_pin);
}

CD74HC::~CD74HC()
{
}
