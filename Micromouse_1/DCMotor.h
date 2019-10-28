/* Owned by Fernando Zaragoza - October 2019 */
#ifndef _DCMOTOR_H
#define _DCMOTOR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Flags.h"
#include "Timers.h"

#ifdef ENCODER
#	include "Encoder.h"
#else
#	define ENCODER FALSE
#endif // !ENCODER

class Motor
{
public:
#if (ENCODER == TRUE)
	Motor(uint8_t pwm_pin, uint8_t direc_1, uint8_t direc_2, uint8_t signala, uint8_t signalb);
#else
	Motor(uint8_t pwm_pin, uint8_t direc_1, uint8_t direc_2);
#endif
	~Motor();

	/*		LOCAL CLASS PUBLIC VARIBALES		*/
	uint8_t duty_cyle;
	bool	flag_right, flag_left;
	/********************************************/

	/*		LOCAL CLASS PUBLIC FUNCTIONS		*/
	void pwmChannelConfig(ledc_channel_t channel, uint8_t pwm_pin, ledc_mode_t speed_mode, ledc_timer_t timer_num, uint32_t pwm_duty);
	void setPWM(uint8_t out_dutyc);
	void right();
	void left();
	void stop();
	void checkRotDirection();
	//void setDirection(uint8_t direction);
	//uint32_t getControlOutput(uint32_t speed);
	/*********************************************/
#if (ENCODER == TRUE)
	Encoder enc;
#endif

	/*		CLASS 		*/
	//Control vel_control;

private:
	ledc_channel_config_t _pwm_ledc;
	uint8_t _pwm_pin, _direc1_pin, _direc2_pin;
	void _chDirection();
};


#endif