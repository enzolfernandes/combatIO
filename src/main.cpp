// ! Modos
//* Enquanto a linha abaixo não for um comentário, a referente parte não será compilada
// #define _DEBUG_
// #define _AUTONOMOUS_

#include <joystick.cpp>
#include <motors.cpp>

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

#ifdef _DEBUG_
  Serial.begin(1200);
#endif
  joystickSetup();
  motorsSetup();

#ifdef _AUTONOMOUS_
  autonomousSetup();
  PS4.setLed(pink);
  PS4.sendToController();
  delay(1000);
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