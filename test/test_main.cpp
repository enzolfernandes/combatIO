#include <unity.h>
#include <joystick.cpp>
#include <IRreciver.cpp>
#include <lidar.cpp>
#include <motors.cpp>

// Testes de Setup
void test_joystickSetup(void)
{
    joystickSetup();
    TEST_ASSERT(true);
}

void test_IRreciverSetup(void)
{
    IRreciverSetup();
    TEST_ASSERT(true);
}

void test_lidarSetup(void)
{
    lidarSetup();
    TEST_ASSERT(true);
}

void test_motorsSetup(void)
{
    motorsSetup();
    TEST_ASSERT(true);
}

// Testes de Loop
void test_joystick(void)
{
    TEST_ASSERT(PS4.isConnected() == true);
}

void test_IRdecode(void)
{
    bool valueReceived = false;
    IrReceiver.resume(); // habilita para receber algum valor
    while (!valueReceived)
    {

        if (IrReceiver.decode())
        {

            TEST_ASSERT_GREATER_THAN_HEX32(0, IrReceiver.decodedIRData.decodedRawData);
            valueReceived = true;
        }
    }
}

void test_lidar(void)
{
    TEST_ASSERT_GREATER_THAN_INT16(0, lidarReadDistance());
}

void test_motors(void)
{
    leftMotor.write(forward);
    rightMotor.write(forward);
    weapon.write(forward);
    delay(2000);
    leftMotor.write(stopped);
    rightMotor.write(stopped);
    weapon.write(stopped);
    delay(2000);
    leftMotor.write(reverse);
    rightMotor.write(reverse);
    weapon.write(reverse);
    delay(2000);
    leftMotor.write(stopped);
    rightMotor.write(stopped);
    weapon.write(stopped);
    delay(2000);
    TEST_ASSERT(true);
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_joystickSetup);
    RUN_TEST(test_IRreciverSetup);
    RUN_TEST(test_lidarSetup);
    RUN_TEST(test_motorsSetup);

    PS4.setLed(orange);
    PS4.sendToController();
}

void loop()
{
    RUN_TEST(test_joystick);
    RUN_TEST(test_IRdecode);
    RUN_TEST(test_lidar);
    RUN_TEST(test_motors);

    PS4.setLed(green);
    PS4.sendToController();
    UNITY_END();
}