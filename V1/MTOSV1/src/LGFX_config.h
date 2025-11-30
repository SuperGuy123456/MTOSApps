#include <Arduino.h>
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9341 _panel;
  lgfx::Bus_SPI       _bus_tft;
  lgfx::Touch_XPT2046 _touch;

public:
  LGFX(void) {
    { // ---- HSPI bus for TFT ----
      auto cfg = _bus_tft.config();
      cfg.spi_host   = HSPI_HOST;   // CYD uses HSPI for TFT
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
      auto pcfg = _panel.config();
      pcfg.pin_cs   = 15;
      pcfg.pin_rst  = -1;
      pcfg.bus_shared = false;      // TFT is on its own bus
      _panel.config(pcfg);
    }

    { // ---- Touch controller config (dedicated pins) ----
      auto tcfg = _touch.config();
      tcfg.spi_host = -1;           // bit-bang mode
      tcfg.pin_cs   = 33;
      tcfg.pin_sclk = 25;
      tcfg.pin_mosi = 32;
      tcfg.pin_miso = 39;
      tcfg.freq     = 2500000;
      tcfg.bus_shared = false;      // independent pins
      tcfg.x_min    = 0;
      tcfg.x_max    = 240;
      tcfg.y_min    = 0;
      tcfg.y_max    = 320;
      _touch.config(tcfg);
      _panel.setTouch(&_touch);
    }

    setPanel(&_panel);
  }
};

extern LGFX lcd;