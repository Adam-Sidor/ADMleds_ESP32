# ADM LEDs – ESP32

A WS2812B LED controller based on ESP32, using HTTP requests to control the device.

---

## Table of Contents

1. [Project Description](#project-description)
2. [Requirements](#requirements)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Features](#features)
6. [License](#license)
7. [Contact](#contact)

---

## Project Description

* This project allows controlling a WS2812B LED strip using HTTP requests, with the ESP32 module acting as the main controller.
* The ESP32 handles Wi-Fi communication, enabling remote light control via a web browser or a dedicated mobile application.
* The project includes ESP32 code written in Arduino IDE, which interprets HTTP requests and controls the LED strip accordingly.
* The project can be used as part of a smart home system, decorative lighting setup, or for educational purposes related to networking protocols and ARGB LED control.

---

## Requirements

* **Hardware:**

  * ESP32
  * WS2812B LED strip
  * Wi-Fi connection
  * 5V power supply

* **Software:**

  * Arduino IDE (only required during installation)
  * Web browser

* **Optional:**

  * [iOS application](https://github.com/Adam-Sidor/ADMleds_IOS)
  * [PC script](https://github.com/Adam-Sidor/ADMleds_PC)

---

## Installation

Step-by-step instructions on how to set up and run the project:

1. Clone the repository:

   ```bash
   git clone https://github.com/Adam-Sidor/ADMleds_ESP32
   ```

2. Upload the code to the ESP32:

   * Open the `.ino` file in Arduino IDE.
   * Install the required libraries.
   * Set the appropriate values in the code:

     * number of LEDs
     * control pin number
     * your Wi-Fi SSID
     * your Wi-Fi password
   * Select the correct COM port and ESP32 board model.
   * Upload the code to the board.
   * Open the Serial Monitor and check the assigned IP address.
     **Note:** The IP address may change if step 3 is skipped.

3. Set a static IP address (optional).

4. Connect the components:

   * Connect the ground (GND) of all components together.
   * Connect `+5V` power to both the ESP32 and the LED strip.
   * Connect the LED strip data pin to the GPIO pin selected in step 2.

---

## Usage

1. **Web Browser**

   * Open your browser and navigate to the IP address obtained in step 2 of the installation.
   * Control the LEDs using the buttons available on the webpage.
   * Advanced users can manually modify URL endpoints, e.g. `IPaddress/status=1` turns the LEDs on.

2. **Mobile Application**

   * A dedicated [iOS application](https://github.com/Adam-Sidor/ADMleds_IOS) is available for convenient control.
     

3. **PC Script**

   * To automatically turn the LEDs on when the computer starts, use the prepared [PC script](https://github.com/Adam-Sidor/ADMleds_PC).

---

## Features

* Built-in HTTP server for LED control.
* Dedicated iOS application allowing control of multiple devices simultaneously.
* Dedicated PC script for automatic LED activation.
* LED on/off control.
* Brightness adjustment.
* Multiple lighting effects:

  * ARGB rainbow
  * RGB rainbow
  * Static color
  * Storm effect
  * Two-color gradient
* Night mode:

  * Reduced brightness
  * Custom night mode brightness level
* Warning indicator

---

## License

All rights reserved. This project is provided for demonstration and educational purposes only.

* You may use this project for personal and educational purposes.
* Commercial use or redistribution of this project, in whole or in part, requires explicit written permission from the author.

---

## Contact

* Author: Adam Sidor
* Email: [sidoadsi1@gmail.com](mailto:sidoadsi1@gmail.com)
