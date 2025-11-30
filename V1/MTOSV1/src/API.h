#pragma once
#include "LGFX_config.h"
#include <SD.h>

struct Vector2
{
    int32_t x;
    int32_t y;
};

class API {
public:
  static void DrawText(const char* text, int x, int y,
                       int fgcolor, int bgcolor,
                       uint8_t size,
                       bool nobg=false, bool centered=false);
    static bool PollTouch(Vector2& coord);
    static bool DrawRaw(const char* path, int x, int y, int w, int h);
};