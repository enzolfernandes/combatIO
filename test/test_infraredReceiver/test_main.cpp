#include <unity.h>
#include <joystick.cpp>
#include <IRremote.hpp>

constexpr const short IRPin = 14;

void test_IRdecode(void)
{
  if (IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    IrReceiver.resume();                    // habilita para receber o próximo valor

    PS4.setLed(green);
    PS4.sendToController();
  }
}

void setup()
{
  UNITY_BEGIN();
  Serial.begin(1200);
  joystickSetup();
  PS4.setLed(orange);
  PS4.sendToController();
  IrReceiver.begin(IRPin, ENABLE_LED_FEEDBACK); // Inicia o receptor infravermelho
}

void loop()
{
  RUN_TEST(test_IRdecode);
  if (PS4.Cross() == 1)
  {
    UNITY_END();
  }
}