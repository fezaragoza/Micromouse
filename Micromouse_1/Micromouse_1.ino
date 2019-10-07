/*
 Name:		Micromouse_1.ino
 Created:	9/9/2019 19:44:16
 Author:	ferzm
*/
#include "Timers.h"
#include "Encoder.h"

portMUX_TYPE encoderMux = portMUX_INITIALIZER_UNLOCKED;
Timer timer0;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	timer0.interruptInit(LEDC_TIMER0, SAMPLINGTIME, &onTimer0_ISR);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (timer0.checkTimer()) {
		Serial.println(timer0.counter);

	}
}



void IRAM_ATTR onTimer0_ISR()
{
	portENTER_CRITICAL_ISR(&timer0.timerMux);
	timer0.flag = true;
	portEXIT_CRITICAL_ISR(&timer0.timerMux);
}


//ENCODER MOTOR1
void IRAM_ATTR encoderA_ISR()
{
	//portENTER_CRITICAL_ISR(&timerMux);
	//noInterrupts();
	//if (robot.motor1.readEncoderA() != robot.motor1.readEncoderB()) {
	//	robot.motor1.flag_encoder_a = true;
	//}
	//else if (robot.motor1.readEncoderA() == robot.motor1.readEncoderB()) {
	//	if (robot.motor1.flag_encoder_b == 1) {
	//		robot.motor1.flag_encoder_b = 0;
	//		//if (motor1.count_s > 0) {
	//			//flag.count = 1;
	//		robot.motor1.count_s++;
	//		//}
	//	}
	//}
	//portEXIT_CRITICAL_ISR(&timerMux);
	//interrupts();
}

void IRAM_ATTR encoderB_ISR()
{
	//portENTER_CRITICAL_ISR(&encoderMux);
	//noInterrupts();
	//if (robot.motor1.readEncoderA() != robot.motor1.readEncoderB()) {
	//	robot.motor1.flag_encoder_b = true;
	//}
	//else if (robot.motor1.readEncoderA() == robot.motor1.readEncoderB()) {
	//	if (robot.motor1.flag_encoder_a == 1) {
	//		robot.motor1.flag_encoder_a = 0;
	//		robot.motor1.count_s++;
	//		robot.motor1.count_p++;
	//	}
	//}
	//portEXIT_CRITICAL_ISR(&encoderMux);
	//interrupts();
}