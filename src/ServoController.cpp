#include "ServoController.hpp"
#include <pigpio.h>
#include <iostream>

ServoController::ServoController() {}

bool ServoController::init()
{
    if (gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialize pigpio\n";
        return false;
    }
    return true;
}

// using pigpio's built in function I send PWM Signal through servo1 pin to move the motor to desired angle
void ServoController::moveServo1(int pulseWidth)
{
    gpioServo(servo1Pin, pulseWidth);
}

// using pigpio's built in function I send PWM Signal through servo2 pin to move the motor to desired angle
void ServoController::moveServo2(int pulseWidth)
{
    gpioServo(servo2Pin, pulseWidth);
}

void ServoController::stop()
{
    gpioServo(servo1Pin, 0);
    gpioServo(servo2Pin, 0);
    gpioTerminate();
}