// Header Guards
#ifndef PIDCONTROLLER_HPP
#define PIDCONTROLLER_HPP

class PIDController
{
public:
    PIDController(float kp, float ki, float kd);

    void reset(); // Resets integral and previous error
    void setTunings(float kp, float ki, float kd);
    void setOutputLimits(float min, float max);

    float compute(float setpoint, float input);

private:
    float kp, ki, kd;
    float prev_error;
    float integral;
    float output_min, output_max;
};

#endif