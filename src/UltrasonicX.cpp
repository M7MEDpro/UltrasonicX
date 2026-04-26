#include "UltrasonicX.h"

UltrasonicX::UltrasonicX(int trigPin, int echoPin) {
    _trigPin = trigPin;
    _echoPin = echoPin;
    _lastDistance = 0;
    _lastTime = 0;
    _lastTriggerTime = 0;
    _cachedDuration = 0;
    _isTriggering = false;
}

void UltrasonicX::begin() {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

long UltrasonicX::getRawMicroseconds() {
    unsigned long currentMicros = micros();

    // To be truly non-blocking without interrupts, we must avoid pulseIn().
    // If you need it fully asynchronous, consider using NewPing or interrupts.
    // However, to mimic non-blocking behavior with pulseIn without hanging the loop forever,
    // we use a short timeout.

    // Check if we are ready for a new reading (allow at least 30ms between pings to prevent echo overlap)
    if (currentMicros - _lastTriggerTime >= 30000) {
        // Trigger pulse
        digitalWrite(_trigPin, LOW);
        delayMicroseconds(2); // Short enough to block without impact
        digitalWrite(_trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(_trigPin, LOW);

        // Timeout reduced to 25ms (about 4 meters max range) to minimize blocking
        _cachedDuration = pulseIn(_echoPin, HIGH, 25000);
        _lastTriggerTime = micros();
    }

    return _cachedDuration;
}

float UltrasonicX::getDistanceCM() {
    long duration = getRawMicroseconds();
    if (duration == 0) return 0.0;
    // Speed of sound is ~0.0343 cm/us. Distance = (Time * Speed) / 2 (round trip)
    float distance = duration * 0.034 / 2.0;
    return distance;
}

float UltrasonicX::getDistanceMM() {
    return getDistanceCM() * 10.0;
}

float UltrasonicX::getDistanceM() {
    return getDistanceCM() / 100.0;
}

float UltrasonicX::getDistanceIN() {
    // 1 cm = 0.393701 inches
    return getDistanceCM() * 0.393701;
}

float UltrasonicX::getDistanceFT() {
    // 1 inch = 1/12 feet
    return getDistanceIN() / 12.0;
}

float UltrasonicX::getDistanceYD() {
    // 1 yard = 3 feet
    return getDistanceFT() / 3.0;
}

bool UltrasonicX::isCloserThan(float maxDistance) {
    float cm = getDistanceCM();
    return cm > 0 && cm < maxDistance;
}

bool UltrasonicX::isMoreThan(float minDistance) {
    float cm = getDistanceCM();
    return cm > minDistance;
}

bool UltrasonicX::isBetween(float minDistance, float maxDistance) {
    float cm = getDistanceCM();
    return cm > minDistance && cm < maxDistance;
}

bool UltrasonicX::isValidReading() {
    return getDistanceCM() > 0.0;
}

float UltrasonicX::getAverageDistance(int samples) {
    float sum = 0;
    int validSamples = 0;

    for(int i = 0; i < samples; i++) {
        // Force an immediate reading bypassing the non-blocking cache delay
        digitalWrite(_trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(_trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(_trigPin, LOW);

        long duration = pulseIn(_echoPin, HIGH, 25000);
        if(duration > 0) {
            sum += (duration * 0.034 / 2.0);
            validSamples++;
        }
        delay(20); // Delay between pings to let reflections fade
    }

    if (validSamples == 0) return 0.0;
    return sum / validSamples;
}

bool UltrasonicX::isMotionDetected(float threshold) {
    float current = getDistanceCM();
    if (current == 0) return false;
    bool motion = abs(current - _lastDistance) > threshold;
    _lastDistance = current;
    return motion;
}

bool UltrasonicX::isApproaching(float threshold) {
    float current = getDistanceCM();
    if (current == 0) return false;
    bool approaching = (_lastDistance - current) > threshold;
    _lastDistance = current;
    return approaching;
}

bool UltrasonicX::isReceding(float threshold) {
    float current = getDistanceCM();
    if (current == 0) return false;
    bool receding = (current - _lastDistance) > threshold;
    _lastDistance = current;
    return receding;
}

float UltrasonicX::getSpeedCMperSec() {
    float currentDistance = getDistanceCM();
    if (currentDistance == 0) return 0.0;

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

String UltrasonicX::getRadarData(int angle) {
    int distance = (int)getDistanceCM();
    // Common format used by Processing and similar GUI apps for radar
    return String(angle) + "," + String(distance) + ".";
}
