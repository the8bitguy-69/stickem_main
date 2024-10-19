#include <BH1750.h>

BH1750 lightSensor; // Create an instance of the BH1750 sensor
float lightLevel; // Variable to store the light level

void BH1750Setup() {
  lightSensor.begin();
}

void getBH1750Data() {
  // Read the light level in lux
  lightLevel = lightSensor.readLightLevel();
}
