// ! Modos
//* Enquanto a linha abaixo não for um comentário, a referente parte não será compilada
// #define _DEBUG_

#include <Arduino.h>
#include "joystick.cpp"
#include "motors.cpp"
#include "controlled.cpp"

void setup()
{
  // Alocação de todos os timers
  //* Por padrão, a biblioteca ESP32PWM reserva apenas o Timer 0 para uso. Usando a definição abaixo é permitida a alocação de todos os timers (0, 1, 2 e 3) para uso com a biblioteca.
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

#ifdef _DEBUG_
  Serial.begin(1200);
#endif
  joystickSetup();
  motorsSetup();
}

void loop()
{
  controlledLoop();
}