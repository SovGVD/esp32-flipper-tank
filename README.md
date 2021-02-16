# ESP32 powered double swing arm crawler robot tank
Robot inspired by iRobot PackBot.

## Harware
 - ESP32
 - 2 x DC motors with encoder (TODO: use encoder)
 - 2 x ToF
 - 2 x 270 deg high voltage (HV) Servos
 - INA3221
 - 3 x DC converter to 5v (esp32), 8v (HV servo) and 12v (motors)
 - 2 x MX1508

## Software
Copy/rename `config_wifi.example.h` to `config_wifi.h` and set WiFi access point SSID and password.

### Arduino library
 - https://github.com/me-no-dev/AsyncTCP and https://github.com/me-no-dev/ESPAsyncWebServer
 - ESP32Servo

## Web interface
 - node.js required to build web interface
   - `npm run-script build` to build web interface
