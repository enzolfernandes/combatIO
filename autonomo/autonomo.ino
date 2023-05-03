//Bibliotecas

#include <Wire.h>
#include <analogWrite.h>
#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <ESP32Tone.h>
#include <VL53L1X.h>

// Motores
constexpr int rightMotorPin = 25;
constexpr int leftMotorPin = 26;
Servo leftMotor;
Servo rightMotor;
constexpr int stopped = 90; // Ponto neutro dos motores, varia de cada ESC, teremos que usar o osciloscópio para saber
constexpr int forward = 180;  // Talvez não seja útil
constexpr int reverse = 0;  // Talvez não seja útil
constexpr int spinsearch = 135; //velocidade de giro

VL53L1X sensor;

void setup()
{

  leftMotor.attach(leftMotorPin);
  leftMotor.write(stopped);
  Serial.begin(9600);
}

void loop()
{

    leftMotor.write(180);
    Serial.println(180);
    delay(2000);
    leftMotor.write(160);
    Serial.println(160);
    delay(2000);
    leftMotor.write(140);
    Serial.println(140);
    delay(2000);
    leftMotor.write(120);
    Serial.println(120);
    delay(2000);
    leftMotor.write(100);
    Serial.println(100);
    delay(2000);
    leftMotor.write(90);
    Serial.println(90);
    delay(2000);
}