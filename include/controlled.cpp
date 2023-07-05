constexpr const short deadZone = 5;
constexpr const short minimumJoystickValue = -127;
constexpr const short maximumJoystickValue = 127;

short x = 0, y = 0, mapXValue = 0, mapYValue = 0;

void controlledLoop()
{
        if (PS4.isConnected())
        {
                x = PS4.LStickX();
                mapXValue = map(x, minimumJoystickValue, maximumJoystickValue, reverse, forward);

                y = PS4.LStickY();
                mapYValue = map(y, minimumJoystickValue, maximumJoystickValue, reverse, forward);

#ifdef _DEBUG_
                Serial.println("----------");
                Serial.print("Eixo X do Analogico: ");
                Serial.println(x);
                Serial.print("Eixo X Re-mapeado: ");
                Serial.println(mapXValue);

                Serial.print("Eixo Y do Analogico: ");
                Serial.println(y);
                Serial.print("Eixo Y Re-mapeado: ");
                Serial.println(mapYValue);
#endif

                if (x ^ 2 + y ^ 2 == deadZone ^ 2)
                {
                        leftMotor.write(stopped);
                        rightMotor.write(stopped);
#ifdef _DEBUG_
                        Serial.println("Zona Morta");
#endif
                }
                else if (x > -deadZone && x < deadZone)
                {
                        leftMotor.write(constrain(mapYValue, reverse, forward));
                        rightMotor.write(constrain(mapYValue, reverse, forward));

#ifdef _DEBUG_
                        Serial.println("Zona de Movimento Linear");
                        Serial.print("Valor enviado aos motores: ");
                        Serial.println(constrain(mapYValue, reverse, forward));
#endif
                }
                else if (x < -deadZone || x > deadZone)
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
        }
}