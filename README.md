# esp32-camera-volume-remote
A Bluetooth camera / volume remote built with ESP32
ESP32 BLE Camera Remote

A single-button Bluetooth remote built on an ESP32, using BLE HID to control a phone's camera shutter AND volume — no app or pairing code needed, just standard Bluetooth keyboard/media-key behavior.

How it works

The ESP32 advertises itself as a Bluetooth HID media device (like a Bluetooth headset's remote control). When the button is pressed, it sends the standard Volume Up consumer key over BLE.

This one key does double duty depending on what's on your phone's screen:

Camera shutter, when the Camera app is open and in focus
Regular volume control, on any other screen (music, videos, calls, etc.)
Hardware
ESP32 dev board (WROOM or similar)
1x push button
Jumper wires / breadboard
Wiring
Button leg 1 → GPIO12
Button leg 2 → GND

Uses the internal pull-up resistor (INPUT_PULLUP), so no external resistor is needed.

Setup
Install the ESP32 board package in Arduino IDE (Boards Manager → search "esp32").
Wire the button as described above.
Open CameraRemote.ino, select your board and port, and upload.
On your phone: Bluetooth settings → pair with "Camera Remote".
Open your phone's Camera app, press the button to take a photo — or press it anywhere else on the phone to raise the volume.
Known limitations
Camera shutter only works while the Camera app is in the foreground — on any other screen, the button just raises the volume instead.
Not all camera apps bind volume keys to the shutter (rare, but possible on some heavily customized phone skins) — test on your device first.
