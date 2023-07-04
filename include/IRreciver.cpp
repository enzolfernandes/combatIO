#include <IRremote.hpp>

constexpr const short IRPin = 14;

void IRreciverSetup()
{
    IrReceiver.begin(IRPin, ENABLE_LED_FEEDBACK); // Inicia o receptor infravermelho
}