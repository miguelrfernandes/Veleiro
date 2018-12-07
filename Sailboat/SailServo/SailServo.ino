#include <Servo.h>

#define _DEBUG TRUE
#define INC_POS 0
#define DEC_POS 1

const unsigned int DEBUG_SERIAL_BAUDRATE = 9600;

const unsigned int SAIL_SERVO_PIN = 49;

unsigned int servoPos = 90;
unsigned int dir = INC_POS;

Servo rudder;

void setup()
{

#ifdef _DEBUG
	Serial.begin(DEBUG_SERIAL_BAUDRATE);
#endif // _DEBUG

	rudder.attach(SAIL_SERVO_PIN);
	rudder.write(90);

}

void loop()
{

	// ServoRange(min, max, delay, increment) 
	ServoRange(rudder, 20, 160, 100, 10);

#ifdef _DEBUG
	Serial.print("Servo Position : "); Serial.println(servoPos);
#endif // _DEBUG


}

void ServoRange(Servo rudder, int _min, int _max, int _delay, int _inc)
{

	rudder.write(servoPos);
	delay(_delay);

	if (servoPos >= _max) dir = DEC_POS;
	if (servoPos <= _min) dir = INC_POS;

	if (dir == INC_POS)
		servoPos += _inc;
	else
		servoPos -= _inc;
}