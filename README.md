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
3. Go to **Sketch** -> **Include Library** -> **Add .ZIP Library...**.
4. Select the downloaded `.zip` file.
5. Include the library in your code using `#include <UltrasonicX.h>`.

## API Reference

### Constructor & Initialization

#### `UltrasonicX(int trigPin, int echoPin)`
Initializes the library with the pins connected to the sensor.
* **trigPin:** The digital pin used for the trigger signal.
* **echoPin:** The digital pin used to receive the echo signal.

#### `void begin()`
Configures the `trigPin` as `OUTPUT` and `echoPin` as `INPUT`. This must be called within your `setup()` function.

---

### Distance Measurement

#### `float getDistanceCM()`
Calculates the current distance to an object in centimeters based on a speed of sound of ~0.0343 cm/us.
* **Returns:** Distance as a `float`.

#### `float getDistanceIN()`
Calculates the current distance to an object in inches (1 cm = 0.393701 inches).
* **Returns:** Distance as a `float`.

#### `float getAverageDistance(int samples = 5)`
Takes multiple readings (defaulting to 5) and returns the mathematical mean to filter out electrical or environmental noise.
* **samples:** Number of readings to average.
* **Returns:** Smoothed distance in cm.

---

### Object & Motion Detection

#### `bool isObjectDetected(float threshold)`
Checks if an object is currently closer than the specified threshold.
* **threshold:** The distance limit in cm.
* **Returns:** `true` if an object is detected within range.

#### `bool isCloserThan(float threshold)`
An alias for `isObjectDetected`.

#### `bool isMotionDetected()`
Compares the current distance reading to the previous one. It returns `true` if the distance has changed by more than 2cm since the last time this function was called.
* **Returns:** `true` if movement is detected.

---

### Advanced Metrics

#### `float getSpeedCMperSec()`
Calculates the velocity of an object relative to the sensor based on the change in distance over time.
* **Returns:** Speed in cm/s. A positive value indicates the object is moving away; a negative value indicates it is approaching.

#### `long getRawMicroseconds()`
Sends a 10µs pulse and returns the raw travel time of the sound wave.
* **Returns:** Time in microseconds; returns `0` if no echo is received (out of range).

---

## Basic Usage Example

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
