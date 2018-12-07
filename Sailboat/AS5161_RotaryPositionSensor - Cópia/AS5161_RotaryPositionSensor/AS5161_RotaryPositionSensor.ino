const unsigned int DEBUG_SERIAL_BAUDRATE = 9600;

const unsigned int ROTARY_SENSOR_PIN = 8;

void setup()
{

	Serial.begin(DEBUG_SERIAL_BAUDRATE);

	pinMode(ROTARY_SENSOR_PIN, INPUT_PULLUP);

}

void loop()
{
	unsigned int duration;

	duration = pulseIn(ROTARY_SENSOR_PIN, HIGH);

	Serial.print("Rotary Sensor Pulse Duration : "); Serial.println(duration);

}