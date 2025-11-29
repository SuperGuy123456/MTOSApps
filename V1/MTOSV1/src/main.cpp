
#include <Arduino.h>
#include "API.h"
#include "Button.h"
 //#define LGFX_AUTODETECT
//#include <LovyanGFX.hpp>
 //static LGFX lcd;

//screen dimensions are 320x240

enum State
{
  SPLASH, //MTOS and start button
  MENU, //With Installr, Boot menu, SD Viewer, About
  BOOT, //Shows downloaded apps
  RUN //Running .wasm file
};

SimpleButton StartBtn("start", ((320  - 100)  / 2) + 0, ((240 - 50) / 2) + 80, TFT_WHITE, TFT_RED, 3);

bool update = false; //If true, will cause a screen update, otherwise, no update(prevents flickering)

//Initialize State
State cstate;
void setup() {
  lcd.init();
  lcd.setRotation(3);
  Serial.begin(9600);

  pinMode(21, OUTPUT);
  analogWrite(21, 255); // try to set brightness using pinmode?

  cstate = State::SPLASH; //set it to splash

  //Draw Splash
  API::DrawText("MTOS", 2,-68, TFT_DARKGRAY, TFT_BLACK, 7, true, true);
  API::DrawText("MTOS", 0,-70, TFT_WHITE, TFT_BLACK, 7, true, true);
  API::DrawText("By: Manomay Tyagi 2025", 0, 0, TFT_WHITE, TFT_BLACK, 2, true, true);

  //Draw Main OS
  StartBtn.SetWidth();
  StartBtn.Draw();
}

void loop() {
 if (cstate == State::SPLASH)
 {
    if (StartBtn.CheckPress())
    {
      cstate = State::MENU;
      update = true;
    }
 }
 else if (cstate == State::MENU)
 {
  //display installr, boot, sd, about
  if (update)
  {
      //draw btns
      lcd.fillScreen(TFT_BLACK);
      update = false;
  }
 }
 else if (cstate == State::BOOT)
 {
  //menu to run apps
  if (update)
  {
      update = false;
  }
 }
 else if (cstate == State::RUN)
 {
  //When running .wasm
  if (update)
  {
      update = false;
  }
 }
  delay(50); // small debounce

}