/*************************************************************************
 * File Name          : DemoArduinoMbot.ino
 * Author             : Francois Bayart
 * Updated            : Francois Bayart
 * Version            : V1.0.0
 * Date               : 13 december 2015
 * Description        : mBot codes
 * License            : MIT
 **************************************************************************/

#include <Makeblock.h>
#include <SoftwareSerial.h>
#include <Wire.h>

// RGB LED
MeRGBLed rgbled(PORT_3);

// MOTOR
MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
uint8_t motorSpeed = 100;

// LIGHT SENSOR
// MeLightSensor lightSensor(PORT_6);

// ULTRASON
MeUltrasonicSensor ultraSensor(PORT_7); 

// MePort lightsensor(8);

// PRESS BUTTON
// Me4Button btn(7); //Me4Button module can only be connected to the PORT_6, PORT_7, PORT_8 of base shield.

int motorState = 0;
int tryToTurn = 0;

void setup() 
{
  Serial.begin(9600);
//    rgbled_2.setNumber(15);
}

void loop()
{
  // Serial.println( lightsensor.aRead2() );
  
  if(motorState==0) {
    motorOn();
  }

  // Serial.println(ultraSensor.distanceCm());
  if(ultraSensor.distanceCm() < 10){
    Serial.println( ultraSensor.distanceCm() );
    Serial.println( "cm" );
    while(ultraSensor.distanceCm() < 10) {
      mbotEscape();
    }
    motorOn();
  }else{
    if(motorState==0) { 
      motorOn();
    }
  }

}

void ledon(int led){
  // led 0 : RGB led2
  // led 1 : RGB led1
  rgbled.setColorAt(led,0,0,255);
  rgbled.show();
  delay(300);
  rgbled.setColorAt(led,0,255,0);
  rgbled.show();
  delay(300);
  rgbled.setColorAt(led,255,0,0);
  rgbled.show();
  delay(300);
  rgbled.setColorAt(led,0,0,0);
  rgbled.show();
  delay(300);
}

void motorOn() {
  motorState=1;
  motor1.run(-motorSpeed); // value: between -255 and 255.
  motor2.run(motorSpeed+10);
  // Serial.println(motorSpeed);
  Serial.println("motor start");
}
void motorOff() {
  motorState=0;
  motor1.stop();
  motor2.stop();
  Serial.println("motor stop");
}
void mbotEscape() {
  byte randomDelay = random(100,1500);
  motor1.run(100);
  motor2.run(-100);
  delay(randomDelay);
  motor1.stop();
  motor2.stop();
  delay(5);
  motor1.run(-100);
  delay(randomDelay);
  motor1.stop();
}
 

