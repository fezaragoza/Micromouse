/* Owned by Fernando Zaragoza - October 2019 */
#include "Timers.h"


Timer::Timer()
{
	_ledc_timer;
	_timer = NULL;
	timerMux = portMUX_INITIALIZER_UNLOCKED;
	//flags_S flag;			// Not necessary
}

Timer::~Timer()
{
}

void Timer::pwmTimerConfig(ledc_mode_t speed_mode, ledc_timer_t timer_num, ledc_timer_bit_t bit_resolution, uint32_t freq_hz)
{
	_ledc_timer.speed_mode = speed_mode;
	_ledc_timer.timer_num = timer_num;
	_ledc_timer.duty_resolution = bit_resolution;
	_ledc_timer.freq_hz = freq_hz;
	ledc_timer_config(&_ledc_timer);
}

void Timer::interruptInit(uint8_t timer_num, uint32_t sampling_time, void(*onTimer)(void))
{
	_timer = timerBegin(timer_num, 80, true);
	timerAttachInterrupt(_timer, onTimer, true);
	timerAlarmWrite(_timer, sampling_time, true);
	timerAlarmEnable(_timer);
}

void Timer::enable() {
	flag.counter = 0;
	timerAlarmEnable(_timer);
}

void Timer::disable() {
	timerAlarmDisable(_timer);
}

bool Timer::checkTimer()
{
	if (flag.check_timer == 1)
	{
		portENTER_CRITICAL(&timerMux);
		flag.check_timer = false;
		portEXIT_CRITICAL(&timerMux);
		flag.counter++;
		return 1;
	}
	else
	{
		return 0;
	}
}
