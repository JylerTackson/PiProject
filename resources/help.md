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
