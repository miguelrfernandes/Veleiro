#include <TinyGPSPlus.h>

const unsigned int DEBUG_SERIAL_BAUDRATE = 9600;
const unsigned int GPS_SERIAL_BAUDRATE = 38400;

TinyGPSPlus gps;

void setup()
{

	Serial.begin(DEBUG_SERIAL_BAUDRATE);

	Serial3.begin(GPS_SERIAL_BAUDRATE);
	Serial3.print("$PGCMD,16,1,1,1,1,1*6B\r\n");	// configure MT3329 to output NMEA sentences

	Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
	Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
	Serial.println();

}

void loop()
{

q
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
