// Bibliotecas
#include <analogWrite.h>
#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <ESP32Tone.h>
#include <PS4Controller.h>
#include <Wire.h>
#include <VL53L1X.h>
#include "movimentos_basicos.hpp"
#include <IRremote.hpp>

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
constexpr int stopped = 90; // Ponto neutro dos motores, varia de cada ESC, teremos que usar o osciloscópio para saber
constexpr int forward = 0;  // Talvez não seja útil
constexpr int reverse = 0;  // Talvez não seja útil
//lidar 
constexpr int lidarPin = 21,22;
const long ready = 0x80; // Botão 1 do controle remoto  
const long start = 0x81; // Botão 2 do controle remoto 
const long stop = 0x82;  // Botão 3 do controle remoto
short pino_receptor_infravermelho{2};// receptor

void setup()
{
    pinMode(21,22, OUTPUT);// lidar vai enviar dados 
     IrReceiver.begin(pino_receptor_infravermelho);// infravermelho recebe os dados do controle 

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
    if (IrReceiver.decode()) // função ready
    {

        if (IrReceiver.decodedIRData.decodedRawData == ready)
        {
            Serial.println("ready");
            PS4.setLed(yellow); // cor amarela 
            PS4.sendToController();
            lidar.begin(serial); 
             analogWrite(leftmotor, stopped);// motor esquerdo parado
             analogWrite(rightmotor, stopped);// motor direito parado

        }
        else
        {
            Serial.println("not ready");
        };
    }
 if (IrReceiver.decode()) // função start
    {

        if (IrReceiver.decodedIRData.decodedRawData == start)
        {
            if (IS_OK(lidar.waitpoint()))
         {
           float distance = lidar.getCurrentPoint().distance;
              if (lidar.getCurrentPoint().satrtBit)
                {  analogWrite(leftMotor, 180);//motor esquerdo para frente 
                   analogWrite(rightMotor, 180);// motor direito para frente 
                }
            PS4.setLed(green);//cor verde 
            PS4.sendToController();
            Serial.println("start");
         }
        else
          {
            Serial.println("not startted");
          }
        }
    }
 if (IrReceiver.decode()) // função stop
    {     
        PS4.setLed(red);//cor vermelha  
        PS4.sendToController();
        Serial.println("stop");
        if (IrReceiver.decodedIRData.decodedRawData == stop)
     {
        while (true)
        {
          analogWrite(leftmotor, 90);// motor esquerdo parado
          analogWrite(rightmotor, 90);// motor direito parado
        }  
     }

    else
        {
            Serial.println("not stopped");
        }
    }
}
