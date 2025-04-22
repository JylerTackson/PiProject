#include "PIDController.hpp"

PIDController::PIDController(float kp, float ki, float kd)
    : kp(kp), ki(ki), kd(kd), prev_error(0), integral(0),
      output_min(-1000), output_max(1000) {}

// Resets the internal state of the PID controller for a new calculation
void PIDController::reset()
{
    integral = 0;
    prev_error = 0;
}

// Updates the PIDs tuning parameters for calculations
void PIDController::setTunings(float kp_, float ki_, float kd_)
{
    kp = kp_;
    ki = ki_;
    kd = kd_;
}

// Sets the output limits for the PID controller
// This is used to prevent integral windup by clamping the output
void PIDController::setOutputLimits(float min, float max)
{
    output_min = min;
    output_max = max;
}

// Computes the control signal based on the current input and desired setpoint
float PIDController::compute(float setpoint, float input)
{
    // Error between desired and current
    float error = setpoint - input;

    // Integrate the error over time and calculate the derivative
    integral += error;
    float derivative = error - prev_error;

    // Store current error for next iteration
    prev_error = error;

    // Compute the PID
    float output = kp * error + ki * integral + kd * derivative;

    // Clamp output to limits
    if (output > output_max)
        output = output_max;
    else if (output < output_min)
        output = output_min;

    return output;
}