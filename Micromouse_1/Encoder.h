/* Owned by Fernando Zaragoza - September 2019 */
#ifndef _ENCODER_H
#define _ENCODER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Timers.h"

#define FULLREVOLUTIONPULSES 12*75

class Encoder
{
public:
	Encoder(uint8_t signal_a, uint8_t signal_b);
	~Encoder();

	volatile bool	flag_encoder_a, flag_encoder_b;
	//volatile bool	_count_s;
	volatile int	count_s, count_p;
	unsigned int	protected_count_s, protected_count_p;
	uint16_t		instant_speed;
	double			instant_pos;

	void begin(void(*encoderA)(void), void(*encoderB)(void));
	bool readEncoderA();
	bool readEncoderB();
	uint16_t getSpeed();
	void resetCounters();

private:
	uint8_t			_signal_encoder_a;
	uint8_t			_signal_encoder_b;
	double			_pulse_time, _time_conv;
};


#endif