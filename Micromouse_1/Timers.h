/* Owned by Fernando Zaragoza - September 2019 */
#ifndef _TIMERS_H
#define _TIMERS_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <driver/ledc.h>

#define MS2MIN 0.00001666F
#define SAMPLINGTIME 1000000 // 100ms, value in us.
#define MSTIMESAMPLING (SAMPLINGTIME * 0.001F)
#define TIMECONVERSION (MSTIMESAMPLING * MS2MIN)

#define ledPin 16 // 16 corresponds to GPIO16
#define frequen 5000 // 5kHz
#define ledChannel 0 // 0 to 15 (16 channels in total)
#define BIT_RESOL 8 // 1 to 16 bits - 8 means from 0 to 255

#define LEDC_HS_MODE        LEDC_HIGH_SPEED_MODE
#define LEDC_TIMER0         LEDC_TIMER_0
#define LEDC_TIMER1         LEDC_TIMER_1
#define LEDC_TIMER2         LEDC_TIMER_2
#define LEDC_8BITR			LEDC_TIMER_8_BIT
#define LEDC_FREQ			2000 // In Hz
#define LEDC_CH0			LEDC_CHANNEL_0
#define LEDC_CH1			LEDC_CHANNEL_1
#define LEDC_CH2			LEDC_CHANNEL_2
#define LEDC_CH3			LEDC_CHANNEL_3



//void interruptTimerInit(uint8_t timer_num, uint32_t sampling_time);
//bool checkTimer();

class Timer
{
public:
	Timer();
	~Timer();
	volatile int serial;
	volatile int change;
	volatile int motor_control;

	typedef struct flags {
		volatile unsigned int counter;
		volatile bool check_timer;
	}flags_S;
	flags_S flag;

	void pwmTimerConfig(ledc_mode_t speed_mode, ledc_timer_t timer_num, ledc_timer_bit_t bit_resolution, uint32_t freq_hz);
	void interruptInit(uint8_t timer_num, uint32_t sampling_time, void(*onTimer)(void));
	void enable();
	void disable();
	bool checkTimer();
	//void IRAM_ATTR onTimer();
	portMUX_TYPE timerMux;

private:
	ledc_timer_config_t _ledc_timer;
	hw_timer_t* _timer;
};

#endif