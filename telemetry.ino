extern volatile int touch1detected;
extern volatile int touch2detected;
extern unsigned long sr04_distance;
extern float yaw;
extern float velocityX;
extern float distanceX;
extern float temperatureValue;
extern float humidityValue;
extern float lightLevel;

void txData() {
  StaticJsonDocument<512> jsonData;
  char output[512];

  jsonData["Touch1"] = touch1detected;
  jsonData["Touch2"] = touch2detected;
  jsonData["Ultrasonic"] = sr04_distance;
  jsonData["Heading"] = (int)yaw;
  jsonData["Speed"] = velocityX;
  jsonData["Distance"] = distanceX;
  jsonData["Temperature"] = temperatureValue;
  jsonData["Humidity"] = humidityValue;
  jsonData["Brightness"] = lightLevel;

  serializeJson(jsonData, output);
  Serial.println((char*)output);
  pTxCharacteristic->setValue((char*)output);
  pTxCharacteristic->notify();
}
