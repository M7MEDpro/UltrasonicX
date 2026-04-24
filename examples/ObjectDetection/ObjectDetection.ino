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
    if (sonar.isObjectDetected(THRESHOLD)) {
        Serial.println("ALERT: Object detected within 15 cm!");
    }

    // Check for extremely close objects
    if (sonar.isCloserThan(5.0)) {
        Serial.println("WARNING: Object is dangerously close (under 5 cm)!");
    }

    // Check if path is clear
    if (sonar.isFartherThan(50.0)) {
        Serial.println("All clear: No objects within 50 cm.");
    }

    Serial.println("--------------------");
    delay(500);
}
