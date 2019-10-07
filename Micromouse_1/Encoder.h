/* Owned by Fernando Zaragoza - September 2019 */
#ifndef _ENCODER_H
#define _ENCODER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define FULLREVOLUTIONPULSES 900

class Encoder
{
public:
	Encoder(uint8_t signal_a, uint8_t signal_b);
	~Encoder();

	volatile bool flag_encoder_a, flag_encoder_b;
	volatile bool _count_s;
	volatile int count_s;
	unsigned int _protected_count;
	double _pulse_time, _time_conv;
	uint16_t instant_speed;

	void begin(void(*encoderA)(void), void(*encoderB)(void));

	bool readEncoderA();
	bool readEncoderB();
	uint16_t getSpeed();

private:
	uint8_t _signal_encoder_a;
	uint8_t _signal_encoder_b;
	uint16_t _protected_count_s;

};



#endif