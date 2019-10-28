/* Owned by Fernando Zaragoza - October 2019 */
#ifndef _MICROMOUSE_H
#define _MICROMOUSE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

//#include "Timers.h"
#include "DCMotor.h"

class Micromouse
{
public:
	Micromouse();
	~Micromouse();


private:

};


#endif