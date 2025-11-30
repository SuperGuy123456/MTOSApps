
#include <Arduino.h>
#include "Button.h"
#include <functional>
#include "API.h"
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
InvisButton install (17, 0, 64, 64);
InvisButton run(91, 0, 64, 64);
InvisButton sdv (165, 0, 64, 64);
InvisButton sett(239, 0, 64, 64);


bool update = false; //If true, will cause a screen update, otherwise, no update(prevents flickering)

//Initialize State
State cstate;
void setup() {
  lcd.init();
  lcd.setRotation(3);

  Serial.begin(9600);
  SPI.begin(18, 19, 23, 5);
  if (!SD.begin(5, SPI, 25000000)) {   // CS pin for SD card
    Serial.println("SD init failed!");
    return;
  }


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
      Serial.println("Menu mode!");
      lcd.fillScreen(TFT_BLACK);
      API::DrawRaw("/os/img/install.raw", 17, 0, 64, 64);
      API::DrawRaw("/os/img/run.raw",     91, 0, 64, 64);
      API::DrawRaw("/os/img/sdv.raw",    165, 0, 64, 64);
      API::DrawRaw("/os/img/sett.raw",   239, 0, 64, 64);

      update = false;
  }

  if (install.CheckPress() or sdv.CheckPress() or sett.CheckPress()) //These three are WASM programs (not living on flash)
  {
    cstate = State::RUN;
    update = true;
  }
  if (run.CheckPress()) // Only Program that lives on flash (since it has to run wasm files)
  {
    cstate = State::BOOT;
    update = true;
  }

 }
 else if (cstate == State::BOOT)
 {
  //menu to run apps
  if (update)
  {
      update = false;
    lcd.fillScreen(TFT_BLACK);
  }
 }
 else if (cstate == State::RUN)
 {
  //When running .wasm
  if (update)
  {
      update = false;
    lcd.fillScreen(TFT_BLACK);
  }
 }
  delay(50); // small debounce

}