/*
Just prints hello world on screen and exits as fast as possible
*/

extern "C" {

extern void DrawText(const char* text,
                     int x, int y,
                     int fgcolor, int bgcolor,
                     unsigned char size,
                     bool nobg, bool centered);
}

int main() {  // Changed from app_main
    DrawText("Hello World",
             0, 0,
             0xFFFFFF,
             0x000000,
             2,
             true,
             false);
    return 0;
}