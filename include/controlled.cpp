constexpr const short minimumTriggerValue = 0;
constexpr const short maximumTriggerValue = 255;

constexpr const short minimumStickValue = -127;
constexpr const short maximumStickValue = 127;
constexpr const short deadZone = 15;
constexpr const short linearZone = deadZone + 10;

short x = 0, y = 0, mapXValue = 0, mapYValue = 0;

void controlledLoop()
{
        if (PS4.isConnected())
        {

                // Locomoção
                x = PS4.LStickX();
                mapXValue = map(x, minimumStickValue, maximumStickValue, reverse, forward);

                y = PS4.LStickY();
                mapYValue = map(y, minimumStickValue, maximumStickValue, reverse, forward);

#ifdef _DEBUG_
                Serial.print("Eixo X do Analogico: ");
                Serial.println(x);
                Serial.print("Eixo X Re-mapeado: ");
                Serial.println(mapXValue);

                Serial.print("Eixo Y do Analogico: ");
                Serial.println(y);
                Serial.print("Eixo Y Re-mapeado: ");
                Serial.println(mapYValue);
#endif

                if ((pow(x, 2) + pow(y, 2)) <= pow(deadZone, 2)) // Interior do Círculo de Zona Morta
                {
                        leftMotor.write(stopped);
                        rightMotor.write(stopped);
#ifdef _DEBUG_
                        Serial.println("Zona Morta");
#endif
                }
                else if (-linearZone < x < linearZone)
                {
                        leftMotor.write(constrain(mapYValue, reverse, forward));
                        rightMotor.write(constrain(mapYValue, reverse, forward));

#ifdef _DEBUG_
                        Serial.println("Zona de Movimento Linear");
                        Serial.print("Valor enviado aos motores: ");
                        Serial.println(constrain(mapYValue, reverse, forward));
#endif
                }
                else if (x < -linearZone || x > linearZone)
                {
                        leftMotor.write(constrain((mapYValue + mapXValue), reverse, forward));
                        rightMotor.write(constrain((mapYValue - mapXValue), reverse, forward));

#ifdef _DEBUG_
                        Serial.println("Zona de Movimento Curvo");
                        Serial.print("Valor enviado ao motor Esquerdo: ");
                        Serial.println(constrain((mapYValue + mapXValue), reverse, forward));
                        Serial.print("Valor enviado ao motor Direto: ");
                        Serial.println(constrain((mapYValue - mapXValue), reverse, forward));
#endif
                }
        }
        else
        {
                leftMotor.write(stopped);
                rightMotor.write(stopped);
                weapon.write(stopped);
        }
}