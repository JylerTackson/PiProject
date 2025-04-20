# PiProject

Raspberry Pi Project using cameras to track the target

### “C++ Smart Target Tracker on Raspberry Pi”

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

What is a header file and why do we need them?

- The header files are used to declare things such as classes, functions, and constsants but NOT to define these declarations. They can be thought of as blueprints that the cpp file follows and constructs.
  - Seperation of interface and implementation
  - Avoiding code duplication
  - Allowing modular compilation

What is CMakeLists.txt?

- This file is an instructional text file that tells your compiler how to compile your main application.

How does the .sh file work?

- .sh is a shell script file that is a batch of terminal commands for Unix-based systems
- Use .sh files for setup, service restarts, data backups, log cleaners, etc.
