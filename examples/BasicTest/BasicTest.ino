#include <UltrasonicX.h>

// Initialize sensor on Trigger Pin 9 and Echo Pin 10
UltrasonicX sonar(9, 10);

void setup() {
    Serial.begin(9600);
    sonar.begin();
}

void loop() {
    Serial.print("Distance: ");
    Serial.print(sonar.getDistanceCM());
    Serial.println(" cm");

    delay(500);
}
