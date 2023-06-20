// Bibliotecas Gerais
#include <Arduino.h>
#include <PS4Controller.h>
#include <ESP32Servo.h>

// Controle
const char *joystickAddress = "94:b9:7e:d5:21:b6"; // Controle do Taka

// Cores de Identificação
#define red 255, 0, 0
#define yellow 255, 255, 0
#define green 0, 255, 0
#define pink 225, 53, 61
#define purple 95, 10, 147

// Motores
constexpr int rightMotorPin = 25;
constexpr int leftMotorPin = 26;

Servo leftMotor;
Servo rightMotor;

constexpr const int OperationFrequency = 50; // Hz
constexpr const int interval = 0;           // ms
constexpr const int movementInterval = 500;  // ms

//* Valores do ESC do Locomotiva
// constexpr const int reverse = 1080; // us
// constexpr const int stopped = 1480;
// constexpr const int forward = 1800;

// TODO: Testar com Valores padrão
constexpr const int reverse = 1000; // us
constexpr const int stopped = 1500;
constexpr const int forward = 2000;

// Modos
// #define _DEBUG_ //* Enquanto a linha abaixo não for um comentário, os valores do controle, LIDAR, receptor infravermelho e motores serão mostrados no monitor serial
// #define _AUTONOMOUS_ //* Ativa o Modo Autônomo, caso esteja comentado o Modo Controlado é ativado
#ifdef _AUTONOMOUS_
#include "autonomous.cpp"
#else
#include "controlled.cpp"
#endif

void setup()
{
  // Alocação de todos os timers
  //* Por padrão, a biblioteca ESP32PWM reserva apenas o Timer 0 para uso. Usando a definição abaixo é permitida a alocação de todos os timers (0, 1, 2 e 3) para uso com a biblioteca.
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Conexão com o joystick
  Serial.begin(300);
  PS4.begin(joystickAddress);

  while (!PS4.isConnected())
  {
#ifdef _DEBUG_
    Serial.println("Disconnected");
#endif
  };

  PS4.setLed(green);
  PS4.sendToController();

  // Vinculando e configurando os motores
  leftMotor.attach(leftMotorPin);
  leftMotor.setPeriodHertz(OperationFrequency);
  leftMotor.writeMicroseconds(stopped);

  rightMotor.attach(rightMotorPin);
  rightMotor.setPeriodHertz(OperationFrequency);
  rightMotor.writeMicroseconds(stopped);

#ifdef _DEBUG_
  Serial.println("Connected");
#endif

#ifdef _AUTONOMOUS_
  autonomousSetup();
  PS4.setLed(pink);
  PS4.sendToController();
#else
  PS4.setLed(purple);
  PS4.sendToController();
#endif
}

void loop()
{
#ifdef _AUTONOMOUS_
  autonomousLoop();
#else
  controlledLoop();
#endif
}