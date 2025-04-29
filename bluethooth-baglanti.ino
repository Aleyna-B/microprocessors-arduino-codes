#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Device connected");
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Device disconnected");
  }
};

void setup() {
  Serial.begin(115200);

  // Create BLE Device
  BLEDevice::init("ESP32_BLE_Server");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create BLE Service
  BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x110A));

  // Create BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                     BLEUUID((uint16_t)0x2A56),
                     BLECharacteristic::PROPERTY_READ |
                     BLECharacteristic::PROPERTY_WRITE
                   );

  pCharacteristic->setValue("Hello from ESP32");
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLEUUID((uint16_t)0x110A));
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  BLEDevice::startAdvertising();
  Serial.println("Waiting for a BLE client connection...");
}

void loop() {
  if (deviceConnected) {
    pCharacteristic->setValue("ESP32 says hello!");
    pCharacteristic->notify(); // Notify connected client
    delay(5000);
  }
}