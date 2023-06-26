void controlledLoop()
{
    short LStickX = PS4.LStickX();
    short LStickY = PS4.LStickY();
#ifdef _DEBUG_
    Serial.print("Eixo X do Analogico: ");
    Serial.println(LStickX);
    Serial.print("Eixo Y do Analogico: ");
    Serial.println(LStickY);
#endif

    short leftMotorOutput = constrain(map(LStickY, -127, 127, reverse, forward) + map(LStickX, -127, 127, reverse, forward), reverse, forward);
    short rightMotorOutput = constrain(map(LStickY, -127, 127, reverse, forward) - map(LStickX, -127, 127, reverse, forward), reverse, forward);

    // Zona morta do analógico
    // TODO: Verificar a usabilidade
    //* Caso ele não dispare ao ser ligado ou apresente movimentos não esperados
    if (leftMotorOutput > 95 || leftMotorOutput < 85)
    {
        leftMotor.write(leftMotorOutput);
        delay(interval);
    }
    else
    {
        leftMotor.write(stopped);
        delay(interval);
    };

    if (rightMotorOutput > 95 || rightMotorOutput < 85)
    {
        rightMotor.write(rightMotorOutput);
        delay(interval);
    }
    else
    {
        rightMotor.write(stopped);
        delay(interval);
    };

#ifdef _DEBUG_
    Serial.print("Motor Esquerdo: ");
    Serial.println(leftMotorOutput);
    Serial.print("Motor Direito: ");
    Serial.println(rightMotorOutput);
    Serial.println("-------------------------");
#endif
}