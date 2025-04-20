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
2. Reads TOF sensor via GPIO pin and filters angle using a Kalman filter
   - Using pigpio to communicate with sensors
   - Using Eigen for matrix calculations
3. Moves servo to keep target centered (PID)
   - Using pigpio to communicate with servos using PWM signals
4. Displays output and writes logs
   - Standard C++ std::ofstream to write .log file
   - Using OpenCV to display visual feedback of tracking
5. Includes unit tests and auto-generated Doxygen documentation
   - Catch2 testing framework to write test cases
   - (Optional) Doxygen to scan .hpp & .cpp and automate documentation

###### What is a header file and why do we need them?

- The header files are used to declare things such as classes, functions, and constsants but NOT to define these declarations. They can be thought of as blueprints that the cpp file follows and constructs.
  - Seperation of interface and implementation
  - Avoiding code duplication
  - Allowing modular compilation

###### What is CMakeLists.txt?

- This file is an instructional text file that tells your compiler how to compile your main application.

###### How does the .sh file work?

- .sh is a shell script file that is a batch of terminal commands for Unix-based systems
- Use .sh files for setup, service restarts, data backups, log cleaners, etc.

###### Workflow:

- I am using my windows machine and using VSCODE then going over to my raspberry Pi and cloning the repo.
- Once on the Pi I need to use the Advanced Package Tool (apt) to do multiple things:
  1.  Install openCV
  2.  Install pigpio
  3.  ReClone eigen
  4.  ReClone Catch2
  5.  Install CMake
  6.  Install g++/gcc/make

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

##### SensorManager.cpp

Purpose: Reads distance or angle data from the TOF sensor via GPIO/I2C

###### Responsibilities:

1. Communicate with the sensor using pigpio or other libraries
2. Return raw sensor data to be passed into the Kalman filter

##### ServoController.cpp

Purpose: Sends PWM signals to move the servo based on PID output

###### Responsibilities:

1. Use pigpio to generate PWM on a GPIO pin
2. Convert control values into pulse widths
3. Center, limit, and stabilize servo motion
