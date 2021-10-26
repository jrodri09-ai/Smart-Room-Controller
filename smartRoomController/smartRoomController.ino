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

int PIXELPIN = 5;
int PIXELCOUNT = 16;
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


}

void click () {
  buttonState = !buttonState;
  if (buttonState) {
    Serial.printf("button state %i\n", buttonState);
    tone(5, frequency, duration);
    for (int i = 0; i < 2; i++) {
      timer.startTimer(1000);
      pixel.clear();
      pixel.fill(blue, 0, 16);
      pixel.show();
      while (!timer.isTimerReady());
      timer.startTimer(1000);
      pixel.clear();
      pixel.show();
      while (!timer.isTimerReady());
      
    }
  }
  else {
    pixel.clear();
    pixel.show();
    noTone(5);
  }
}
