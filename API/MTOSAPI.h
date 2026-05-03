#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// =========================
// SCREEN
// =========================

void ClearScreen(unsigned short color);

void DrawText(const char* text, int x, int y,
              unsigned short fg, unsigned short bg,
              int size,
              int nobg, int centered);

int  DrawRaw(const char* path, int x, int y, int w, int h);

int  DrawPixel(int x, int y, unsigned short color);

int  DrawRect(int x, int y, int w, int h, unsigned short color);
int  FillRect(int x, int y, int w, int h, unsigned short color);

int  DrawCircle(int x, int y, int r, unsigned short color);
int  FillCircle(int x, int y, int r, unsigned short color);


// =========================
// TOUCH
// =========================

typedef struct {
    int x;
    int y;
} Vector2;

int PollTouch(Vector2* out);


// =========================
// WIFI + NETWORK
// =========================

int ConnectToWiFi(const char* ssid, const char* password);

int DownloadFile(const char* url, const char* localPath);

int DownloadApp(const char* name);

int CheckManifestUpToDate();


// =========================
// FILESYSTEM
// =========================

int RecursiveDelete(const char* path);
int FileExists(const char* path);

int ReadFile(const char* path, char* buffer, int bufferSize);

int WriteFile(const char* path, const char* data);
int AppendToFile(const char* path, const char* data);

int ListDirectory(const char* path);
int CreateDirectory(const char* path);


// =========================
// TIME + DELAY
// =========================

unsigned int GetTime();
void Delay(int ms);


// =========================
// RANDOM
// =========================

int Random(int min, int max);


#ifdef __cplusplus
}
#endif
