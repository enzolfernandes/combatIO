#include <unity.h>
#include <joystick.cpp>
#include <IRreciver.cpp>
#include <lidar.cpp>
#include <motors.cpp>

void test_IRdecode(void)
{
    bool valueReceived = false;
    IrReceiver.resume(); // habilita para receber algum valor
    while (!valueReceived)
    {

        if (IrReceiver.decode())
        {

            TEST_ASSERT_GREATER_THAN_HEX32(0, IrReceiver.decodedIRData.decodedRawData); // Botão Play/Pause
            valueReceived = true;
        }
    }
}

void test_lidar(void)
{
}

void test_motors(void)
{
    leftMotor.write(reverse);
    rightMotor.write(reverse);
    delay(2000);
    leftMotor.write(stopped);
    rightMotor.write(stopped);
    delay(2000);
    leftMotor.write(forward);
    rightMotor.write(forward);
    delay(2000);
    leftMotor.detach();
    rightMotor.detach();

    TEST_ASSERT(true);
}

void setup()
{
    UNITY_BEGIN();
    joystickSetup();
    IRreciverSetup();
    lidarSetup();
    motorsSetup();
    PS4.setLed(orange);
    PS4.sendToController();
}

void loop()
{
    RUN_TEST(test_IRdecode);
    RUN_TEST(test_motors);
    PS4.setLed(green);
    PS4.sendToController();
    UNITY_END();
}