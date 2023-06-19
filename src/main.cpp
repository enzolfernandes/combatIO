// Debug
// #define _DEBUG_ // Enquanto essa linha não for um comentário, os valores do controle, LIDAR, receptor infravermelho e motores serão mostrados no monitor serial

// Bibliotecas Gerais
#include <Arduino.h>
#include <PS4Controller.h>
#include <ESP32Servo.h>

// Headers
#include "autonomous.cpp"
#include "controlled.cpp"

// Controle
const char *joystickAddress = "94:b9:7e:d5:21:b6"; // Controle do Taka

// Cores de Identificação
#define red 255, 0, 0
#define green 0, 255, 0
#define blue 0, 0, 255
#define yellow 255, 255, 0
#define pink 225, 53, 61
#define purple 95, 10, 147
#define orange 255, 165, 0

// Motores
constexpr int rightMotorPin = 25;
constexpr int leftMotorPin = 26;

Servo leftMotor;
Servo rightMotor;

constexpr const int stopped = 1480; // ms
constexpr const int forward = 1800;
constexpr const int reverse = 1080;
constexpr const int interval = 50;

void setup()
{
  // Alocação de todos os timers
  //? Não descobrimos o utilidade disso ainda, mas é utilizados em todos os exemplos da biblioteca ESP32Servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  Serial.begin(300);
  PS4.begin(joystickAddress);

  #ifdef _DEBUG_
  while (!PS4.isConnected())
  {
    Serial.println("Disconnected");
  };
  #endif

  PS4.setLed(green);
  PS4.sendToController();
}
void loop()
{
}