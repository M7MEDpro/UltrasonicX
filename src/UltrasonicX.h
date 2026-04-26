#ifndef UltrasonicX_h
#define UltrasonicX_h

#include <Arduino.h>

/*
  UltrasonicX
  A non-blocking wrapper class for ultrasonic sensors (like HC-SR04)
  providing distance, motion, and speed measurements in various units.
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
      Triggers the sensor and returns the raw travel time in a non-blocking manner
      using interrupt or millis/micros based timing where possible.
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
      getDistanceMM
      Calculates current distance in Millimeters.
      Returns: Distance in mm.
    */
    float getDistanceMM();

    /*
      getDistanceM
      Calculates current distance in Meters.
      Returns: Distance in m.
    */
    float getDistanceM();

    /*
      getDistanceIN
      Calculates current distance in Inches.
      Returns: Distance in inches.
    */
    float getDistanceIN();

    /*
      getDistanceFT
      Calculates current distance in Feet.
      Returns: Distance in feet.
    */
    float getDistanceFT();

    /*
      getDistanceYD
      Calculates current distance in Yards.
      Returns: Distance in yards.
    */
    float getDistanceYD();

    /*
      isCloserThan
      Checks if an object is closer than a specific range.
      maxDistance - The maximum distance limit in CM.
      Returns: true if an object is closer than maxDistance.
    */
    bool isCloserThan(float maxDistance);

    /*
      isMoreThan
      Checks if an object is farther than a specific range.
      minDistance - The minimum distance limit in CM.
      Returns: true if an object is farther than minDistance.
    */
    bool isMoreThan(float minDistance);

    /*
      isBetween
      Checks if an object is between a specific minimum and maximum range.
      minDistance - The minimum distance limit in CM.
      maxDistance - The maximum distance limit in CM.
      Returns: true if an object is between minDistance and maxDistance.
    */
    bool isBetween(float minDistance, float maxDistance);

    /*
      isValidReading
      Checks if distance reading is valid (greater than 0).
      Returns: true if the sensor is providing a valid reading.
    */
    bool isValidReading();

    /*
      getAverageDistance
      Takes multiple readings and returns the mean to filter noise.
      (Note: Averaging naturally takes time, but uses non-blocking delay principles if possible).
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

    // For non-blocking timing
    unsigned long _lastTriggerTime;
    long _cachedDuration;
    bool _isTriggering;
};

#endif
