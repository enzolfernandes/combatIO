void controlledLoop()
{
    int LStickX = PS4.LStickX();
    int LStickY = PS4.LStickY();

    int leftMotorOutput = constrain(map(LStickY, -127, 127, reverse, forward) + map(LStickX, -127, 127, reverse, forward), reverse, forward);
    int rightMotorOutput = constrain(map(LStickY, -127, 127, reverse, forward) - map(LStickX, -127, 127, reverse, forward), reverse, forward);

    // Zona morta do analógico
    // TODO: Verificar a usabilidade
    //* Caso ele não dispare ao ser ligado ou apresente movimentos não esperados
    // if(leftMotorOutput > 95 || leftMotorOutput < 85)
    // {
    //     leftMotor.writeMicroseconds(leftMotorOutput);
    //     delay(interval);
    // }
    // else
    // {
    //     leftMotor.writeMicroseconds(stopped);
    //     delay(interval);
    // };

    // if(rightMotorOutput > 95 || rightMotorOutput < 85)
    // {
    //     rightMotor.writeMicroseconds(rightMotorOutput);
    //     delay(interval);
    // }
    // else
    // {
    //     rightMotor.writeMicroseconds(stopped);
    //     delay(interval);
    // };

#ifdef _DEBUG_
    Serial.print("Motor Esquerdo: ");
    Serial.println(leftMotorOutput);
    Serial.print("Motor Direito: ");
    Serial.println(rightMotorOutput);
    Serial.println("-------------------------");
#endif
}