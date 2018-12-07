#include <Wire.h>
#include <Servo.h>

Servo myservo;

void setup() {
  
  Wire.begin();
  myservo.attach(49);
  Serial.begin(9600);
}

void loop() {

  int dados = ler_bussola();

  if (((dados >= 0) && (dados <= 10)) || ((dados <= 359)  && (dados >= 349))) {
    
    myservo.write(1500);
    Serial.print(dados);
    Serial.println("  Frente");
    delay(100);
  }
  if ((dados > 10) && (dados < 180)) {
    
    myservo.write(2000);
    Serial.print(dados);
    Serial.println("Esquerda");
    delay(100);
  }

  if ((dados > 180) && (dados < 349)) {
    
    myservo.write(1000);
    Serial.print(dados);
    Serial.println("Direita");
    delay(100);
  }
}

int ler_bussola() {

  byte highByte, lowByte;
  int bearing;

  Wire.beginTransmission((int) 0x60);
  Wire.write(2);
  Wire.endTransmission();

  Wire.requestFrom(0x60, 2);

  while (Wire.available()) {

    highByte = Wire.read();
    lowByte = Wire.read();
    bearing = word(highByte, lowByte) / 10.0;
  }

  delay(100);
  return bearing;
}
