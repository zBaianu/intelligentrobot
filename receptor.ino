/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#define button 4
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo myServo;
boolean buttonState = 0;
void setup() {
  pinMode(button, INPUT);
  pinMode(6, OUTPUT);
  myServo.attach(5);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}
void loop() {
  delay(5);
  radio.startListening();
    while (radio.available()) {
      int angleV = 0;
      radio.read(&angleV, sizeof(angleV));
      if(angleV >= 100){
        digitalWrite(6, HIGH);
      } else {
        digitalWrite(6, LOW);
      }
    }
}
