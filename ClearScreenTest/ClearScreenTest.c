__attribute__((import_module("env"), import_name("ClearScreen")))
extern int ClearScreen(int color);

__attribute__((import_module("env"), import_name("DrawText")))
extern void DrawText(const char* text,
                     int x, int y,
                     int fg, int bg,
                     int size,
                     int nobg,
                     int centered);

__attribute__((import_module("env"), import_name("Delay")))
extern void Delay(int ms);

__attribute__((used, export_name("main")))
int main() {
    ClearScreen(0x0000);
    DrawText("Clear Screen Test", 0, 0,
             0xFFFF, 0x0000,
             2, 1, 0);
    Delay(1000);

    ClearScreen(0xF800);
    Delay(1000);

    ClearScreen(0x07E0);
    Delay(1000);

    ClearScreen(0x001F);
    Delay(1000);

    return 0;
}
