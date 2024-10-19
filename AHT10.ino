#include <Adafruit_AHT10.h>

// Create an instance of the AHT10 sensor
Adafruit_AHT10 aht10;

//Variables
sensors_event_t humidity, temperature; // For storing sensor readings
float temperatureValue; // To store temperature
float humidityValue; // To store humidity

void AHT10Setup() {
  aht10.begin();
}

void getAHTdata() {
  // Read temperature and humidity
  aht10.getEvent(&humidity, &temperature);

  // Store readings in global variables
  temperatureValue = temperature.temperature;
  humidityValue = humidity.relative_humidity;
}
