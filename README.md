# UltrasonicX Arduino Library

An advanced and easy-to-use ultrasonic sensor library for HC-SR04 and similar modules.

## Features
- **Distance Measurement:** Get highly accurate readings in Centimeters (cm) and Inches (in).
- **Object Detection:** Easily check if objects are within a specific threshold.
- **Motion Detection:** Automatically detect if an object has moved relative to the sensor.
- **Speed Calculation:** Calculate the velocity of an object (cm/s) as it approaches or moves away.
- **Averaging Filter:** Smooth out noisy data by taking multiple rapid readings and returning the mean.

## Installation
1. Download this repository as a `.zip` file.
2. Open the Arduino IDE.
3. Go to **Sketch** -> **Include Library** -> **Add .ZIP Library...**
4. Select the downloaded `.zip` file.
5. Include the library in your code using `#include <UltrasonicX.h>`.

## Basic Usage

```cpp
#include <UltrasonicX.h>

// Initialize sensor on Trigger Pin 9 and Echo Pin 10
UltrasonicX sonar(9, 10);

void setup() {
    Serial.begin(9600);
    sonar.begin();
}

void loop() {
    // Get distance in cm
    Serial.print("Distance: ");
    Serial.print(sonar.getDistanceCM());
    Serial.println(" cm");

    // Check for motion
    if (sonar.isMotionDetected()) {
        Serial.println("Motion detected!");
    }

    delay(500);
}