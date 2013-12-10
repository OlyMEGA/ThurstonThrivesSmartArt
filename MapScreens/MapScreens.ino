//================================================================================================
// Thurston Thrives - Economic Action Team - Visualizing Economic Indicators Proof-of-Concept
// Justin Burns / OlyMEGA - 10/13
//================================================================================================

#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
//#include <SPI.h>
//#include <LPD8806.h>
#include <UTFT.h>
#include <UTouch.h>
//#include <UTFT_Buttons.h>

#include "MapScreen.h"
//#include <NoTFT.h>

#define ITDB32S 3

boolean needsRedraw = false;
const int prevButton = 2, nextButton = 3;
const int numScreens = 3, numLEDs = 2, numMessages = 3;
unsigned long updateInterval = 5000;
int x, y;

//NoTFT gLCD(ITDB32S, 38, 39, 40, 41, 0);  // Init the graphical LCD
UTFT gLCD(ITDB32S, 38, 39, 40, 41); //, 0, &Serial);  // Init the graphical LCD
UTouch      myTouch(6,5,4,3,2);
//UTFT_Buttons  myButtons(&gLCD, &myTouch);


//LiquidCrystal_I2C cLCD(0x27,16,2);      // Init character LCD, address 0x27 (16 chars, 2 lines)
//LPD8806 ledStrip = LPD8806(6);            // RGB LGD Strips  (Native SPI)

MapScreen mapScreen;
extern uint8_t SmallFont[];
extern uint8_t BigFont[];



unsigned long lastUpdateTime;
boolean shouldUpdateNow = false;

//========================================================================================================================================================================================================



//long updateInterval = 2000;
long animInterval = 1000/60;

//long lastUpdateTime;
long lastAnimTime;

//boolean shouldUpdateNow = false;


//========================================================================================================================================================================================================



void setup()
{
//  Serial.begin(38400);
    
//  ((NoTFT)gLCD).SetSerial(&Serial);
//  attachInterrupt(0, prevButtonPressed, FALLING);
//  attachInterrupt(1, nextButtonPressed, FALLING);

  // Initialize Screens
//  cLCD.init();
//  cLCD.backlight();

  gLCD.InitLCD();
  gLCD.clrScr();  
  gLCD.setFont(BigFont);

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
//  myButtons.setTextFont(SmallFont);

//  ledStrip.begin();
  
  // Init MapScreen class with test data
  mapScreen = MapScreen(&gLCD);
  mapScreen.init();

  shouldUpdateNow = true;
}

void loop()
{
//  int but1, but2, but3, butX, butY, pressed_button;
//  but1 = myButtons.addButton(250, 60,60,30, "Prev");
//  but2 = myButtons.addButton(250,100,60,30, "Next");
//  but3 = myButtons.addButton(250,200,60,30, "Info");
//  myButtons.drawButtons();


  while (1) {
    unsigned long now = millis();  

    
    if (myTouch.dataAvailable())
    {
//      myTouch.read();
//      x=myTouch.getX();
//      y=myTouch.getY();
//      
      pressed_button = myButtons.checkButtons();
//      Serial.print("Button: "); Serial.println(pressed_button);
//if (x > 0) {
//      Serial.print("x: "); Serial.print(x);      Serial.print("y: "); Serial.println(y);
//
//}
//      Serial.println("Touched!!!!!!!!!!!!!!!!!");
//      
      if (pressed_button == but1) { 
        mapScreen.prevDataPoint();
      } else if (pressed_button == but2) {
        mapScreen.nextDataPoint();
      } else if (pressed_button == but3) {
      }
//      
//      //gLCD.drawCircle(50,50,50);
    }
//
//
//    boolean intervalElapsed = (now - lastUpdateTime > updateInterval);
//    boolean animationTicked = (now - lastAnimTime > animInterval);
//  
////    if (animationTicked) {
////  //    needsRedraw = true;
////      lastAnimTime = now;
////    }
//  
//    if (shouldUpdateNow || intervalElapsed) {
//      mapScreen.cycleColors();
////      mapScreen.nextDataPoint();    
//      lastUpdateTime = now;
//
//      needsRedraw = true;
//      shouldUpdateNow = false;
//      lastUpdateTime = now;
//    }
//    
//    if (needsRedraw) {
//      mapScreen.update();
////      myButtons.drawButtons();
//      needsRedraw = false;
//    }
  }
}

void prevButtonPressed() {
  mapScreen.prevDataPoint();
  shouldUpdateNow = true;
}

void nextButtonPressed() {
  mapScreen.nextDataPoint();
  shouldUpdateNow = true;
}

void updateScreens() {
//  Serial.println("updating.....");
  mapScreen.update();
}



