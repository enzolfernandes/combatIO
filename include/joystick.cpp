#include <PS4Controller.h>

// Controle
const char *joystickAddress = "d0:bc:c1:15:43:ef"; // Controle do Taka

// Cores de Identificação
#define red 255, 0, 0
#define yellow 255, 255, 0
#define orange 255, 140, 0
#define green 0, 255, 0
#define pink 225, 53, 61

void joystickSetup()
{
    PS4.begin(joystickAddress);

    while (!PS4.isConnected())
    {
#ifdef _DEBUG_
        Serial.println("Disconnected");
#endif
    };

#ifdef _DEBUG_
    Serial.println("Connected");
#endif
}
