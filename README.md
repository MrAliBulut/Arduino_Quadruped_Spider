# Quadruped Spider Robot

## Project Banner (in Turkish)

![QSRBPoster](https://github.com/MrAliBulut/Arduino_Quadruped_Spider/assets/95712617/a9a58923-a293-4d81-91e7-b787436f6a17)

## TinkerCAD


![QSRBPoster_Back](https://github.com/MrAliBulut/Arduino_Quadruped_Spider/assets/95712617/283c9688-e093-4ba3-a85f-060aa71e3c30)



## Overview

This project involves the creation of a Quadruped Spider Robot using Robotistan's template. The robot is controlled through an Arduino board, featuring an IR remote control for easy maneuvering. The project is divided into three main components: IR Code Finder, Servo Configuration, and the Quadruped Spider Robot.

## Components


### 1. IR Code Finder (Arduino Code)

The purpose of this code is to identify and display the IR codes received from an IR remote control. This is crucial for understanding the commands that the robot will respond to. The IR Code Finder provides a simple interface to recognize IR signals and their corresponding codes.

### 2. Servo Configuration (Arduino Code)

This code facilitates the calibration and configuration of the servos used in the Quadruped Spider Robot. It allows you to individually set the positions of the servos, ensuring precise control over each leg's movement. The code helps in finding the high, low, and center states for optimal robot performance.

### 3. Quadruped Spider Robot (Arduino Code)

The main project code orchestrates the movements and actions of the Quadruped Spider Robot. It utilizes the IR codes identified in the first component and configures the servos based on the second component. The robot can perform various actions, including walking forward, backward, turning, leaning in different directions, and more.

## How to Use

1. Upload the respective Arduino code for each component to your Arduino board.
2. Connect the necessary components, including the IR receiver and servos, according to the specified pin configurations in the code.
3. Power up the robot and use the IR remote control to send commands.

## Important Functions

### `handleIRCommand(unsigned long value)`

This function interprets the IR commands received by the robot. It maps each IR code to specific actions, allowing the Quadruped Spider Robot to perform various maneuvers. The following are some key functions called within `handleIRCommand`:

- `walkForward(int _delay)`, `walkForward_Alternate(int _delay)`: Initiates forward walking motions with optional delays.

- `walkBackward(int _delay)`, `walkBackward_Alternate(int _delay)`: Initiates backward walking motions with optional delays.

- `turnLeft()`, `turnRight()`: Causes the robot to turn left or right.

- `leanForward(int _delay)`: Commands the robot to lean forward with an optional delay.

- `leanBackward(int _delay)`: Commands the robot to lean backward with an optional delay.

- `leanLeft(int _delay)`: Commands the robot to lean to the left with an optional delay.

- `leanRight(int _delay)`: Commands the robot to lean to the right with an optional delay.

- `Elevate()`, `Centralize()`, `DeElevate()`: Functions to control the elevation of specific legs.

- And more...

Feel free to explore the code to discover additional functionalities and customize them as needed.



## Lecture Presentation (in Turkish)

[Quadruped-Spider-Arduino-Projesi.pdf](https://github.com/MrAliBulut/Arduino_Quadruped_Spider/files/13928860/Quadruped-Spider-Arduino-Projesi.pdf)


## Special Thanks

Special thanks to Robotistan for the template.
https://robotistan.com/Data/EditorFiles/örümcek_robot_klavuz%204%20Bacaklı.pdf

Special thanks to my Teammates of the project. 
Special Thanks to ChatGPT for assistance in refining the README and the code itself.
