#include <unity.h>
#include <joystick.cpp>
#include <motors.cpp>

// Testes de Setup
void test_joystickSetup(void)
{
    joystickSetup();
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

void test_motors(void)
{
    leftMotor.write(forward);
    rightMotor.write(forward);
    delay(2000);
    leftMotor.write(stopped);
    rightMotor.write(stopped);
    delay(2000);
    leftMotor.write(reverse);
    rightMotor.write(reverse);
    delay(2000);
    leftMotor.write(stopped);
    rightMotor.write(stopped);
    delay(2000);
    TEST_ASSERT(true);
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_joystickSetup);
    RUN_TEST(test_motorsSetup);

    PS4.setLed(orange);
    PS4.sendToController();
}

void loop()
{
    RUN_TEST(test_joystick);
    RUN_TEST(test_motors);

    PS4.setLed(green);
    PS4.sendToController();
    UNITY_END();
}