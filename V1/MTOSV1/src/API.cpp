#include "API.h"

void API::DrawText(const char* text, int x, int y,
                   int fgcolor, int bgcolor,
                   uint8_t size,
                   bool nobg, bool centered) {
  lcd.setTextSize(size);
  if (nobg) {
    lcd.setTextColor(fgcolor);
  } else {
    lcd.setTextColor(fgcolor, bgcolor);
  }

  if (centered) {
    int textWidth  = lcd.textWidth(text);
    int textHeight = lcd.fontHeight();
    lcd.setCursor(((lcd.width()  - textWidth)  / 2) + x,
                  ((lcd.height() - textHeight) / 2) + y);
  } else {
    lcd.setCursor(x, y);
  }
  lcd.print(text);
}

bool API::PollTouch(Vector2& coord)
{
    int32_t x;
    int32_t y;
    if (lcd.getTouch(&x, &y)) {
        // If touched, print coordinates
        x = map(x, 200, 3700, 1, 320) * -1;
        y = map(y, 240, 3800, 1, 240);
        coord.x = x;
        coord.y = y;
        return true;
    }
    coord.x = -1;
    coord.y = -1;
    return false;
}

bool API::DrawRaw(const char* path, int x, int y, int w, int h)
{
    File f = SD.open(path, FILE_READ);
    if (!f) {
        Serial.printf("Failed to open %s\n", path);
        return false;
    }

    // Buffer for one row of pixels
    uint16_t lineBuf[w];

    for (int row = 0; row < h; row++) {
        // Read w pixels (2 bytes each) into buffer
        size_t bytesRead = f.read((uint8_t*)lineBuf, w * 2);
        if (bytesRead != w * 2) {
            Serial.printf("Unexpected EOF in %s at row %d\n", path, row);
            f.close();
            return false;
        }

        // Push one row to TFT
        lcd.pushImage(x, y + row, w, 1, lineBuf);
    }

    f.close();
    return true;
}
