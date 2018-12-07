#include <Wire.h>
#include <Servo.h>
#include <TinyGPSPlus.h>

const unsigned int DEBUG_SERIAL_BAUDRATE = 9600;

//GFS
const unsigned int GPS_SERIAL_BAUDRATE = 38400;
TinyGPSPlus gps;

//bússula
const unsigned int COMPASS_I2C_ADDRESS = 0x60;
char pitch, roll;
int bearing;

//Servo
#define _DEBUG TRUE
#define INC_POS 0
#define DEC_POS 1
const unsigned int SAIL_SERVO_PIN = 9;
unsigned int servoPos = 90;
unsigned int dir = INC_POS;
Servo rudder;

//Catavento
unsigned int ROTARY_SENSOR_PIN = 2;
unsigned int catavento;


void setup()
{
	Serial.begin(DEBUG_SERIAL_BAUDRATE);
	pinMode(ROTARY_SENSOR_PIN, INPUT_PULLUP);
        rudder.attach(SAIL_SERVO_PIN);
	rudder.write(90);
        Wire.begin();
        
        
        
        Serial3.begin(GPS_SERIAL_BAUDRATE);
	Serial3.print("$PGCMD,16,1,1,1,1,1*6B\r\n");	// configure MT3329 to output NMEA sentences

	Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
	Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
	Serial.println();

        
}

void loop()
{
	//catavento = pulseIn(ROTARY_SENSOR_PIN, HIGH);
        retrieveCompassData(&bearing, &pitch, &roll);
	


        Serial.print("Cata-vento: "); Serial.println(catavento);
	Serial.print("Bearing : "); Serial.println(bearing);
	Serial.print("Pitch : "); Serial.println(pitch, DEC);
	Serial.print("Roll : "); Serial.println(roll, DEC);
        Serial.println(" ");
	delay(250);
        catavento = map(catavento, 0, 4000,0 , 359);
        rudder.write(catavento);
        
        	// This sketch displays information every time a new sentence is correctly encoded.
	while (Serial3.available() > 0)
		if (gps.encode(Serial3.read()))
			displayGPSdata();

	if (millis() > 5000 && gps.charsProcessed() < 10)
	{
		Serial.println(F("No GPS detected: check wiring."));
		while (true);
	}


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


void displayGPSdata()
{
	Serial.print(F("Location: "));
	if (gps.location.isValid())
	{
		Serial.print(gps.location.lat(), 6);
		Serial.print(F(","));
		Serial.print(gps.location.lng(), 6);
	}
	else
	{
		Serial.print(F("INVALID"));
	}

	Serial.print(F("  Date/Time: "));
	if (gps.date.isValid())
	{
		Serial.print(gps.date.month());
		Serial.print(F("/"));
		Serial.print(gps.date.day());
		Serial.print(F("/"));
		Serial.print(gps.date.year());
	}
	else
	{
		Serial.print(F("INVALID"));
	}

	Serial.print(F(" "));
	if (gps.time.isValid())
	{
		if (gps.time.hour() < 10) Serial.print(F("0"));
		Serial.print(gps.time.hour());
		Serial.print(F(":"));
		if (gps.time.minute() < 10) Serial.print(F("0"));
		Serial.print(gps.time.minute());
		Serial.print(F(":"));
		if (gps.time.second() < 10) Serial.print(F("0"));
		Serial.print(gps.time.second());
		Serial.print(F("."));
		if (gps.time.centisecond() < 10) Serial.print(F("0"));
		Serial.print(gps.time.centisecond());
	}
	else
	{
		Serial.print(F("INVALID"));
	}

	Serial.println();
}
