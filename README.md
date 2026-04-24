# UltrasonicX Arduino Library

An advanced and easy-to-use ultrasonic sensor library for HC-SR04 and similar modules.

## Features
- **Distance Measurement:** Get highly accurate readings in Centimeters (cm) and Inches (in).
- **Object Detection:** Easily check if objects are within a specific threshold, or further away.
- **Motion Detection:** Automatically detect if an object has moved relative to the sensor, or if it is approaching/receding.
- **Speed Calculation:** Calculate the velocity of an object (cm/s) as it approaches or moves away.
- **Averaging Filter:** Smooth out noisy data by taking multiple rapid readings and returning the mean.
- **Radar Support:** Output data formatted for radar screens and Processing interfaces.

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

#### `bool isValidReading()`
Checks if the sensor is providing a valid reading (greater than 0 distance).
* **Returns:** `true` if the reading is valid.

---

### Object & Motion Detection

#### `bool isObjectDetected(float threshold)`
Checks if an object is currently closer than the specified threshold.
* **threshold:** The distance limit in cm.
* **Returns:** `true` if an object is detected within range.

#### `bool isCloserThan(float threshold)`
An alias for `isObjectDetected`.

#### `bool isFartherThan(float threshold)`
Checks if an object is currently farther than the specified threshold.
* **threshold:** The distance limit in cm.
* **Returns:** `true` if an object is farther than the specified limit.

#### `bool isMotionDetected(float threshold = 2.0)`
Compares the current distance reading to the previous one. It returns `true` if the distance has changed by more than the threshold since the last time this function was called.
* **threshold:** Sensitivity in cm. Default is 2.0cm.
* **Returns:** `true` if movement is detected.

#### `bool isApproaching(float threshold = 2.0)`
Compares the current distance reading to the previous one. It returns `true` if the object moved closer by more than the threshold since the last time this function was called.
* **threshold:** Sensitivity in cm. Default is 2.0cm.
* **Returns:** `true` if the object is approaching.

#### `bool isReceding(float threshold = 2.0)`
Compares the current distance reading to the previous one. It returns `true` if the object moved farther by more than the threshold since the last time this function was called.
* **threshold:** Sensitivity in cm. Default is 2.0cm.
* **Returns:** `true` if the object is receding.

---

### Advanced Metrics & Tools

#### `float getSpeedCMperSec()`
Calculates the velocity of an object relative to the sensor based on the change in distance over time.
* **Returns:** Speed in cm/s. A positive value indicates the object is moving away; a negative value indicates it is approaching.

#### `long getRawMicroseconds()`
Sends a 10µs pulse and returns the raw travel time of the sound wave.
* **Returns:** Time in microseconds; returns `0` if no echo is received (out of range).

#### `String getRadarData(int angle)`
Formats the reading for applications like Processing to build a radar screen.
* **angle:** The current angle of the servo motor holding the sensor.
* **Returns:** A `String` formatted as `"angle,distance."`

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

    // Check for motion (5cm threshold)
    if (sonar.isMotionDetected(5.0)) {
        Serial.println("Motion detected!");
    }

    // Check if reading is valid
    if (sonar.isValidReading()) {
        if (sonar.isApproaching(2.0)) {
            Serial.println("Object is approaching!");
        } else if (sonar.isReceding(2.0)) {
            Serial.println("Object is moving away!");
        }
    } else {
        Serial.println("Reading invalid or out of range.");
    }

    delay(500);
}
```

## Radar Application Example

```cpp
#include <UltrasonicX.h>
#include <Servo.h> 

UltrasonicX sonar(9, 10);
Servo myServo;

void setup() {
    Serial.begin(9600);
    sonar.begin();
    myServo.attach(11); // Attach servo to pin 11
}

void loop() {
    // Sweep servo from 15 to 165 degrees
    for(int i = 15; i <= 165; i++) {
        myServo.write(i);
        delay(30);
        // Print data formatted for Processing radar sketch
        Serial.print(sonar.getRadarData(i)); 
    }
    
    // Sweep servo back from 165 to 15 degrees
    for(int i = 165; i >= 15; i--) {
        myServo.write(i);
        delay(30);
        Serial.print(sonar.getRadarData(i));
    }
}
```
