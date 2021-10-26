/*
   Project: Smart Room Controller
   Description:
   Author: Jessica Rodriquez
   Date:
*/



#include <OneButton.h>
#include <Adafruit_NeoPixel.h>
#include <colors.h>
#include <IoTTimer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int PIXELPIN = 5;
int PIXELCOUNT = 12;
const int BUTTONPIN = 23;
bool buttonState;
int pixels;
unsigned int frequency = 396;
unsigned long duration = 1000;

OneButton button1(BUTTONPIN, false); //define objects
Adafruit_NeoPixel pixel(PIXELCOUNT, PIXELPIN, NEO_GRB + NEO_KHZ800 );
IoTTimer timer;

void setup() {
  Serial.begin (9600) ; // begin processes
  pixel.begin();
  pixel.show();
  pixel.setBrightness(25);
  button1.attachClick(click); // initialize objects
  buttonState = false ; // set variables



}

void loop() {
  button1.tick();
  if (buttonState) {
    Serial.printf("button state %i\n", buttonState);
    //tone(, frequency, duration);
    for (int i = 0; i <= 2; i++) {
      delay(1000);
      pixel.clear();
      pixel.fill(blue, 0, PIXELCOUNT);
      pixel.show();
      delay(1000);
      pixel.clear();
      pixel.show();
      //timer.startTimer(4000);
    }
    timer.startTimer(4000);
    pixel.clear();
    pixel.fill(blue, 0, PIXELCOUNT);
    pixel.show();
    if (timer.isTimerReady()) {
      buttonState = false;
      Serial.printf("timer ready");
    }
  }
  else {
    pixel.clear();
    pixel.show();
    //noTone(5);
  }


}

void click () {
  buttonState = true;

}
