// Header Guards -- prevent file from being included multiple times during compilation.
#ifndef LIGHTSENSOR_HPP
#define LIGHTSENSOR_HPP

// Gives standard integer types
// uint8_t (8-bit unsigned int)
// uint16_t (16-bit unsigned int)
#include <cstdint>

// Creates our LightSensor Class Blueprint
class LightSensor
{
public:
    LightSensor();      // Constructor
    bool init();        // Initialize I2C connection to the TSL2561 Sensor
    uint16_t readLux(); // Return the current lux reading in the form of uint16

private:
    int i2c_fd;                        // A file descriptor — needed to talk to I2C devices in Linux
    const char *device = "/dev/i2c-1"; // I2C bus on Raspberry Pi
    const uint8_t address = 0x39;      // Default I2C address for TSL2561

    // I2C helper functions
    bool writeByte(uint8_t reg, uint8_t value);  // Sends 1 byte to a sensor register
    bool readWord(uint8_t reg, uint16_t &value); // Reads 2 bytes (a 16-bit word) from the sensor

    // Lux calculation helpers
    bool readRawChannels(uint16_t &ch0, uint16_t &ch1); // Gets raw IR and visible light readings
    uint16_t calculateLux(uint16_t ch0, uint16_t ch1);  // Applies math to convert sensor data into lux
};

#endif