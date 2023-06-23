#include <ESP32Servo.h>

constexpr const short rightMotorPin = 25;
constexpr const short leftMotorPin = 26;

constexpr const short OperationFrequency = 50; // Hz
constexpr const short interval = 5;            // ms
constexpr const short movementInterval = 500;  // ms

constexpr const short minimumPulseWidth = 500;  // us, Padrão: 1000us, Funcional: 1080us
constexpr const short maximumPulseWidth = 2000; // us

constexpr const short reverse = 0; // graus
constexpr const short stopped = 90;
constexpr const short forward = 180;

Servo leftMotor;
Servo rightMotor;

void motorsAttach()
{
    leftMotor.attach(leftMotorPin, minimumPulseWidth, maximumPulseWidth);
    leftMotor.setPeriodHertz(OperationFrequency);
    leftMotor.write(stopped);

    rightMotor.attach(rightMotorPin, minimumPulseWidth, maximumPulseWidth);
    rightMotor.setPeriodHertz(OperationFrequency);
    rightMotor.write(stopped);
}