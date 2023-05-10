//Bibliotecas

#include <Wire.h>
#include <analogWrite.h>
#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <ESP32Tone.h>
#include <VL53L1X.h>

// Motores
constexpr int rightMotorPin = 25;
constexpr int leftMotorPin = 26;
Servo leftMotor;
Servo rightMotor;
constexpr int stopped = 90; // Ponto neutro dos motores, varia de cada ESC, teremos que usar o osciloscópio para saber
constexpr int forward = 180;  // Talvez não seja útil
constexpr int reverse = 0;  // Talvez não seja útil
constexpr int spinsearch = 135; //velocidade de giro

VL53L1X sensor;

void setup()
{
  // Iniciando Sensor
  while (!Serial) {}
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); 

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);

  leftMotor.attach(leftMotorPin);
  rightMotor.attach(rightMotorPin);
  leftMotor.write(stopped);
  rightMotor.write(stopped);
}

void loop()
{
  //Procurar inimigo
  Serial.print(sensor.read());

  if(sensor.read() > 1000) //distância lida for maior que 1m o Shenbong gira 
  {
    leftMotor.write(spinsearch);
    rightMotor.write(spinsearch-90);
    delay(200);

    leftMotor.write(stopped);
    rightMotor.write(stopped);
    delay(200);

  } 

  //Atacar inimigo
  if(sensor.read() <= 1000) //distância lida menor do que 1m o Shenbong ataca
  {
    leftMotor.write(forward);
    rightMotor.write(forward);
  }

  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();

}