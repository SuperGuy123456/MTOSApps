#include "MTOSAPI.h"

// These function pointers will be patched by MTOS at load time.
extern "C" {

void (*_ClearScreen)(unsigned short);
void (*_DrawText)(const char*, int, int, unsigned short, unsigned short, int, int, int);
void (*_Delay)(int);

}

// Public API functions that the app calls
extern "C" void ClearScreen(unsigned short color) {
    _ClearScreen(color);
}

extern "C" void DrawText(const char* text, int x, int y,
                         unsigned short fg, unsigned short bg,
                         int size,
                         int nobg, int centered) {
    _DrawText(text, x, y, fg, bg, size, nobg, centered);
}

extern "C" void Delay(int ms) {
    _Delay(ms);
}
