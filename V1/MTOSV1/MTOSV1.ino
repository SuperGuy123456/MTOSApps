#include <WiFi.h>

//Function to connect to wifi
bool ConnectToWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    Serial.printf("🔌 Connecting to Wi-Fi: %s\n", ssid);

    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
        delay(500);
        Serial.print(".");
        retries++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("\n✅ Connected! IP: %s\n", WiFi.localIP().toString().c_str());
        return true;
    } else {
        Serial.println("\n❌ Failed to connect to Wi-Fi.");
        return false;
    }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
