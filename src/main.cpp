#include <Arduino.h>
#include <joystick.cpp>
#include <motors.cpp>

// ! Modos
//* Enquanto a linha abaixo não for um comentário, a referente parte não será compilada
// #define _DEBUG_
// #define _AUTONOMOUS_

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

  motorsAttach();

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