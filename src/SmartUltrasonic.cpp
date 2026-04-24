#include "UltrasonicX.h"

UltrasonicX::UltrasonicX(int trigPin, int echoPin) {
    _trigPin = trigPin;
    _echoPin = echoPin;
    _lastDistance = 0;
    _lastTime = 0;
}

void UltrasonicX::begin() {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

long UltrasonicX::getRawMicroseconds() {
    // Ensure trigger is low
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);

    // Send 10 microsecond pulse to trigger ranging
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    // Read echo pulse (30ms timeout is approx 5 meters range)
    long duration = pulseIn(_echoPin, HIGH, 30000);
    return duration;
}

float UltrasonicX::getDistanceCM() {
    long duration = getRawMicroseconds();
    // Speed of sound is ~0.0343 cm/us. Distance = (Time * Speed) / 2 (round trip)
    float distance = duration * 0.034 / 2;
    return distance;
}

float UltrasonicX::getDistanceIN() {
    // 1 cm = 0.393701 inches
    return getDistanceCM() * 0.393701;
}

bool UltrasonicX::isObjectDetected(float distance) {
    return getDistanceCM() < distance;
}

bool UltrasonicX::isCloserThan(float distance) {
    return isObjectDetected(distance);
}

float UltrasonicX::getAverageDistance(int samples) {
    float sum = 0;
    for(int i = 0; i < samples; i++) {
        sum += getDistanceCM();
        delay(20); // Short delay to let reflections fade
    }
    return sum / samples;
}

bool UltrasonicX::isMotionDetected() {
    float current = getDistanceCM();
    // Returns true if change is greater than 2cm sensitivity threshold
    bool motion = abs(current - _lastDistance) > 2.0;
    _lastDistance = current;
    return motion;
}

float UltrasonicX::getSpeedCMperSec() {
    float currentDistance = getDistanceCM();
    unsigned long currentTime = millis();

    // Calculate delta time in seconds
    float deltaTime = (currentTime - _lastTime) / 1000.0;

    // Avoid division by zero if called too rapidly
    float speed = 0;
    if (deltaTime > 0) {
        speed = (currentDistance - _lastDistance) / deltaTime;
    }

    _lastDistance = currentDistance;
    _lastTime = currentTime;

    return speed;
}