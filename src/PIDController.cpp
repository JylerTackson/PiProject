#include "PIDController.hpp"

PIDController::PIDController(float kp, float ki, float kd)
    : kp(kp), ki(ki), kd(kd), prev_error(0), integral(0),
      output_min(-1000), output_max(1000) {}

void PIDController::reset()
{
    integral = 0;
    prev_error = 0;
}

void PIDController::setTunings(float kp_, float ki_, float kd_)
{
    kp = kp_;
    ki = ki_;
    kd = kd_;
}

void PIDController::setOutputLimits(float min, float max)
{
    output_min = min;
    output_max = max;
}

float PIDController::compute(float setpoint, float input)
{
    float error = setpoint - input;
    integral += error;
    float derivative = error - prev_error;
    prev_error = error;

    float output = kp * error + ki * integral + kd * derivative;

    // Clamp output to limits
    if (output > output_max)
        output = output_max;
    else if (output < output_min)
        output = output_min;

    return output;
}