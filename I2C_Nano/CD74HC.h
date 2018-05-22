#pragma once
#include "Arduino.h"
//TODO: IMPORTANT -- Check for variable range and crank in some limitation and security code
extern int _g_channel_truth_table[16][4];

class CD74HC
{
public:
	CD74HC(int s0, int s1, int s2, int s3, int common_pin, int en_pin);
	void ch_sel(int ch);
	void enable(bool mode); // true==enable, false==disable
	void a_write(int ch, int a_value);
	void d_write(int ch, int d_value);
	int a_read(int ch);
	int d_read(int ch);
	virtual ~CD74HC();

private:
	int _s0;
	int _s1;
	int _s2;
	int _s3;
	int _c_pin;
	int _en_pin;
	
};

