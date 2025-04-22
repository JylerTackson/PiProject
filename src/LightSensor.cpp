#include "LightSensor.hpp"
#include <fcntl.h>         // Provides file control options like open(), O_RDWR (used to access /dev/i2c-1)
#include <unistd.h>        // Gives access to system calls like read(), write(), and close()
#include <sys/ioctl.h>     // Allows low-level control of hardware using ioctl(), including I2C commands
#include <linux/i2c-dev.h> // Contains I2C-specific definitions like I2C_SLAVE (used to set device address)
#include <iostream>        // Enables logging and error output using std::cerr and std::cout

// Command bit used for register access
// When communicating, the sensor expects you to prefix every register access with a command byte.
// Tells the sensor you’re about to send a register command
#define CMD 0x80

// REG_Control is the register that turns on and off the sensor
#define REG_CONTROL 0x00
#define POWER_ON 0x03
#define POWER_OFF 0x00

#define REG_TIMING 0x01 // Exposure timing & Gain settings (controls the amount of time the sensor is reading)
#define REG_CH0 0x0C    // Raw BroadBand Light
#define REG_CH1 0x0E    // Raw IR Light

// Constructor that initializes the I2C file descriptor to -1
LightSensor::LightSensor() : i2c_fd(-1) {}

// Initializes the I2C connection to the TSL2561 sensor and powers it on
bool LightSensor::init()
{
    i2c_fd = open(device, O_RDWR);
    if (i2c_fd < 0)
    {
        std::cerr << "Failed to open I2C device\n";
        return false;
    }

    if (ioctl(i2c_fd, I2C_SLAVE, address) < 0)
    {
        std::cerr << "Failed to acquire I2C bus access\n";
        return false;
    }

    // Power on the sensor
    return writeByte(CMD | REG_CONTROL, POWER_ON);
}

// Writes a single byte value to a specified register on the sensor
bool LightSensor::writeByte(uint8_t reg, uint8_t value)
{
    uint8_t buffer[2] = {reg, value};
    return write(i2c_fd, buffer, 2) == 2;
}

// Reads a 16-bit word (2 bytes) from a specified register on the sensor
bool LightSensor::readWord(uint8_t reg, uint16_t &value)
{
    uint8_t buf[2];
    if (write(i2c_fd, &reg, 1) != 1 || read(i2c_fd, buf, 2) != 2)
    {
        return false;
    }
    value = buf[1] << 8 | buf[0];
    return true;
}

// Reads raw 16-bit values from both channel 0 (broadband) and channel 1 (IR)
bool LightSensor::readRawChannels(uint16_t &ch0, uint16_t &ch1)
{
    return readWord(CMD | REG_CH0, ch0) && readWord(CMD | REG_CH1, ch1);
}

// Calculates and returns the lux value based on raw channel data using TSL2561's lux formula
uint16_t LightSensor::calculateLux(uint16_t ch0, uint16_t ch1)
{
    if (ch0 == 0)
        return 0;

    float ratio = static_cast<float>(ch1) / static_cast<float>(ch0);
    float lux = 0;

    if (ratio <= 0.5)
        lux = (0.0304 * ch0) - (0.062 * ch0 * pow(ratio, 1.4));
    else if (ratio <= 0.61)
        lux = (0.0224 * ch0) - (0.031 * ch1);
    else if (ratio <= 0.80)
        lux = (0.0128 * ch0) - (0.0153 * ch1);
    else if (ratio <= 1.30)
        lux = (0.00146 * ch0) - (0.00112 * ch1);
    else
        lux = 0;

    return static_cast<uint16_t>(lux);
}

// Returns the computed lux value after reading both sensor channels
uint16_t LightSensor::readLux()
{
    uint16_t ch0 = 0, ch1 = 0;
    if (!readRawChannels(ch0, ch1))
    {
        std::cerr << "Failed to read light channels\n";
        return 0;
    }
    return calculateLux(ch0, ch1);
}