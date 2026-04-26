# UltrasonicX Arduino Library

An advanced, non-blocking ultrasonic sensor library for HC-SR04 and similar modules. 

## Features
- **Non-Blocking Architecture:** Uses reduced timeouts and caching to prevent your Arduino's `loop()` from hanging.
- **Multiple Units:** Get highly accurate readings in Centimeters (cm), Millimeters (mm), Meters (m), Inches (in), Feet (ft), and Yards (yd).
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

### Initialization

| Method | Description |
| :--- | :--- |
| `UltrasonicX(int trigPin, int echoPin)` | Initializes the library with the trigger and echo pins connected to the sensor. |
| `void begin()` | Configures the pins. Must be called within your `setup()` function. |

### Distance Measurement

| Method | Return Type | Description |
| :--- | :--- | :--- |
| `getDistanceCM()` | `float` | Calculates the distance to an object in centimeters. |
| `getDistanceMM()` | `float` | Calculates the distance to an object in millimeters. |
| `getDistanceM()` | `float` | Calculates the distance to an object in meters. |
| `getDistanceIN()` | `float` | Calculates the distance to an object in inches. |
| `getDistanceFT()` | `float` | Calculates the distance to an object in feet. |
| `getDistanceYD()` | `float` | Calculates the distance to an object in yards. |
| `getAverageDistance(int samples = 5)` | `float` | Takes multiple readings and returns the smoothed mathematical mean (in cm). |
| `getRawMicroseconds()` | `long` | Sends a pulse and returns the raw travel time of the sound wave. Returns `0` on timeout. |
| `isValidReading()` | `bool` | Checks if the sensor is providing a valid reading (greater than 0 distance). |

### Object & Motion Detection

| Method | Return Type | Description |
| :--- | :--- | :--- |
| `isCloserThan(float maxDistance)` | `bool` | Checks if an object is currently closer than the specified maximum distance (cm). |
| `isMoreThan(float minDistance)` | `bool` | Checks if an object is currently farther than the specified minimum distance (cm). |
| `isBetween(float minDistance, float maxDistance)` | `bool` | Checks if an object is between a specified minimum and maximum distance (cm). |
| `isMotionDetected(float threshold = 2.0)` | `bool` | Returns `true` if the distance has changed by more than the threshold since the last check. |
| `isApproaching(float threshold = 2.0)` | `bool` | Returns `true` if the object moved closer by more than the threshold. |
| `isReceding(float threshold = 2.0)` | `bool` | Returns `true` if the object moved farther by more than the threshold. |

### Advanced Metrics & Tools

| Method | Return Type | Description |
| :--- | :--- | :--- |
| `getSpeedCMperSec()` | `float` | Calculates the velocity of an object. Positive = moving away, Negative = approaching. |
| `getRadarData(int angle)` | `String` | Formats reading as `"angle,distance."` for Processing applications or serial plotters. |

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
