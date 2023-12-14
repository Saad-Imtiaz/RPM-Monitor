# RPM_Monitor 🚀

## Overview 🌐
RPM_Monitor is a specialized Arduino project designed to accurately measure and monitor the rotational speed (RPM) and angular velocity of a DC motor with a built-in encoder. This tool is ideal for applications in robotics, mechanical engineering, and DIY projects involving motor speed regulation.

## Features 🌟
- Measures RPM (Revolutions Per Minute) of a DC motor.
- Calculates angular velocity in both radians per second and degrees per second.
- Supports direction detection (forward and reverse).
- Utilizes Arduino interrupts for precise pulse counting.

## Hardware Requirements 🔧
- Arduino Board (Uno, Mega, etc.)
- DC Motor with Built-in Encoder
- Connecting Wires

## Setup and Installation 🛠️
1. **Connect the Encoder:**
   - Connect the encoder outputs to the specified Arduino interrupt and digital pins.
2. **Arduino Configuration:**
   - Ensure your Arduino IDE is set up and the board is connected.
3. **Code Deployment:**
   - Upload the provided sketch to your Arduino board.

## Usage 🔄
Once set up, the RPM_Monitor will:
- Continuously measure the number of pulses from the motor encoder.
- Calculate and display the RPM and angular velocity every second.
- Indicate the motor's direction of rotation.

## Code Explanation 📖
- `ENC_COUNT_REV`: Number of encoder pulses per 360-degree revolution.
- `ENC_IN_RIGHT_A` and `ENC_IN_RIGHT_B`: Encoder input pins.
- `right_wheel_pulse()`: Interrupt service routine for counting pulses.
- Main loop calculates and prints RPM and angular velocity.
