#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <BLEHIDDevice.h>

#define BTN_PHOTO 12
#define DEBOUNCE_MS 300

BLEHIDDevice* hid;
BLECharacteristic* inputMediaKeys;
bool connected = false;

const uint8_t KEY_VOLUME_UP[2] = {0xE9, 0x00}; // shutter / volume
const uint8_t KEY_RELEASE[2]   = {0x00, 0x00};

unsigned long lastPress = 0;

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) { connected = true; }
  void onDisconnect(BLEServer* pServer) {
    connected = false;
    BLEDevice::startAdvertising();
  }
};

void sendHidKey(const uint8_t key[2]) {
  if (!connected) return;
  inputMediaKeys->setValue((uint8_t*)key, 2);
  inputMediaKeys->notify();
  delay(80);
  inputMediaKeys->setValue((uint8_t*)KEY_RELEASE, 2);
  inputMediaKeys->notify();
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PHOTO, INPUT_PULLUP);

  BLEDevice::init("Camera Remote");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  hid = new BLEHIDDevice(pServer);
  inputMediaKeys = hid->inputReport(1);

  const uint8_t reportMap[] = {
    0x05, 0x0C,
    0x09, 0x01,
    0xA1, 0x01,
    0x85, 0x01,
    0x15, 0x00,
    0x26, 0x9C, 0x02,
    0x19, 0x00,
    0x2A, 0x9C, 0x02,
    0x95, 0x01,
    0x75, 0x10,
    0x81, 0x00,
    0xC0
  };

  hid->reportMap((uint8_t*)reportMap, sizeof(reportMap));
  hid->startServices();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->setAppearance(0x03C0);
  pAdvertising->addServiceUUID(hid->hidService()->getUUID());
  pAdvertising->start();
}

void loop() {
  unsigned long now = millis();

  if (digitalRead(BTN_PHOTO) == LOW && now - lastPress > DEBOUNCE_MS) {
    lastPress = now;
    sendHidKey(KEY_VOLUME_UP);
  }
}
 // IRENE SKY - OFFICIAL
