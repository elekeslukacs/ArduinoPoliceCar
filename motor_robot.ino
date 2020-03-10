#include <Servo.h>
#include <Wire.h>
// Pins of motor 1
#define mpin00 5
#define mpin01 6
// Pins of motor 2
#define mpin10 3
#define mpin11 11
//Servo srv;

char current = 'a';
//****SETUP*****
void setup() {
 // configuration of motor pins as output, initially 0
 digitalWrite(mpin00, 0);
 digitalWrite(mpin01, 0);
 digitalWrite(mpin10, 0);
 digitalWrite(mpin11, 0);
 pinMode (mpin00, OUTPUT);
 pinMode (mpin01, OUTPUT);
 pinMode (mpin10, OUTPUT);
 pinMode (mpin11, OUTPUT);
 // LED pin
 pinMode(13, OUTPUT);

 //I2C
  Wire.begin(9);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  //  Warning code
//  Slow blink
 for (int i=0; i<10; i++)
 {
 digitalWrite(13, 1);
 delay(200);
 digitalWrite(13, 0);
 delay(200);
 }
 // Fast blink. Remove the USB cable!!!!
 for (int i=0; i<10; i++)
 {
 digitalWrite(13, 1);
 delay(100);
 digitalWrite(13, 0);
 delay(100);
 }
 digitalWrite(13, 1);
}

//*****SETUP******


void receiveEvent(int bytes){
  current = (char)Wire.read();
}

// Function to control a motor
// Input: pins m1 and m2, direction and speed
void StartMotor (int m1, int m2, int forward, int speed)
{

 if (speed==0) // stop
 {
 digitalWrite(m1, 0); 
 digitalWrite(m2, 0);
 }
 else
 {
 if (forward)
 {
 digitalWrite(m2, 0);
 analogWrite (m1, speed); // use PWM
 }
 else
 {
 digitalWrite(m1, 0);
 analogWrite(m2, speed);
 }
 }
}
// Safety function
// Commands motors to stop, then delays
void delayStopped(int ms)
{
 StartMotor (mpin00, mpin01, 0, 0);
 StartMotor (mpin10, mpin11, 0, 0);
 delay(ms);
}

void moveForward(int ms){
 StartMotor (mpin00, mpin01, 1, 128);
 StartMotor (mpin10, mpin11, 1, 128);
 delay(ms);
 current = 'a';
 delayStopped(100);
}

void moveBack(int ms){
 StartMotor (mpin00, mpin01, 0, 128);
 StartMotor (mpin10, mpin11, 0, 128);
 delay(ms);
 current = 'a';
 delayStopped(100);
}

void moveLeft(int ms){
  StartMotor (mpin00, mpin01, 1, 128);
  StartMotor (mpin10, mpin11, 0, 128);
  delay(ms);
  current = 'a';
  delayStopped(100);
}

void moveRight(int ms){
  StartMotor (mpin00, mpin01, 0, 128);
  StartMotor (mpin10, mpin11, 1, 128);
  delay(ms);
  current = 'a';
  delayStopped(100);
}

void loop() { 

 Serial.println(current);
 if(current == '1'){
  moveForward(500);
  current = '0';
 }
 else if(current == '2'){
  moveBack(500);
  current = '0';
 }
 else if (current == '3'){
  moveRight(250);
  current = '0';
 }
 else if (current == '4'){
  moveLeft(250);
  current = '0';
 }

 //delay(500);
 //delayStopped(500);
} 
