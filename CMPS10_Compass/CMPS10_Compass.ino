#include <Wire.h>

#include <Servo.h>

#define _DEBUG TRUE
#define INC_POS 0
#define DEC_POS 1

const unsigned int DEBUG_SERIAL_BAUDRATE = 9600;

const unsigned int SAIL_SERVO_PIN = 9;

const unsigned int COMPASS_I2C_ADDRESS = 0x60;

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
	Wire.begin();

}

void loop()
{
      

	char pitch, roll;
	int bearing;
        
	retrieveCompassData(&bearing, &pitch, &roll);
        rudder.write(pitch);
	Serial.print("Compass Bearing : "); Serial.println(bearing);
	Serial.print("Pitch : "); Serial.println(pitch, DEC);
	Serial.print("Roll : "); Serial.println(roll, DEC);
        Serial.println(" ");

	delay(250);

}

void retrieveCompassData(int *bearing, char *pitch, char *roll)
{
	byte highByte, lowByte;

	Wire.beginTransmission((int)COMPASS_I2C_ADDRESS);
	Wire.write(2);
	Wire.endTransmission();

	Wire.requestFrom(COMPASS_I2C_ADDRESS, 4);

	while (Wire.available() < 4);

	highByte = Wire.read();
	lowByte = Wire.read();
	*pitch = (int)Wire.read();
	*roll = (int)Wire.read();

	*bearing = word(highByte, lowByte) / 10.0;
}
