/*
 Name:		Micromouse_1.ino
 Created:	9/9/2019 19:44:16
 Author:	Fernando Zaragoza
*/

/* MOTOR A */
#define MOTOR1_PWM_PIN	32 // Motor.h
#define MOTOR1_DIREC_1	34 // Motor.h
#define MOTOR1_DIREC_2	35 // Motor.h
#define ENCODER1_PINA	21 // ENCODER.h
#define ENCODER1_PINB	22 // ENCODER.H
/* MOTOR B */
#define MOTOR1_PWM_PIN	14 // Motor.h
#define MOTOR1_DIREC_1	26 // Motor.h
#define MOTOR1_DIREC_2	27 // Motor.h
#define ENCODER1_PINA	12 // ENCODER.h
#define ENCODER1_PINB	13 // ENCODER.H

#include "Micromouse.h"

portMUX_TYPE encoderMux = portMUX_INITIALIZER_UNLOCKED;
Timer timer0;
Motor motor1(MOTOR1_PWM_PIN, MOTOR1_DIREC_1, MOTOR1_DIREC_2, ENCODER1_PINA, ENCODER1_PINB);
//Encoder enc_motor1(12, 14);
//Encoder enc_motor2(22, 21);


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	timer0.interruptInit(LEDC_TIMER0, SAMPLINGTIME, &onTimer0_ISR);
	motor1.enc.begin(&encoder_Motor1A_ISR, &encoder_motor1B_ISR);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (timer0.checkTimer()) {
		Serial.println(timer0.flag.counter);
		//Serial.println(enc_motor1.getSpeed());

	}

}


void IRAM_ATTR onTimer0_ISR()
{
	portENTER_CRITICAL_ISR(&timer0.timerMux);
	timer0.flag.check_timer = true;
	portEXIT_CRITICAL_ISR(&timer0.timerMux);
}


//ENCODER MOTOR1
void IRAM_ATTR encoder_Motor1A_ISR()
{
	//portENTER_CRITICAL_ISR(&timerMux);
	noInterrupts();
	if (motor1.enc.readEncoderA() != motor1.enc.readEncoderB())
	{
		motor1.enc.flag_encoder_a = true;
	}
	else if (motor1.enc.readEncoderA() == motor1.enc.readEncoderB()) {
		if (motor1.enc.flag_encoder_b == 1) {
			motor1.enc.flag_encoder_b = 0;
			//if (motor1.enc.count_s > 0) {
				//motor1.enc.flag.count --;
			motor1.enc.count_p--;
			motor1.enc.count_s++;
			//}
		}
	}
	//portEXIT_CRITICAL_ISR(&timerMux);
	interrupts();
}

void IRAM_ATTR encoder_motor1B_ISR()
{
	//portENTER_CRITICAL_ISR(&encoderMux);
	noInterrupts();
	if (motor1.enc.readEncoderA() != motor1.enc.readEncoderB()) {
		motor1.enc.flag_encoder_b = true;
	}
	else if (motor1.enc.readEncoderA() == motor1.enc.readEncoderB()) {
		if (motor1.enc.flag_encoder_a == 1) {
			motor1.enc.flag_encoder_a = 0;
			motor1.enc.count_s++;
			motor1.enc.count_p++;
			//motor1.encA.count_p++;
		}
	}
	//portEXIT_CRITICAL_ISR(&encoderMux);
	interrupts();
}