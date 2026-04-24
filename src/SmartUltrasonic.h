#ifndef UltrasonicX_h
#define UltrasonicX_h

#include <Arduino.h>

/**
 * @class UltrasonicX
 * @brief A wrapper class for ultrasonic sensors (like HC-SR04) providing
 * distance, motion, and speed measurements.
 */
class UltrasonicX {
public:
    /**
     * @brief Construct a new UltrasonicX object.
     * @param trigPin The GPIO pin connected to the sensor's Trigger pin.
     * @param echoPin The GPIO pin connected to the sensor's Echo pin.
     */
    UltrasonicX(int trigPin, int echoPin);

    /**
     * @brief Initializes the pin modes. Should be called in Arduino's setup().
     */
    void begin();

    /**
     * @brief Triggers the sensor and returns the raw travel time.
     * @return long Time in microseconds (0 if out of range/timeout).
     */
    long getRawMicroseconds();

    /**
     * @brief Calculates current distance in Centimeters.
     * @return float Distance in cm.
     */
    float getDistanceCM();

    /**
     * @brief Calculates current distance in Inches.
     * @return float Distance in inches.
     */
    float getDistanceIN();

    /**
     * @brief Checks if an object is within a specific range.
     * @param threshold The distance limit to check against.
     * @return true if an object is closer than the threshold.
     */
    bool isObjectDetected(float threshold);

    /**
     * @brief Alias for isObjectDetected.
     * @param threshold The distance limit.
     * @return true if an object is closer than the threshold.
     */
    bool isCloserThan(float threshold);

    /**
     * @brief Takes multiple readings and returns the mean to filter noise.
     * @param samples Number of readings to take (default: 5).
     * @return float The smoothed distance in cm.
     */
    float getAverageDistance(int samples = 5);

    /**
     * @brief Compares current reading to the previous one to detect movement.
     * @return true if distance changed by more than 2cm since last call.
     */
    bool isMotionDetected();

    /**
     * @brief Calculates the velocity of an object relative to the sensor.
     * @return float Speed in cm/s. Positive = moving