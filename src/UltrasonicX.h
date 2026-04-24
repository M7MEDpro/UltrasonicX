#ifndef UltrasonicX_h
#define UltrasonicX_h

#include <Arduino.h>

/*
  UltrasonicX
  A wrapper class for ultrasonic sensors (like HC-SR04) providing
  distance, motion, and speed measurements.
*/
class UltrasonicX {
public:
    /*
      UltrasonicX
      Construct a new UltrasonicX object.

      trigPin - The GPIO pin connected to the sensor's Trigger pin.
      echoPin - The GPIO pin connected to the sensor's Echo pin.
    */
    UltrasonicX(int trigPin, int echoPin);

    /*
      begin
      Initializes the pin modes. Should be called in Arduino's setup().
    */
    void begin();

    /*
      getRawMicroseconds
      Triggers the sensor and returns the raw travel time.

      Returns: Time in microseconds (0 if out of range/timeout).
    */
    long getRawMicroseconds();

    /*
      getDistanceCM
      Calculates current distance in Centimeters.

      Returns: Distance in cm.
    */
    float getDistanceCM();

    /*
      getDistanceIN
      Calculates current distance in Inches.

      Returns: Distance in inches.
    */
    float getDistanceIN();

    /*
      isObjectDetected
      Checks if an object is within a specific range.

      threshold - The distance limit to check against.
      Returns: true if an object is closer than the threshold.
    */
    bool isObjectDetected(float threshold);

    /*
      isCloserThan
      Alias for isObjectDetected.

      threshold - The distance limit.
      Returns: true if an object is closer than the threshold.
    */
    bool isCloserThan(float threshold);

    /*
      isFartherThan
      Checks if an object is farther than a specific range.

      threshold - The distance limit to check against.
      Returns: true if an object is farther than the threshold.
    */
    bool isFartherThan(float threshold);

    /*
      isValidReading
      Checks if distance reading is valid (greater than 0).

      Returns: true if the sensor is providing a valid reading.
    */
    bool isValidReading();

    /*
      getAverageDistance
      Takes multiple readings and returns the mean to filter noise.

      samples - Number of readings to take (default: 5).
      Returns: The smoothed distance in cm.
    */
    float getAverageDistance(int samples = 5);

    /*
      isMotionDetected
      Compares current reading to the previous one to detect movement.

      threshold - Sensitivity threshold in cm (default: 2.0).
      Returns: true if distance changed by more than threshold since last call.
    */
    bool isMotionDetected(float threshold = 2.0);

    /*
      isApproaching
      Checks if an object has approached the sensor.

      threshold - Sensitivity threshold in cm (default: 2.0).
      Returns: true if the object moved closer by more than threshold since the last reading.
    */
    bool isApproaching(float threshold = 2.0);

    /*
      isReceding
      Checks if an object has moved away from the sensor.

      threshold - Sensitivity threshold in cm (default: 2.0).
      Returns: true if the object moved farther by more than threshold since the last reading.
    */
    bool isReceding(float threshold = 2.0);

    /*
      getSpeedCMperSec
      Calculates the velocity of an object relative to the sensor.

      Returns: Speed in cm/s. Positive = moving away, Negative = approaching.
    */
    float getSpeedCMperSec();

    /*
      getRadarData
      Helper function for building a radar screen.
      Formats the reading for applications like Processing.

      angle - The current angle of the servo motor.
      Returns: Formatted as "angle,distance."
    */
    String getRadarData(int angle);

private:
    int _trigPin;
    int _echoPin;
    float _lastDistance;
    unsigned long _lastTime;
};

#endif
