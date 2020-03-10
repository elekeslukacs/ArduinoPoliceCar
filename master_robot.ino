#include <LiquidCrystal.h>
// include I2C library
#include <Wire.h>
char current = 10;


volatile int start = 0; //start siren
int buzzer = 8;
int red = 10; //red led to pin 10
int blue = 9; //blue led to pin 9

int led = 3; // headlights connected to pin 3
int photoResistor = A0; //photoresistor connected to A0
int lightIntensity;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(2, HIGH);
  //digitalWrite(3, HIGH);
  attachInterrupt(digitalPinToInterrupt(2), functieUnu, RISING);
  
 // Open I2C bus as master
 Serial.begin(9600);
 Serial1.begin(9600);
 Wire.begin();
}

void startSiren(){
  tone(buzzer, 1000);// Send 1KHz sound signal...
  digitalWrite(blue, HIGH);
  digitalWrite(red, LOW);
  delay(500);        // ...for 0.5 sec
  noTone(buzzer);
  tone(buzzer, 600);// Stop sound...
  digitalWrite(blue, LOW);
  digitalWrite(red, HIGH);
  delay(500);        // ...for 0.5 sec
}

void setLights(){
  lightIntensity = analogRead(photoResistor);
  Serial.println(lightIntensity);
  if(lightIntensity < 50)
  digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
}

void functieUnu(){
  start = 1 - start;
}

void loop() {
 if(Serial1.available()){
  current = (char)Serial1.read();
  Serial.println(current);
 }
 //Serial.println(current);
 Wire.beginTransmission(9); // transmit to device #9
 Wire.write(current); // transmit x
 Wire.endTransmission(); // stop transmission
 delay(10);
 current = 'a';

  setLights();
  if(start){
    startSiren();
  }
  else{
    noTone(buzzer);
  }
  Serial.println(start);
delay(500);
}
