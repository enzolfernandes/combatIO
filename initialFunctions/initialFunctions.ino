
// Bibliotecas
#include <analogWrite.h>
#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <ESP32Tone.h>
#include <PS4Controller.h>
#include <Wire.h>
#include <VL53L1X.h>
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
constexpr int rightMotorPin= 25;
constexpr int leftMotorPin = 26;
Servo leftMotor;
Servo rightMotor;
constexpr int stopped = 90; // Ponto neutro dos motores, varia de cada ESC, teremos que usar o osciloscópio para saber
constexpr int forward = 180;  // Talvez não seja útil
constexpr int reverse = 0;  // Talvez não seja útil
//lidar 
constexpr int lidarPin = 21,22;
const long ready = 0x80; // Botão 1 do controle remoto  
const long start = 0x81; // Botão 2 do controle remoto 
const long stop = 0x82;  // Botão 3 do controle remoto
short infraRed {2};// receptor

void void setup() {
    pinMode(21,22, OUTPUT);// lidar vai enviar dados 
    IrReceiver.begin(infraRed);// infravermelho recebe os dados do controle 
    
    // PS4.begin("40:99:22:f6:ca:78"); // Controle de Casa
    PS4.begin("e8:d8:19:b9:72:58"); // Controle do Taka
    Serial.begin(9600);
}
void void loop()
{
    
 if (IrReceiver.decode()) 
    {

     if (IrReceiver.decodedIRData.decodedRawData == ready)// função ready 
       {
            Serial.println("ready");
            PS4.setLed(); // cor amarela 
            PS4.sendToController(yellow);
            lidar.begin(serial); 
             analogWrite(leftMotor, stopped);// motor esquerdo parado
             analogWrite(rightMotor, stopped);// motor direito parado

        }
        else
        {
            Serial.println("not ready");
            if (IrReceiver.decodedIRData.decodedRawData == start)// função start 
         {
            if (IS_OK(lidar.waitpoint()))
          {
           float distance = lidar.getCurrentPoint().distance;
              if (lidar.getCurrentPoint().satrtBit)
                {  analogWrite(leftMotor, forward);//motor esquerdo para frente 
                   analogWrite(rightMotor, forward);// motor direito para frente 
                }
            PS4.setLed(green);//cor verde 
            PS4.sendToController();
            Serial.println("start");
          }
         }
        }
         else
          {
            Serial.println("not ready to start");
            if (IrReceiver.decodedIRData.decodedRawData == stop)//função stop 
          {
            PS4.setLed(red);//cor vermelha  
            PS4.sendToController();
            Serial.println("stop");
         while (true)
           {
              analogWrite(leftMotor, stopped);// motor esquerdo parado
              analogWrite(rightMotor, stopped);// motor direito parado
           }  
          }
         }

         else
         {
            Serial.println("not stopped");
         }
    }
}