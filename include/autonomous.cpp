#include <IRreciver.cpp>
#include <lidar.cpp>

constexpr const int ready = 0xF30CFF00; // Botão 1
constexpr const int start = 0xE718FF00; // Botão 2
constexpr const int stop = 0xA15EFF00;  // Botão 3

bool readyFlag = true;
bool startFlag = false;

void autonomousSetup()
{
    IRreciverSetup();
    lidarSetup();
}

void autonomousLoop()
{
    // Controle Remoto
    IrReceiver.resume();
    switch (IrReceiver.decodedIRData.decodedRawData)
    {
    case stop:
        while (true)
        {
            leftMotor.write(stopped);
            delay(interval);
            rightMotor.write(stopped);
            delay(interval);

            PS4.setLed(red);
            PS4.sendToController();

#ifdef _DEBUG_
            Serial.print("STOP");
#endif
        }
        break;

    case ready:
    default:
        readyFlag = true;

        PS4.setLed(yellow);
        PS4.sendToController();
#ifdef _DEBUG_
        Serial.print("READY");
#endif
        break;

    case start:
        startFlag = true;

        PS4.setLed(green);
        PS4.sendToController();
#ifdef _DEBUG_
        Serial.print("START");
#endif
        break;
    }

    // TODO: Trocar estratégia
    // TODO: executar estratégia
}