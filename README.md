# PiProject

Raspberry Pi Project using cameras to track the target

# “C++ Smart Target Tracker on Raspberry Pi”

###### Current Identified Dependencies:

1. OpenCV
2. pigpio
3. Eigen
4. Catch2
5. CMake
6. g++/gcc/make

## Project Overview:

1. Track a colored object (Red)
   - Using OpenCV to capture video stream and apply filters
2. Dynamically adjust camera exposure based on ambient light
   - Using TSL2561 via I2C
   - Using ExposureManager to convert lux → exposure
3. Moves servo to keep target centered (PID)
   - Using pigpio to communicate with servos using PWM signals
4. Displays output and writes logs
   - Standard C++ std::ofstream to write .log file
   - Using OpenCV to display visual feedback of tracking
5. Includes unit tests and auto-generated Doxygen documentation
   - Catch2 testing framework to write test cases
   - (Optional) Doxygen to scan .hpp & .cpp and automate documentation

### Files:

##### KalmanFilter.cpp

Purpose: Implements a basic Kalman filter for smoothing TOF angle data

###### Responsibilities:

1. Maintain internal state vectors and matrices
2. Predict and update steps using Eigen for matrix math
3. Return filtered sensor values to be used by the servo controller

##### PIDController.cpp

Purpose: Implements PID control logic

###### Responsibilities:

1. Calculate error between current and target position
2. Apply proportional, integral, and derivative adjustments
3. Return a servo command (e.g., PWM pulse width)

##### Tracker.cpp

Purpose: Handles OpenCV-based red object detection

###### Responsibilities:

1. Capture video frames
2. Apply HSV filtering and contour detection
3. Return object coordinates (e.g., x-position in the frame)

##### LightSensor.cpp

Purpose: Measure ambient light in lux using TSL2561 via GPIO/I2C

###### Responsibilities:

1. Communicate with the sensor using pigpio or other libraries
2. Return lux to Exposure Manager for processing.

##### ExposureManager.cpp

Purpose: Reaceives the Lux Measuerment and creates a dynamic exposure for the camera.

###### Responsibilities:

1. Communicate with the camera using openCV or other libraries.
2. Create a dynamic exposure for better object tracking using the camera.

##### ServoController.cpp

Purpose: Sends PWM signals to move the servo based on PID output

###### Responsibilities:

1. Use pigpio to generate PWM on a GPIO pin
2. Convert control values into pulse widths
3. Center, limit, and stabilize servo motion

### Hardware:

1. Raspberry Pi 3 B+
2. Camera: OV5647 Camera Module
3. Luminosity Sensor: TSL2561
4. Servo: WWZMDiB SG90 Micro Servo
