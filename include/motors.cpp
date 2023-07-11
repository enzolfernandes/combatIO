#include <ESP32Servo.h>

constexpr const short rightMotorPin = 25;
constexpr const short leftMotorPin = 26;

constexpr const short OperationFrequency = 50; // Hz
constexpr const short interval = 0;            // ms
constexpr const short movementInterval = 500;  // ms

constexpr const short minimumPulseWidth = 920;  // us, Padrão: 1000us, Funcional: 1080us
constexpr const short maximumPulseWidth = 1920; // us

constexpr const short reverse = 0; // graus
constexpr const short stopped = 90;
constexpr const short forward = 180;

Servo leftMotor;
Servo rightMotor;

void motorsSetup()
{
    leftMotor.setPeriodHertz(OperationFrequency);
    leftMotor.attach(leftMotorPin, minimumPulseWidth, maximumPulseWidth);
    leftMotor.write(stopped);

    rightMotor.setPeriodHertz(OperationFrequency);
    rightMotor.attach(rightMotorPin, minimumPulseWidth, maximumPulseWidth);
    rightMotor.write(stopped);
}