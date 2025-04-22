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

###### Linux Philosiphy:

- When running Linux, hardware is exposed as if it were a file. This is part of the 'Unix philosiphy'
  - Everything is a file

###### I2C Communication:

- When you refer to an i2C device file you are referring to a special file that represents the I2C bus that connects

  - An I2C bus refers to the two physical wires that creates a shared communication channel between the master and slave.
    - SCL: Serial Clock Line
      - Sets the pace for communication
    - SDA: Serial Data Line
      - Carries the Actual Data

- In this project I am wiring up the TSL2561 Sensor to the Pi through the 3 and 5 pins.
  - 3 Pin is the SDA
  - 5 Pin is the SCL
- However, by using the I2C device file:
  ```
  const char* device = "/dev/i2c-1";
  ```
  - We do neet to map indivual pins. The Linux Kernal I2C driver takes care of communicating with the correct phyiscal pins.

###### PWM Motor Control:

- When controller a Motor using PWM signals you are using the signal to tell the motor what angle to go to.
  - The motoro will ALWAYS take the shortest path to that angle, unless physically constrained
  - The SG90 Micro Servo's have an view angle of 180 degrees.
- What happens when you send a PWM signal to the servo:
  1. Compares its current angle to the target
  2. Applies voltage internally to move toward that angle
  3. Stops when it reaches it
- What if you want Continous Motor Movement?
  - A 360 degree continuous rotation servo treate PWM as speed and direction
    - 1500 mus = stop
    - < 1500 mus = spin one direction
    - > 1500 mus = spin other direction

###### PID Encoder:

- PID stands for Proportaional Integral Derivative.
  - P: How far off the target you are.
  - I: How long you've been off.
  - D: How quickly the error is changing.
- It is a type of feedback control system that adjusts an ouput based on the difference between a desired and actual value.
