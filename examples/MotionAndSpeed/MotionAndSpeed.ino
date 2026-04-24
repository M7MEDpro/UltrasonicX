#include <UltrasonicX.h>

/*
  MotionAndSpeed
  Demonstrates how to measure relative speed and determine if
  an object is approaching, receding, or stationary.
*/

UltrasonicX sonar(9, 10);

void setup() {
    Serial.begin(9600);
    sonar.begin();
    Serial.println("Motion and Speed Example Started...");
}

void loop() {
    if (sonar.isValidReading()) {
        float speed = sonar.getSpeedCMperSec();
        Serial.print("Speed: ");
        Serial.print(speed);
        Serial.println(" cm/s");

        // Use a threshold of 2.0 cm to ignore slight vibrations
        if (sonar.isApproaching(2.0)) {
            Serial.println("Status: Object is approaching!");
        } else if (sonar.isReceding(2.0)) {
            Serial.println("Status: Object is moving away!");
        } else if (sonar.isMotionDetected(2.0)) {
            Serial.println("Status: Motion detected!");
        } else {
            Serial.println("Status: Stationary.");
        }
    } else {
        Serial.println("Invalid reading or out of range.");
    }

    Serial.println("---------------------------------");
    delay(1000);
}
