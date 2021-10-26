/*
   Project: Smart Room Controller
   Description: Miterm Project
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
#include <SPI.h>
#include <Ethernet.h>
#include <mac.h>
#include <hue.h>
#include <wemo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define SCREEN_ADDRESS 0X3C

int PIXELPIN = 5;
int PIXELCOUNT = 12;
const int BUTTONPIN = 23;
bool buttonState;
int pixels;
unsigned int frequency = 396;
unsigned long duration = 1000;
int currentTime;
int lastTime;

OneButton button1(BUTTONPIN, false); //define objects
Adafruit_NeoPixel pixel(PIXELCOUNT, PIXELPIN, NEO_GRB + NEO_KHZ800 );
IoTTimer timer;
Adafruit_SSD1306 display (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

EthernetClient client;
bool status;   //user to ensure port openned correctly
byte thisbyte; //used to get IP address

void setup() {
  Serial.begin (9600) ; // begin processes
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  button1.attachClick(click); // initialize objects

  //initialize ethernet port and uSD module to off
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  //Open Serial Communication and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  Serial.printf("Starting Program:\n");

  //Start ethernet connection
  status = Ethernet.begin(mac);
  if (!status) {
    Serial.printf("failed to configure Ethernet using DHCP \n");
    //no point in continueing
    while (1);
  }

  //print your local IP address
  Serial.print("My IP address: ");
  for (thisbyte = 0; thisbyte < 3; thisbyte++) {
    //print value of each byte of the IP address
    Serial.printf("%i.", Ethernet.localIP()[thisbyte]);
  }
  Serial.printf("%i\n", Ethernet.localIP()[thisbyte]);



  display.display();
  delay(2000);
  pixel.begin();
  pixel.show();
  pixel.setBrightness(25);
  button1.attachClick(click); // initialize objects
  buttonState = false ; // set variables
}

void loop() {
  button1.tick();
  currentTime = millis();
  if (buttonState) {
    Serial.printf("button state %i\n", buttonState);
    //tone(, frequency, duration);
    for (int i = 0; i < 2; i++) {
      pixel.fill(blue, 0, PIXELCOUNT);
      pixel.show();
      delay(1000);
      pixel.clear();
      pixel.show();
      delay(1000);
    }
    pixel.clear();
    pixel.show();
    pixel.fill(blue, 0, PIXELCOUNT);
    pixel.show();
    delay(4000);
    buttonState = false;
    //Use different timer
    //    if (currentTime-lastTime > 5000) {
    //      lastTime = millis();
    //      buttonState = false;
    //      Serial.printf("timer ready");
    // }
    doorbellringingtext();
    display.clearDisplay();
    display.display();
  }
  else {
    pixel.clear();
    pixel.show();
    //noTone(5);
  }
}

void click () {
  buttonState = true;
   Serial.printf("button state %i\n",buttonState);
  if (buttonState) {
    switchON(0);
  }
    else {
    switchOFF(0);
  }
}

void doorbellringingtext (void) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.printf("Doorbell Ringing!");
  display.display();
  delay(2000);
}
