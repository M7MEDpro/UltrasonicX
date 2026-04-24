#include <UltrasonicX.h>
#include <Servo.h>

/*
  ServoRadar
  Demonstrates how to use the getRadarData() function in combination
  with a Servo motor to create a scanning radar. The data format
  outputted to the Serial monitor is ideal for processing apps
  that draw a visual radar screen.
*/

UltrasonicX sonar(9, 10);
Servo radarServo;

void setup() {
    Serial.begin(9600);
    sonar.begin();

    radarServo.attach(11);
}

void loop() {
    // Sweep from 15 to 165 degrees
    for (int angle = 15; angle <= 165; angle++) {
        radarServo.write(angle);
        delay(30); // Wait for servo to reach position

        // Prints "angle,distance."
        Serial.println(sonar.getRadarData(angle));
    }

    // Sweep back from 165 to 15 degrees
    for (int angle = 165; angle >= 15; angle--) {
        radarServo.write(angle);
        delay(30);

        Serial.println(sonar.getRadarData(angle));
    }
}
