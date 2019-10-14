/*
 Name:		Micromouse_1.ino
 Created:	9/9/2019 19:44:16
 Author:	Fernando Zaragoza
*/
#include "Timers.h"
#include "Encoder.h"

portMUX_TYPE encoderMux = portMUX_INITIALIZER_UNLOCKED;
Timer timer0;
Encoder enc_motor1(12, 14);
Encoder enc_motor2(22, 21);


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	timer0.interruptInit(LEDC_TIMER0, SAMPLINGTIME, &onTimer0_ISR);
	enc_motor1.begin(&encoder_Motor1A_ISR, &encoder_motor1B_ISR);
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
	if (enc_motor1.readEncoderA() != enc_motor1.readEncoderB())
	{
		enc_motor1.flag_encoder_a = true;
	}
	else if (enc_motor1.readEncoderA() == enc_motor1.readEncoderB()) {
		if (enc_motor1.flag_encoder_b == 1) {
			enc_motor1.flag_encoder_b = 0;
			//if (enc_motor1.count_s > 0) {
				//enc_motor1.flag.count --;
			enc_motor1.count_p--;
			enc_motor1.count_s++;
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
	if (enc_motor1.readEncoderA() != enc_motor1.readEncoderB()) {
		enc_motor1.flag_encoder_b = true;
	}
	else if (enc_motor1.readEncoderA() == enc_motor1.readEncoderB()) {
		if (enc_motor1.flag_encoder_a == 1) {
			enc_motor1.flag_encoder_a = 0;
			enc_motor1.count_s++;
			enc_motor1.count_p++;
			//enc_motor1A.count_p++;
		}
	}
	//portEXIT_CRITICAL_ISR(&encoderMux);
	interrupts();
}