# Cryptocurrency Ticker with OLED Display

This Arduino project utilizes an ESP8266 microcontroller and an OLED display to create a cryptocurrency ticker. Specifically, it fetches the current Bitcoin (BTC) price from the CoinGecko API, displays it on the OLED screen, and adds a touch of fun with animated faces. The ESP8266 connects to Wi-Fi and updates the display periodically.

## Getting Started

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) installed
- [ESP8266 board support](https://arduino-esp8266.readthedocs.io/en/latest/installing.html) in Arduino IDE
- Necessary libraries installed: `Wire`, `Adafruit_SH110X`, `ESP8266WiFi`, `ESP8266HTTPClient`, `WiFiClientSecure`, `ArduinoJson`

### Wiring

Connect the OLED display to the ESP8266 as per the specifications of your hardware. Ensure the I2C address, display dimensions, and OLED reset pin are correctly configured in the code.

### Installation

1. Open the Arduino IDE.
2. Copy and paste the provided code into a new Arduino sketch.
3. Install the required libraries through the Arduino Library Manager.
4. Select the appropriate ESP8266 board from the Tools menu.
5. Upload the sketch to your ESP8266.

## Usage

1. Power on the ESP8266 and observe the OLED display.
2. The animated faces will cycle through, providing a touch of entertainment.
3. The Wi-Fi connection status, signal strength, and Bitcoin price will be periodically updated on the OLED display.

## Configuration

- Adjust the Wi-Fi credentials (`ssid` and `password`) in the code to match your network.
- Modify the `apiUrl` variable if you want to fetch cryptocurrency prices from a different API.

## Contributing

If you'd like to contribute to this project, feel free to fork the repository, make changes, and submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE.md).

## Acknowledgments

- This code utilizes the Adafruit_SH110X and ArduinoJson libraries.
- Special thanks to the open-source community for their contributions to the Arduino ecosystem.
