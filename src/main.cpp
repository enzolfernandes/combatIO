// Bibliotecas Gerais
#include <Arduino.h>
#include <PS4Controller.h>
#include <ESP32Servo.h>

// Controle
const char *joystickAddress = "2c:dc:d7:1b:3c:0a"; // Controle do Taka

// Cores de Identificação
#define red 255, 0, 0
#define yellow 255, 255, 0
#define green 0, 255, 0
#define pink 225, 53, 61

// Motores
constexpr int rightMotorPin = 25;
constexpr int leftMotorPin = 26;

Servo leftMotor;
Servo rightMotor;

constexpr const int OperationFrequency = 50; // Hz
constexpr const int interval = 5;            // ms
constexpr const int movementInterval = 500;  // ms

constexpr const int reverse = 0; // graus
constexpr const int stopped = 90;
constexpr const int forward = 180;

// TODO: Fazer um Mode.cpp contendo essa parte de modos
// Modos
#define _DEBUG_ //* Enquanto a linha abaixo não for um comentário, os valores do controle, LIDAR, receptor infravermelho e motores serão mostrados no monitor serial
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
  Serial.begin(1200);
  PS4.begin(joystickAddress);

  while (!PS4.isConnected())
  {
#ifdef _DEBUG_
    Serial.println("Disconnected");
#endif
  };

#ifdef _DEBUG_
  Serial.println("Connected");
#endif

  // Vinculando e configurando os motores
  leftMotor.attach(leftMotorPin);
  leftMotor.setPeriodHertz(OperationFrequency);
  leftMotor.write(stopped);

  rightMotor.attach(rightMotorPin);
  rightMotor.setPeriodHertz(OperationFrequency);
  rightMotor.write(stopped);

#ifdef _AUTONOMOUS_
  autonomousSetup();
  PS4.setLed(pink);
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