/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 Most Arduinos have an on-board LED you can control. On the Uno and
 Leonardo, it is attached to digital pin 13. If you're unsure what
 pin the on-board LED is connected to on your Arduino model, check
 the documentation at http://arduino.cc
 
 This example code is not in the public domain.
 
 modified 25 de julho de 2016
 by Claudio § Miguel
 */
int ledPin = 10 ;
int inPin = 2;
int val = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(inPin, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {


  val = digitalRead(inPin); 
  Serial.println("val = "+val);
  if (val == LOW){

    digitalWrite(ledPin, LOW);
  } 
  else{
    for(int i=10;i<250;i+=10){

      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(i);              // wait for a second
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      delay(i);
      i=i+10;    // wait for a second
      if(digitalRead(inPin) == LOW){
        break;
      }
    }
    digitalWrite(ledPin, HIGH);
  }


}
/*
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
 delay(1000);              // wait for a second
 digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
 delay(1000);
 */




