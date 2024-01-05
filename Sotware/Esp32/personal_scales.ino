#include <WiFi.h>

const char* ssid = "saeed";
const char* password = "saeed111";

const char* serverAddress = "100.81.113.21";
const int serverPort = 1234;

const int adcPin = 34;
float gewicht;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  // Connect to the server
  while (client.connect(serverAddress, serverPort)) {
    Serial.println("Connected to server");

    // Read the value of the ADC pin
    int adcValue = analogRead(adcPin);
    float voltage = adcValue * (3.3 / 4095.0);

    Serial.print("Dein Gewicht: ");
    gewicht = ((0.99789494* pow(voltage,2)) + (45.79758729 * voltage) + 7.62528027);
    Serial.println (gewicht);

    // Send the ADC value to the server
    String message = String(gewicht);
    client.println(message);
    Serial.println("Sent message: " + message);

    delay(1000);

  }
    Serial.println("Connection failed");

    if (WiFi.status() != WL_CONNECTED) {
    ESP.restart();
  }
}
