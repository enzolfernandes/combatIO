#include <unity.h>
#include <joystick.cpp>
#include <motors.cpp>

void setup()
{
    motorsAttach();
}
void loop()
{
    if (PS4.L2() == 1)
    {
        leftMotor.write(forward);
        delay(interval);
    }
    else if (PS4.L1() == 1)
    {
        leftMotor.write(reverse);
        delay(interval);
    }
    else
    {
        leftMotor.write(stopped);
        delay(interval);
    };

    if (PS4.R2() == 1)
    {
        rightMotor.write(forward);
        delay(interval);
    }
    else if (PS4.R1() == 1)
    {
        rightMotor.write(reverse);
        delay(interval);
    }
    else
    {
        rightMotor.write(stopped);
        delay(interval);
    };
}