
# Prototyping-Self-Driving-Car
## Overview
This GitHub repository contains the source code and documentation for a self-driving car prototype built on a big ride-on electric car. The project utilizes a Servo motor with gears to control the steering mechanism, and the car is powered and controlled using an Arduino Uno. The car can be operated manually or automatically, with a switch to transition between modes. The automatic mode allows the car to maintain its straight-forward motion by correcting deviations using the steering with the help of a simple PD controller.

![image](https://github.com/shryam102/Prototyping-Self-Driving-Car/assets/78613519/5bc98567-3286-4de8-bf6f-06edbda50caf)

## Features
* **Manual and Automatic Modes**: The car can be controlled manually or switched to automatic mode.
* **Straight Movement with PID**: In automatic mode, the car moves in a straight line, correcting deviations using a simple PID (Proportional-Integral-Derivative) controller.
* **Future Goals**: The project aims to achieve full autonomy, enabling the car to navigate to specified GPS locations autonomously.

## Components Used
* Arduino Uno
* Toy car (Any car/ robot with wheels)
* Servo (S8218)
* IMU Sensor (MPU6050)
* Motor Driver (TA6586)
* RF Module (nRF24L01)

## Circuit 
<img src="https://github.com/shryam102/Prototyping-Self-Driving-Car/assets/78613519/966a2d22-f986-4b70-a8bc-2e14429fa78b.png" width="400" height="300"> "\t" <img src="https://github.com/shryam102/Prototyping-Self-Driving-Car/assets/78613519/ed2b2f2a-796b-4f25-aa02-63033eeb80e7.png" width = "400" height = "300">



