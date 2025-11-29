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