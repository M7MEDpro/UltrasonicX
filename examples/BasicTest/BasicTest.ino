#include <UltrasonicX.h>

UltrasonicX sonar(9, 10);

void setup() {
    Serial.begin(9600);
    sonar.begin();
}

void loop() {

    Serial.print("Distance: ");
    Serial.print(sonar.getDistanceCM());
    Serial.println(" cm");

    if(sonar.isMotionDetected()) {
    Serial.println("Motion detected!");
}

    delay(500);
}