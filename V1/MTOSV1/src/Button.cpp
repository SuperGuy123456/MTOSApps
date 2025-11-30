#include "Button.h"

SimpleButton::SimpleButton(const char* _name, int x, int y, const int _textcolor, const int _bgcolor, const int _fontsize)
{
    name = _name;

    pos.x = x;
    pos.y = y;

    textcolor = _textcolor;
    bgcolor = _bgcolor;
    fontsize = _fontsize;
}

SimpleButton::~SimpleButton(){};

void SimpleButton::SetWidth()
{
    lcd.setTextSize(fontsize);

    size.x = lcd.textWidth(name);
    size.y = lcd.fontHeight();
}

bool SimpleButton::CheckPress()
{
    Vector2 coord;
    if (API::PollTouch(coord))
    {
        if ((coord.x > pos.x and coord.x < pos.x+size.x) and (coord.y > pos.y and coord.y < pos.y + size.y))
        {
            return true;
        }
    }
    return false;
}

void SimpleButton::Draw()
{
    lcd.fillRect(pos.x, pos.y, size.x, size.y, TFT_RED);
    API::DrawText(name, pos.x, pos.y, textcolor, bgcolor, fontsize, true, false);
}

//For invisible button

InvisButton::InvisButton(int x, int y, int width, int height)
{
    pos.x = x;
    pos.y = y;

    size.x = width;
    size.y = height;
}

InvisButton::~InvisButton(){};

void InvisButton::ChangeWidth(int _w, int _h)
{
    size.x = _w;
    size.y = _h;
}

bool InvisButton::CheckPress()
{
    Vector2 coord;
    if (API::PollTouch(coord))
    {
        if ((coord.x > pos.x and coord.x < pos.x+size.x) and (coord.y > pos.y and coord.y < pos.y + size.y))
        {
            return true;
        }
    }
    return false;
}