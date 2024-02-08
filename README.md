# Objectify Seven Segment Displays

## Overview

Are you tired of dealing with the complexity of coding for 7-segment displays using traditional methods? Introducing **Objectify Seven Segment Displays**, a simplified approach to programming and managing 7-segment displays using object-oriented principles.

## Description

This GitHub repository contains a C++ program that demonstrates a class named `Disp`, designed to make interacting with 7-segment displays a breeze. The class utilizes the 74HC595 shift registers to simplify the control of multiple displays.

## Features

- **Object-Oriented Design:** Treat 7-segment displays as objects, making your code more modular and easier to manage.

- **Simplified Programming:** Forget about complicated code for 7-segment displays. With the `Disp` class, you can easily set and get display values without the hassle.

- **Shift Register Integration:** The program uses the 74HC595 shift registers to efficiently control multiple displays, reducing the number of pins required for your Arduino project.

## Getting Started

1. **Clone the Repository:**
   ```
   git clone https://github.com/SebastianCikes/Objectify-7-degment-displays-in-Arduino.git
   ```
2. **Open in Arduino IDE:**
    Open the main Arduino file (objectifySevenSegmentDisplays.ino) in the Arduino IDE.

3. **Upload to Arduino:**
    Upload the code to your Arduino board, and witness the simplicity of managing 7-segment displays.

4. **Build the electronic circuit:**
    Follow the scheme and connect the circuit to the Arduino.

## Usage

1. **Initialize Displays:**
    Create instances of the `Disp` class to represent your 7-segment displays. Customize the display positions and default values.
    ```
    const int numDisplays = 2;
    Disp displays[numDisplays] = {
        Disp(1),
        Disp(2)
    };
    ```
2. **Set Display Values:**
    Change the display values easily without complex code.
    ```
    bool test[8] = {0, 0, 1, 1, 0, 0, 1, 1};
    displays[0].setValue(test);
    Disp::updateDisplays(displays, numDisplays);
    ```
    The index of the `displays` array starts from the value 0 up to the number `numDisplays - 1`. The smallest index equals the smallest positioned display, while the `numDisplays - 1` index equals the largest positioned display.

## Contributing
Feel free to contribute to make this project even better! Fork the repository, make your changes, and submit a pull request.

## License
This project is licensed under the GNU License - see the `LICENSE` file for details.
