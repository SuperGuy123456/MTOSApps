#include <Arduino.h>
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9341 _panel;
  lgfx::Bus_SPI       _bus_tft;
  lgfx::Touch_XPT2046 _touch;

public:
  LGFX(void) {
    { // ---- VSPI bus for TFT ----
      auto cfg = _bus_tft.config();
      cfg.spi_host   = VSPI_HOST;   // CYD uses VSPI, not HSPI
      cfg.pin_sclk   = 14;
      cfg.pin_mosi   = 13;
      cfg.pin_miso   = 12;
      cfg.pin_dc     = 2;
      cfg.freq_write = 40000000;
      cfg.freq_read  = 16000000;
      _bus_tft.config(cfg);
      _panel.setBus(&_bus_tft);
    }

    { // ---- TFT panel config ----
      auto cfg = _panel.config();
      cfg.pin_cs   = 15;
      cfg.pin_rst  = -1; // tied to EN
      cfg.panel_width  = 240;
      cfg.panel_height = 320;
      cfg.readable = true;
      cfg.bus_shared = true;
      _panel.config(cfg);
    }

    { // ---- Touch controller config (dedicated pins) ----
      auto cfg = _touch.config();
      cfg.spi_host = -1;       // bit-bang mode
      cfg.pin_cs   = 33;       // TOUCH_CS
      cfg.pin_sclk = 25;       // TOUCH_CLK
      cfg.pin_mosi = 32;       // TOUCH_MOSI
      cfg.pin_miso = 39;       // TOUCH_MISO
      cfg.freq     = 2500000;
      cfg.x_min    = 0;
      cfg.x_max    = 240;
      cfg.y_min    = 0;
      cfg.y_max    = 320;
      _touch.config(cfg);
      _panel.setTouch(&_touch);
    }


    setPanel(&_panel);
  }
};

extern LGFX lcd;