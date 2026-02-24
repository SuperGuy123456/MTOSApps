/*
FullAPITest — imports every MTOS API v1 function
*/


// import every function
extern "C" {

// =========================
// SCREEN + DRAWING
// =========================

extern void DrawText(const char* text,
                     int x, int y,
                     int fgcolor, int bgcolor,
                     unsigned char size,
                     bool nobg, bool centered);

extern int  DrawPixel(int x, int y, int color);
extern int  ClearScreen(int color);

extern int  DrawRect(int x, int y, int w, int h, int color);
extern int  FillRect(int x, int y, int w, int h, int color);

extern int  DrawCircle(int x, int y, int r, int color);
extern int  FillCircle(int x, int y, int r, int color);

extern int  DrawRaw(const char* path,
                    int x, int y,
                    int w, int h);


// =========================
// TOUCH
// =========================

extern int  PollTouch(int* outPtr);


// =========================
// WIFI + NETWORK
// =========================

extern int  ConnectToWiFi(const char* ssid,
                          const char* password);

extern int  DownloadFile(const char* url,
                         const char* localPath);

extern int  DownloadApp(const char* name);

extern int  CheckManifestUpToDate();


// =========================
// FILESYSTEM
// =========================

extern int  RecursiveDelete(const char* path);
extern int  FileExists(const char* path);

extern int  ReadFile(const char* path,
                     char* buffer,
                     int bufferSize);

extern int  WriteFile(const char* path,
                      const char* data);

extern int  AppendToFile(const char* path,
                         const char* data);

extern int  ListDirectory(const char* path);
extern int  CreateDirectory(const char* path);


// =========================
// TIME + DELAY
// =========================

extern int  GetTime();
extern void Delay(int ms);


// =========================
// RANDOM
// =========================

extern int  Random(int min, int max);

} // extern "C"

// convenience: 16-bit RGB565-ish style colors in 0xRRGGBB form
static inline int rgb(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}

int main()
{
    int startTime = GetTime();
    int totalDelay = 2400;//24 seconds of total delay across the test


    // Intro
    ClearScreen(0x000000);
    DrawText("Full API Test", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);
    Delay(2000);

    // Clear screen color test
    ClearScreen(0x000000);
    DrawText("Clear Screen Color Test", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);
    Delay(2000);

    ClearScreen(0xFF0000); // red
    Delay(1000);
    ClearScreen(0x00FF00); // green
    Delay(1000);
    ClearScreen(0x0000FF); // blue
    Delay(1000);

    // Drawing test header
    ClearScreen(0x000000);
    DrawText("Drawing Test", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);
    Delay(1000);

    // 1) Random starfield with DrawPixel
    ClearScreen(0x000000);
    DrawText("Random Starfield", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);

    for (int i = 0; i < 800; i++) {
        int x = Random(0, 480);
        int y = Random(0, 320);
        DrawPixel(x, y, 0xFFFFFF);
    }
    Delay(2000);

    // 2) Rectangles: outline + filled grid
    ClearScreen(0x000000);
    DrawText("Rectangles", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);

    // Outline frame
    DrawRect(10, 30, 460, 280, 0xFFFFFF);

    // Draw fewer rectangles to reduce stack usage
    FillRect(20, 50, 40, 30, rgb(255, 0, 0));
    FillRect(70, 50, 40, 30, rgb(0, 255, 0));
    FillRect(120, 50, 40, 30, rgb(0, 0, 255));
    FillRect(170, 50, 40, 30, rgb(255, 255, 0));
    FillRect(220, 50, 40, 30, rgb(255, 0, 255));
    Delay(2000);

    // 3) Concentric circles
    ClearScreen(0x000000);
    DrawText("Concentric Circles", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);

    int cx = 240;
    int cy = 160;
    for (int r = 10; r < 150; r += 10) {
        int col = rgb(Random(100, 255), Random(100, 255), Random(100, 255));
        DrawCircle(cx, cy, r, col);
    }
    Delay(2000);

    // 4) Filled circle pattern (bubbles)
    ClearScreen(0x000000);
    DrawText("Bubble Pattern", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);

    for (int i = 0; i < 40; i++) {
        int r = Random(5, 30);
        int x = Random(r, 480 - r);
        int y = Random(r + 20, 320 - r);
        int col = rgb(Random(80, 255), Random(80, 255), Random(80, 255));
        FillCircle(x, y, r, col);
    }
    Delay(2000);

    // 5) Diagonal lines made of pixels
    ClearScreen(0x000000);
    DrawText("Diagonal Pixel Lines", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);

    for (int d = 0; d < 320; d += 8) {
        int col = rgb(Random(100, 255), Random(100, 255), Random(100, 255));
        for (int x = 0; x < 480; x++) {
            int y = (x + d) % 320;
            DrawPixel(x, y, col);
        }
    }
    Delay(2000);

    // 6) Rect spiral
    ClearScreen(0x000000);
    DrawText("Rectangle Spiral", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);

    int x0 = 20, y0 = 40;
    int w = 440, h = 260;
    for (int i = 0; i < 15; i++) {
        int col = rgb(255 - i * 10, 50 + i * 10, 150);
        DrawRect(x0, y0, w, h, col);
        x0 += 10;
        y0 += 8;
        w  -= 20;
        h  -= 16;
    }
    Delay(2000);

    // 7) Filled rect stripes
    ClearScreen(0x000000);
    DrawText("Color Stripes", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);

    int stripeH = 40;
    for (int y = 20; y < 320; y += stripeH) {
        int col = rgb(Random(0, 255), Random(0, 255), Random(0, 255));
        FillRect(0, y, 480, stripeH, col);
    }
    Delay(2000);

    // 8) Text alignment / size test
    ClearScreen(0x000000);
    DrawText("Text Test", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);

    DrawText("Small", 10, 40, 0xFFFFFF, 0x000000, 1, true, false);
    DrawText("Medium", 10, 70, 0xFFAA00, 0x000000, 2, true, false);
    DrawText("Large", 10, 110, 0x00FFAA, 0x000000, 3, true, false);

    DrawText("Centered", 240, 200, 0xFFFFFF, 0x000000, 2, true, true);
    Delay(3000);

    // 9) Optional: DrawRaw test (if you have an asset)
    // ClearScreen(0x000000);
    // DrawText("DrawRaw Test", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);
    // DrawRaw("/MTOS/apps/FullAPITest/assets/test.raw", 0, 20, 240, 160);
    // Delay(3000);

    ClearScreen(0x000000);
    DrawText("Full API Drawing Test Done", 0, 0, 0xFFFFFF, 0x000000, 2, true, false);
    Delay(2000);


    return 0;
}
