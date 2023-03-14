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
Servo.attach(leftMotorPin, 1080, 1800);
Servo.attach(rightMotorPin, 1080, 1800);
constexpr int stopped = 1480; // Ponto neutro dos motores, varia de cada ESC, teremos que usar o osciloscópio para saber
constexpr int forward = 1800;  // Talvez não seja útil
constexpr int reverse = 1080;  // Talvez não seja útil

void setup()
{
    // PS4.begin("40:99:22:f6:ca:78"); // Controle de Casa
    PS4.begin("e8:d8:19:b9:72:58"); // Controle do Taka
    Serial.begin(9600);

    while (!PS4.isConnected())
    {
        Serial.println("Disconnected");
        delay(50);
    };
    PS4.setLed(purple);
    PS4.sendToController();

    leftMotor.attach(leftMotorPin);
    rightMotor.attach(rightMotorPin);
    leftMotor.write(stopped);
    rightMotor.write(stopped);

    Serial.println("Connected");
}

void loop()
{

    if (PS4.isConnected())
    {

        if (PS4.R2() == 1)
        {
            Serial.println("Arma ativada");
        }
        else
        {
            Serial.println("Arma desativada");
        };

        int LStickX = PS4.LStickX();
        int LStickY = PS4.LStickY();

        int leftMotorOutput = constrain(map(LStickY, -128, 127, 0, 180) + map(LStickX, -127, 127, 0, 180), 0, 180);
        int rightMotorOutput = constrain(map(LStickY, -128, 127, 0, 180) - map(LStickX, -127, 127, 0, 180), 0, 180);

        // Zona morta do analógico
        if (leftMotorOutput && rightMotorOutput > 95 || leftMotorOutput && rightMotorOutput < 85)
        {
            leftMotor.write(leftMotorOutput);
            rightMotor.write(rightMotorOutput);
        }
        else
        {
            leftMotor.write(stopped);
            rightMotor.write(stopped);
        };

        Serial.print("Motor Esquerdo: ");
        Serial.println(leftMotorOutput);
        Serial.print("Motor Direito: ");
        Serial.println(rightMotorOutput);
        Serial.println("-------------------------");
    }
    else
    {
        leftMotor.write(stopped);
        rightMotor.write(stopped);
    };
}
