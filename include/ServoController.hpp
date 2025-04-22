// Header Guards
#ifndef SERVOCONTROLLER_HPP
#define SERVOCONTROLLER_HPP

// Create ServoController Class
class ServoController
{
public:
    // ServoController Instance
    ServoController();
    bool init();
    void moveServo1(int pulseWidth);
    void moveServo2(int pulseWidth);
    void stop();

private:
    // Output GPIOS from RaspPi
    const int servo1Pin = 32; // GPIO32
    const int servo2Pin = 33; // GPIO33
};

#endif