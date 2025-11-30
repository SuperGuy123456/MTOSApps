#pragma once
#include "API.h"

class SimpleButton
{
public:
    const char* name;
    SimpleButton(const char* _name, int x, int y, const int textcolor, const int bgcolor, const int fontsize);
    ~SimpleButton();

    void SetWidth();
    bool CheckPress(); //returns name (assigned to button at init)
    void Draw();
private:
    Vector2 pos;
    Vector2 size;
    int textcolor, bgcolor, fontsize;
};

//Just a simple rectangle/square that can detect mouse press (no ui) for things like images
class InvisButton
{
public:
    InvisButton(int x, int y, int width, int height);
    ~InvisButton();

    void ChangeWidth(int _w, int _h);

    bool CheckPress();
private:
    Vector2 pos;
    Vector2 size;
};