#include <Arduino.h>


#define inputPin 2

void setup() {
  // put your setup code here, to run once:


  //pinMode(analogPin, INPUT_PULLUP);
  Serial.begin(115200);

    pinMode(inputPin, INPUT);

  //adcStart(analogPin);

  delay(100);
}


void loop() {
    // put your main code here, to run repeatedly:

//    unsigned long highTime pulseIn(inputPin, HIGH);
//    unsigned long lowTime pulseIn(inputPin, LOW);
//    unsigned long cycleTime = highTime + lowTime;
//    float dutyCycle = (float)highTime / float(cycleTime);

    int dutyCycle = pulseIn(inputPin, HIGH);
    //Serial.println(pwm_value);

    Serial.print("val: ");
    Serial.println(dutyCycle);
    //delay(100);


//    delay(2000);
//    Serial.println("==================");
//    for (int i = 0; i < 36; i++) {
//        Serial.print("pin: ");
//        Serial.print(i);
//        Serial.print(" | val: ");
//        Serial.println(analogRead(i));
//        delay(1);
//    }


}