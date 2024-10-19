#define BLUETOOTHNAME "⠀StickEm_Beta2"

#include "Wire.h"
#include <Adafruit_Sensor.h>

const int PwrLED_Pin = 26;

extern volatile bool OLED_ConnectFlag;
extern volatile bool BH1750_ConnectFlag;
extern volatile bool SR04_ConnectFlag;
extern volatile bool AHT10_ConnectFlag;
extern volatile bool MPU6050_ConnectFlag;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);  // Set I2C to 400 kHz
  sensorSetup();
  BluetoothSetup();
  BuzzerSetup();
  TouchSetup();
  
  pinMode(PwrLED_Pin, OUTPUT);
  digitalWrite(PwrLED_Pin, HIGH);
}

void loop() {
  clearOLED();

  if(MPU6050_ConnectFlag==1) {
    if(OLED_ConnectFlag==1) {
      displayMPU6050();
    }
  }
  if(SR04_ConnectFlag==1) {
    getSR04data();
    if(OLED_ConnectFlag==1) {
      displaySR04();
    }
  }
  if(AHT10_ConnectFlag==1) {
    getAHTdata();
    if(OLED_ConnectFlag==1) {
      displayAHT10();
    }
  }
  if(BH1750_ConnectFlag==1) {
    displayBH1750();
  }
  
  displayOLED();
  txData();
  resetTouch();
  delay(10);
}
