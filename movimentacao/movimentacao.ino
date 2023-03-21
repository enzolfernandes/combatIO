// Bibliotecas
#include <analogWrite.h>
#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <ESP32Tone.h>
#include <PS4Controller.h>

// Colors
#define red 255, 0, 0
#define green 0, 255, 0
#define blue 0, 0, 255
#define yellow 255, 255, 0
#define pink 225, 53, 61
#define purple 95, 10, 147
#define orange 255, 165, 0

// Motores
constexpr int rightMotorPin = 25;
constexpr int leftMotorPin = 26;

Servo leftMotor;
Servo rightMotor;

constexpr const int stopped = 1480; // Ponto neutro dos motores, varia de cada ESC, teremos que usar o osciloscópio para saber
constexpr const int forward = 1800; // Talvez não seja útil
constexpr const int reverse = 1080; // Talvez não seja útil
constexpr const int intervalo = 50; // ms

void setup()
{
    // PS4.begin("40:99:22:f6:ca:78"); // Controle de Casa
    PS4.begin("e8:d8:19:b9:72:58"); // Controle do Taka
    Serial.begin(9600);

    while (!PS4.isConnected())
    {
        Serial.println("Disconnected");
    };
    PS4.setLed(purple);
    PS4.sendToController();

    leftMotor.attach(leftMotorPin, reverse, forward);
    leftMotor.setPeriodHertz(100); // testar com 48kHz
    leftMotor.writeMicroseconds(stopped);

    rightMotor.attach(rightMotorPin, reverse, forward);
    rightMotor.setPeriodHertz(100);
    rightMotor.writeMicroseconds(stopped);

    Serial.println("Connected");
}

void loop()
{

    if (PS4.isConnected())
    {

        if (PS4.R2() == 1)
        {
            Serial.println("Arma ativada");
            leftMotor.writeMicroseconds(forward); // teste
            delay(intervalo);
        }
        else
        {
            Serial.println("Arma desativada");
        };

        int LStickX = PS4.LStickX();
        int LStickY = PS4.LStickY();

        int leftMotorOutput = constrain(map(LStickY, -128, 127, stopped, forward) + map(LStickX, -127, 127, stopped, forward), stopped, forward);
        int rightMotorOutput = constrain(map(LStickY, -128, 127, stopped, forward) - map(LStickX, -127, 127, stopped, forward), stopped, forward);

        // Zona morta do analógico
        if (leftMotorOutput && rightMotorOutput > 95 || leftMotorOutput && rightMotorOutput < 85)
        {
            leftMotor.writeMicroseconds(leftMotorOutput);
            rightMotor.writeMicroseconds(rightMotorOutput);
            delay(intervalo);
        }
        else
        {
            leftMotor.writeMicroseconds(stopped);
            rightMotor.writeMicroseconds(stopped);
            delay(intervalo);
        };

        Serial.print("Motor Esquerdo: ");
        Serial.println(leftMotorOutput);
        Serial.print("Motor Direito: ");
        Serial.println(rightMotorOutput);
        Serial.println("-------------------------");
    }
    else
    {
        leftMotor.writeMicroseconds(stopped);
        rightMotor.writeMicroseconds(stopped);
        delay(intervalo);
    };
}
