#include <Wire.h>
#include <VL53L1X.h>

VL53L1X distanceSensor;

void lidarSetup()
{
    Wire.begin();
    Wire.setClock(400 * 10 ^ 3); // 400 kHz para o protocolo I2C
    distanceSensor.setTimeout(500);
    if (!distanceSensor.init())
    {
#ifdef _DEBUG_
        Serial.println(" Sensor não detectado ou iniciado!");
#endif
        while (1);
    }

    distanceSensor.setDistanceMode(VL53L1X::Long);
    distanceSensor.setMeasurementTimingBudget(50000); // us
    distanceSensor.startContinuous(50);               // ms
}

uint16_t lidarReadDistance()
{
#ifdef _DEBUG_
    Serial.print("Distancia (mm): ");
    Serial.println(distanceSensor.read());
    if (distanceSensor.timeoutOccurred())
    {
        Serial.print(" Sensor de Distancia Inoperante");
    }

    Serial.println();
#endif
    return distanceSensor.read(); //mm
}