#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "ArduinoJson.h"
#include "pitches.h"
#include "parser.h"

#define SERVICE_UUID            (BLEUUID((uint16_t)0xFFE0)).toString()
#define CHARACTERISTIC_UUID_RX  (BLEUUID((uint16_t)0xFFE1)).toString()
#define CHARACTERISTIC_UUID_TX  (BLEUUID((uint16_t)0xFFE2)).toString()

const int BTled_Pin = 32;
const int Buzzer_Pin = 25;

BLEServer* pServer = NULL;
BLECharacteristic* pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;

    buzzerTone(NOTE_C5, 150);
    buzzerTone(NOTE_E5, 150);
    buzzerTone(NOTE_G5, 250);

    ServoAttach();

    digitalWrite(BTled_Pin, HIGH);
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    pServer->getAdvertising()->start();

    ServoDetach();

    buzzerTone(NOTE_G5, 150);
    buzzerTone(NOTE_E5, 150);
    buzzerTone(NOTE_C5, 250);

    digitalWrite(BTled_Pin, LOW);
  }
};

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();

    START parser(rxValue);
    Serial.println("\n~~~ EXECUTING ~~~");
    parser.execute();
  }
};

void BluetoothSetup() {
  BLEDevice::init(BLUETOOTHNAME);

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY  |
                    BLECharacteristic::PROPERTY_READ
                  );
                      
  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();

  pinMode(BTled_Pin, OUTPUT);
}
