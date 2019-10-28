/* Owned by Fernando Zaragoza - October 2019 */
#include "DCMotor.h"

#if (ENCODER == TRUE)
Motor::Motor(uint8_t pwm_pin, uint8_t direc_1, uint8_t direc_2, uint8_t signala, uint8_t signalb):enc(signala, signalb)
{
	duty_cyle	= 0;
	flag_right	= 0;
	flag_left	= 0;
	_pwm_pin	= pwm_pin;
	_direc1_pin = direc_1;
	_direc2_pin = direc_2;
	pinMode(_direc1_pin, OUTPUT);
	pinMode(_direc2_pin, OUTPUT);
	_pwm_ledc;
}
#else 
Motor::Motor(uint8_t pwm_pin, uint8_t direc_1, uint8_t direc_2)
{
	duty_cyle = 0;
	flag_right = 0;
	flag_left = 0;

	_pwm_ledc;
	_pwm_pin = pwm_pin;
	_direc1_pin = direc_1;
	_direc2_pin = direc_2;
	pinMode(_direc1_pin, OUTPUT);
	pinMode(_direc2_pin, OUTPUT);

}
#endif

Motor::~Motor()
{
}


void Motor::pwmChannelConfig(ledc_channel_t channel, uint8_t pwm_pin, ledc_mode_t speed_mode, ledc_timer_t timer_num, uint32_t pwm_duty)
{
	_pwm_ledc.channel = channel;
	_pwm_ledc.gpio_num = pwm_pin;
	_pwm_ledc.speed_mode = speed_mode;
	_pwm_ledc.timer_sel = timer_num;
	_pwm_ledc.duty = pwm_duty;
	ledc_channel_config(&_pwm_ledc);
}

void Motor::setPWM(uint8_t out_dutyc) {
	//ledc_set_duty_and_update(_pwm_ledc.speed_mode, _pwm_ledc.channel, out_dutyc, maxDuty_8b);
	ledc_set_duty(_pwm_ledc.speed_mode, _pwm_ledc.channel, out_dutyc);
	ledc_update_duty(_pwm_ledc.speed_mode, _pwm_ledc.channel);
}


//uint32_t Motor::getControlOutput(uint32_t speed) {
//	return vel_control.pidCallback(speed);
//}


void Motor::right() {
	digitalWrite(_direc1_pin, LOW);
	digitalWrite(_direc2_pin, HIGH);
	flag_right				= true;
	flag_left				= 0;
#if (ENCODER == TRUE)
	enc.resetCounters();
#endif
	//vel_control.resetError();
}
void Motor::left() {
	digitalWrite(_direc1_pin, HIGH);
	digitalWrite(_direc2_pin, LOW);
	flag_right				= false;
	flag_left				= 1;
#if (ENCODER == TRUE)
	enc.resetCounters();
#endif
	//vel_control.resetError();
}

void Motor::stop() {
	digitalWrite(_direc1_pin, LOW);
	digitalWrite(_direc2_pin, LOW);
	flag_right				= false;
	flag_left				= 0;
#if (ENCODER == TRUE)
	enc.resetCounters();
#endif
	//vel_control.resetError();
}

void Motor::checkRotDirection() {
	/*if (control.error >= 0)
	{
	}
	else {
		left();
	}*/
}

void Motor::_chDirection() {
	/*if (flag_left)
	{
		right();
	}
	else
	{
		left();
	}*/
}
