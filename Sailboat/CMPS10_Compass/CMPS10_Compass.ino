#include <Wire.h>

const unsigned int DEBUG_SERIAL_BAUDRATE = 9600;

const unsigned int COMPASS_I2C_ADDRESS = 0x60;

void setup()
{

	Serial.begin(DEBUG_SERIAL_BAUDRATE);

	Wire.begin();

}

void loop()
{

	char pitch, roll;
	int bearing;

	retrieveCompassData(&bearing, &pitch, &roll);

	Serial.print("Compass Bearing : "); Serial.println(bearing);
	Serial.print("Pitch : "); Serial.println(pitch, DEC);
	Serial.print("Roll : "); Serial.println(roll, DEC);

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