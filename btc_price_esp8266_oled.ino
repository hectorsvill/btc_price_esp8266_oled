/*
 * Cryptocurrency Ticker with OLED Display
 * This Arduino code retrieves Bitcoin (BTC) price from the CoinGecko API,
 * displays it on an OLED screen, and cycles through animated faces.
 * The ESP8266 connects to Wi-Fi and updates the display periodically.
 * Author: [hectorsvill]
 */

#include <Wire.h>
#include <Adafruit_SH110X.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// I2C address of the OLED display
#define i2c_Address 0x3c

// OLED display dimensions
#define SCREEN_WIDTH 128  // in pixels
#define SCREEN_HEIGHT 64  // in pixels

// OLED reset pin
#define OLED_RESET -1     //

// Adafruit SH1106G OLED display instance
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Wi-Fi credentials
const char* ssid = "RS21-Guest";
const char* password = "guestb117688";

// CoinGecko API URL
const char* apiUrl = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd";

// Wi-Fi Signal Strength Icon
const unsigned char wifi_icon[] PROGMEM = {
  0x00, 0xff, 0x00, 0x7e, 0x00, 0x18, 0x00, 0x00
};

// Animated Faces
#define FACECOUNT 8
char *faces[] = {
  "[ o__o ]",    // Surprise or Amazement.
  "[=__=  ]",    // Boredom or Indifference.
  "[ o__0 ]",    // Confusion
  "[ -_-  ]",    // Disapproval or Annoyance
  "[+__+  ]",    // Excitement or Enthusiasm.
  "[   *_*]",    // Playful
  "[ #__# ]",    // Worried or Anxious.
  "[   ^_^]",    // Happiness or Contentment.
};

// Function Prototypes
void setup();
void loop();
void oled_1_3_display(int cursorx, int cursory, String str);
void connectWiFi();
String requests(String url);
String getBTC(String jsonStr);
String animated_face();

/**
 * @brief Setup function called once at the beginning of the program.
 * It initializes the serial communication, OLED display, and connects to Wi-Fi.
 */
void setup() {
  Serial.begin(115200);
  delay(250);
  display.begin(i2c_Address, true);
  connectWiFi();
  display.clearDisplay();
}

/**
 * @brief Main loop function that runs continuously.
 * It updates the animated face, fetches Bitcoin price, and displays information on the OLED.
 */
void loop() {
  String serialDisplay = "";
  serialDisplay += animated_face();
  String ipConfig = "       ";

  if (WiFi.status() == WL_CONNECTED) {
    String btcJson = requests(apiUrl) + "\n";
    ipConfig += "\n\nBTC: $" + getBTC(btcJson) + "\n";
    oled_1_3_display(SCREEN_WIDTH - 40, 0, String(WiFi.RSSI()));
    display.drawBitmap(SCREEN_WIDTH - 15, 0, wifi_icon, 8, 8, SH110X_WHITE);
    oled_1_3_display(0, 0, ipConfig);
  } else {
    // Wi-Fi error
    WiFi.printDiag(Serial);
  }
}

/**
 * @brief Displays a text on the OLED display at the specified cursor position.
 * @param cursorx The x-coordinate of the cursor position.
 * @param cursory The y-coordinate of the cursor position.
 * @param str The text to be displayed.
 */
void oled_1_3_display(int cursorx, int cursory, String str) {
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(cursorx, cursory);
  display.print(str);
  display.display();
}

/**
 * @brief Connects the ESP8266 to Wi-Fi using the specified credentials.
 * It displays connection status on both the serial monitor and OLED display.
 */
void connectWiFi() {
  // WiFi.mode(WIFI_STA);
  WiFi.begin("RS21-Guest", "guestb117688");
  Serial.print("Connecting");
  oled_1_3_display(0, 0, "Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  display.println();
  Serial.print("Connected, IP address: ");
  oled_1_3_display(0, 0, "Connected");
  Serial.println(WiFi.localIP());
}

/**
 * @brief Makes an HTTP GET request to the specified URL and returns the response as a string.
 * @param url The URL to make the GET request to.
 * @return The response from the HTTP GET request.
 */
String requests(String url) {
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient https;
  String jsonStr;

  if (https.begin(client, url)) {
    int httpCode = https.GET();
    Serial.println("============== Response code: " + String(httpCode) + "===============================");

    if (httpCode > 0) {
      jsonStr = https.getString();
    }
    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }

  return jsonStr;
}

/**
 * @brief Parses the JSON string and extracts the Bitcoin price in USD.
 * @param jsonStr The JSON string containing the Bitcoin price information.
 * @return The Bitcoin price in USD as a string.
 */
String getBTC(String jsonStr) {
  StaticJsonDocument<64> doc;
  DeserializationError error = deserializeJson(doc, jsonStr);

  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
    return "";
  }

  int bitcoinUSD = doc["bitcoin"]["usd"];
  Serial.print("Bitcoin price in USD: ");
  Serial.println(bitcoinUSD);

  return String(bitcoinUSD);
}

/**
 * @brief Displays a randomly selected animated face on the OLED display for a random duration.
 * @return The animated face that was displayed.
 */
String animated_face() {
  int ran = random(3000, 6000);
  int fi = random(1, FACECOUNT);

  oled_1_3_display(0, 0, faces[fi]);
  delay(ran);
  display.clearDisplay();

  return faces[fi];
}
