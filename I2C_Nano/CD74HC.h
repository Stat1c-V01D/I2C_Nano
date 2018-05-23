#pragma once
#include "Arduino.h"
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
	
};

