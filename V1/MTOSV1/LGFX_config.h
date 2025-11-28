#include <LovyanGFX.hpp>

// Custom LGFX device for CYD board
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9341 _panel;
  lgfx::Bus_SPI       _bus;
  lgfx::Touch_XPT2046 _touch;

public:
  LGFX(void) {
    { // ---- HSPI bus for TFT ----
      auto cfg = _bus.config();
      cfg.spi_host   = HSPI_HOST;   // HSPI for display
      cfg.spi_mode   = 0;
      cfg.freq_write = 80000000;    // 80 MHz write
      cfg.freq_read  = 20000000;    // 20 MHz read
      cfg.pin_sclk   = 18;
      cfg.pin_mosi   = 23;
      cfg.pin_miso   = 19;
      cfg.pin_dc     = 2;
      _bus.config(cfg);
      _panel.setBus(&_bus);
    }

    { // ---- TFT panel config ----
      auto cfg = _panel.config();
      cfg.pin_cs   = 15;
      cfg.pin_rst  = 4;
      cfg.pin_bl   = 13;            // backlight
      cfg.panel_width  = 240;
      cfg.panel_height = 320;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits  = 1;
      cfg.readable = true;
      cfg.invert   = false;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = true;
      _panel.config(cfg);
    }

    { // ---- Touch controller config ----
      auto cfg = _touch.config();
      cfg.spi_host = -1;            // bit-bang mode
      cfg.pin_cs   = 5;
      cfg.pin_sclk = 25;
      cfg.pin_mosi = 32;
      cfg.pin_miso = 35;
      cfg.freq     = 2500000;       // ~2.5 MHz
      cfg.x_min    = 0;
      cfg.x_max    = 240;
      cfg.y_min    = 0;
      cfg.y_max    = 320;
      cfg.offset_rotation = 0;
      _touch.config(cfg);
      _panel.setTouch(&_touch);
    }

    setPanel(&_panel);
  }
};

// Instantiate globally
LGFX lcd;