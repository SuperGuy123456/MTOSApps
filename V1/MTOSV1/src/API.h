#pragma once
#include "LGFX_config.h"

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
};