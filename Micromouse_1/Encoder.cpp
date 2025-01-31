/* Owned by Fernando Zaragoza - October 2019 */
#include "Encoder.h"

Encoder::Encoder(uint8_t signal_a, uint8_t signal_b)
{
	_signal_encoder_a	= signal_a;
	_signal_encoder_b	= signal_b;
	flag_encoder_a		= 0;
	flag_encoder_b		= false;
	count_p				= 0;
	count_s				= 0;
}

Encoder::~Encoder()
{
}

void Encoder::begin(void(*encoderA)(void), void(*encoderB)(void)) {
	pinMode(_signal_encoder_a, INPUT_PULLUP);
	pinMode(_signal_encoder_b, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(_signal_encoder_a), *encoderA, CHANGE);
	attachInterrupt(digitalPinToInterrupt(_signal_encoder_b), *encoderB, CHANGE);
}

bool Encoder::readEncoderA() {
	return digitalRead(_signal_encoder_a);
}

bool Encoder::readEncoderB() {
	return digitalRead(_signal_encoder_b);
}

uint16_t Encoder::getSpeed(){
	noInterrupts();
	protected_count_s = count_s;
	count_s				= 0;
	interrupts();
	_pulse_time = (protected_count_s / TIMECONVERSION);
	instant_speed = round(_pulse_time / FULLREVOLUTIONPULSES);
	//Serial.print(instant_speed);
	return instant_speed;
}

void Encoder::resetCounters()
{
	count_s = 0;
	protected_count_s = 0;
	instant_speed = 0;
}