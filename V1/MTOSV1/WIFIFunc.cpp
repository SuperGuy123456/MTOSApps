#include "WIFIFunc.h"

WIFIFunc::WIFIFunc(){}

bool WIFIFunc::connectToWiFi(const char* ssid, const char* password) {
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

bool WIFIFunc::downloadBinToSD(const char* url, const char* localPath) {
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode != HTTP_CODE_OK) {
        Serial.printf("❌ HTTP GET failed: %d\n", httpCode);
        http.end();
        if (tft) {
            tft->fillScreen(TFT_BLACK);
            tft->setTextColor(TFT_RED);
            tft->setCursor(90, 150);
            tft->print("Download failed!");
        }
        return false;
    }

    int contentLength = http.getSize();
    WiFiClient* stream = http.getStreamPtr();

    File file = SDCard->open(localPath, FILE_WRITE);
    if (!file) {
        Serial.printf("❌ Failed to open file: %s\n", localPath);
        http.end();
        if (tft) {
            tft->fillScreen(TFT_BLACK);
            tft->setTextColor(TFT_RED);
            tft->setCursor(90, 150);
            tft->print("SD open failed!");
        }
        return false;
    }

    // 🖥️ Show download screen
    if (tft) {
        tft->fillScreen(TFT_BLACK);
        tft->setTextColor(TFT_WHITE);
        tft->setTextSize(2);
        tft->setCursor(90, 40);
        tft->print("Downloading...");
        tft->drawRect(50, 100, 220, 20, TFT_WHITE); // progress bar outline
    }

    uint8_t buf[2048];
    int totalRead = 0;
    unsigned long lastReadTime = millis();
    const unsigned long timeout = 10000;

    while (totalRead < contentLength) {
        int len = stream->readBytes(buf, sizeof(buf));
        if (len <= 0) {
            if (millis() - lastReadTime > timeout) {
                Serial.println("⏱️ Timeout: No data received for 10 seconds.");
                break;
            }
            delay(100);
            continue;
        }

        lastReadTime = millis();
        size_t writtenNow = file.write(buf, len);
        if (writtenNow != len) {
            Serial.println("❌ SD write error.");
            break;
        }

        totalRead += len;
        Serial.printf("📦 %d/%d bytes written\n", totalRead, contentLength);

        // 📊 Update progress bar
        if (tft) {
            int progress = map(totalRead, 0, contentLength, 0, 218);
            tft->fillRect(51, 101, progress, 18, TFT_GREEN);
        }
    }

    file.close();
    http.end();

    if (totalRead == contentLength) {
        Serial.printf("✅ Download complete: %d bytes written\n", totalRead);
        if (tft) {
            tft->setTextColor(TFT_GREEN);
            tft->setCursor(90, 150);
            tft->print("Download complete!");
        }
        return true;
    } else {
        Serial.printf("⚠️ Incomplete download: %d/%d bytes written\n", totalRead, contentLength);
        if (tft) {
            tft->setTextColor(TFT_RED);
            tft->setCursor(90, 150);
            tft->print("Download incomplete!");
        }
        return false;
    }
}