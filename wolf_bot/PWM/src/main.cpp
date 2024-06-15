#include <Arduino.h>

void motorSetup(int res, int pwmChannel, int freq, int motorPin1, int motorPin2, int enablePin, int inputPin) {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(inputPin, INPUT);
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, res);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enablePin, pwmChannel);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
} 

void moveMotor(int dutyCycle, int motorPin1, int motorPin2, int pwmChannel, int inputPin) {
  dutyCycle = pulseIn(inputPin, HIGH);
  if (dutyCycle < 1617) { // Left
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    dutyCycle = ((1621-dutyCycle)*127)/(1621-1121) + 127; //2121 is high, 1121 is low, 1621 is neutral
    ledcWrite(pwmChannel, dutyCycle); 
  } else if (dutyCycle > 1625) { // Right
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    dutyCycle = ((dutyCycle - 1621)*127)/(2121-1621) + 127; //2121 is high, 1121 is low, 1621 is neutral
    ledcWrite(pwmChannel, dutyCycle); 
  }
  Serial.println(dutyCycle);
}

// Motor A
int motor1Pin1 = 15; //15
int motor1Pin2 = 13; //13
int enable1Pin = 12; //12
int motor2Pin1 = 25; //25
int motor2Pin2 = 26; //26
int enable2Pin = 27; //27
int inputPin1 = 2;
int inputPin2 = 32;
int inputPin3 = 33; // shooting pin

// Setting PWM properties
const int freq = 30000;
const int pwmChannel1 = 0;
const int resolution = 8;
int dutyCycle1 = 0;
const int pwmChannel2 = 1;
int dutyCycle2 = 0;

void setup() {

  Serial.begin(115200);
  motorSetup(resolution, pwmChannel1, freq, motor1Pin1, motor1Pin2, enable1Pin, inputPin1);
  motorSetup(resolution, pwmChannel2, freq, motor2Pin1, motor2Pin2, enable2Pin, inputPin2);
  //pinMode(inputPin3, INPUT);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  moveMotor(dutyCycle1, motor1Pin1, motor1Pin2, pwmChannel1, inputPin1);
  moveMotor(dutyCycle2, motor2Pin1, motor2Pin2, pwmChannel2, inputPin2);
  // int val = pulseIn(inputPin3, HIGH);
  // Serial.println(val);
  
}