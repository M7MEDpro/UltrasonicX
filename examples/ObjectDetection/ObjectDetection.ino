#include <UltrasonicX.h>

UltrasonicX sonar(9, 10);

// A standard threshold for detecting objects (in cm)
const float THRESHOLD = 15.0;

void setup() {
    Serial.begin(9600);
    sonar.begin();
}

void loop() {
    float dist = sonar.getDistanceCM();
    Serial.print("Current Distance: ");
    Serial.print(dist);
    Serial.println(" cm");

    // Check if an object has entered our threshold zone
    if (sonar.isCloserThan(THRESHOLD)) {
        Serial.println("ALERT: Object detected within 15 cm!");
    }

    // Check for extremely close objects
    if (sonar.isCloserThan(5.0)) {
        Serial.println("WARNING: Object is dangerously close (under 5 cm)!");
    }

    // Check if an object is between 20 and 30 cm
    if (sonar.isBetween(20.0, 30.0)) {
        Serial.println("INFO: Object is between 20cm and 30cm.");
    }

    // Check if path is clear
    if (sonar.isMoreThan(50.0)) {
        Serial.println("All clear: No objects within 50 cm.");
    }

    Serial.println("--------------------");
    delay(500);
}
