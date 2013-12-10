//#include <NoTFT.h>
//#include <HardwareSerial.h>
#include "MapScreen.h"

#define CENTER 160

PVector dataPoints[10];

int xAxisY = 220;
int yAxisX = 35;
int startingX = yAxisX + 10;
int startingY = xAxisY - 10;
int xFactor = 20;
int rectRadius = 10;

int currentDataPoint = 0;
int currentHighlightX = 0;
int targetHighlightX = 0;
int targetDataPoint = 0;
float minThresh = 45.0f;
float maxThresh = 105.0f;

PVector lowerColor = { 128.0f, 0, 0 };
PVector middleColor = { 0, 128.0f, 0 };
PVector upperColor = { 255.0f, 128.0f, 0 };

int animColorStep = 10;


MapScreen::MapScreen() {}
MapScreen::MapScreen(UTFT *gLCD) {
  _glcd = gLCD;
//  _clcd = cLCD;
//  _ledstrip = ledStrip;
  //_dataSet = dataSet;
  initDataSet();
}

void MapScreen::load(DataSet theSet){
  _dataSet = theSet;
}

void MapScreen::update(){
  draw();
}

void MapScreen::draw(){
  drawGUI();
} 



int MapScreen::getNumDataPoints(){
  return 10; // (int)(sizeof(_dataSet.dataPoints) / (sizeof(PVector)*3) );
}

void MapScreen::outputSerial(char* message) {
//  Serial.println(message);
}


void MapScreen::outputGraphicalLCD(char* message)
{
  _glcd->fillScr(0,0,0);
  _glcd->setColor(255, 0, 255);
  _glcd->fillRect(10, 10, 320, 230);
  
  _glcd->setBackColor(255, 0, 255);
  _glcd->setColor(255, 255, 255);
  _glcd->print(message, CENTER, 1, 0);
}

void MapScreen::outputCharLCD(char* message) {
//  _clcd->clear();
//  _clcd->print(message);
}

void MapScreen::outputLedStrip(uint32_t color)
{
//  for (int i=0; i<_ledstrip->numPixels(); i++) {
//    _ledstrip->setPixelColor(i, color);
//  }
//  _ledstrip->show();
}


void MapScreen::drawGUI()
{
  // Init background
  _glcd->setColor(0,0,0);
  _glcd->setColor(currentColor.x, currentColor.y, currentColor.z);
  _glcd->fillScr(currentColor.x, currentColor.y, currentColor.z);
  
  // Dividing Line Between Header and Data
  _glcd->setColor(0,0,0);
  _glcd->drawLine(11,50,309,50);

  // Black Rounded Rect for Year
  _glcd->setColor(0,0,0);
  _glcd->fillRoundRect(15, 12, 80, 45);

  // Year
  _glcd->setColor(255,255,255);
  _glcd->setBackColor(0,0,0);
  _glcd->print("2013", 16, 20);

  // Other Text
  _glcd->setColor(255,255,255);
  _glcd->setBackColor(currentColor.x, currentColor.y, currentColor.z);
  _glcd->print("Economic Data", 100, 17);

  // Black Graph Area 
  _glcd->setColor(0,0,0);
  _glcd->fillRect(21,60,240,230);

  // Draw X/Y Axes
  _glcd->setColor(255,255,255);
  _glcd->drawLine(yAxisX, 70, yAxisX, 225); // Vertical
  _glcd->drawLine(30, xAxisY, 230, xAxisY); // Horizontal
  
  // "Min Threshold" line
  _glcd->setColor(lowerColor.x, lowerColor.y, lowerColor.z);
  _glcd->drawLine(25, startingY - (int)minThresh,   235, startingY - (int)minThresh);

  // "Max Threshold" line
  _glcd->setColor(upperColor.x, upperColor.y, upperColor.z);
  _glcd->drawLine(25, startingY - (int)maxThresh, 235, startingY - (int)maxThresh);
  
  
//
//numDataPoints()
  for (int i=0; i<numDataPoints(); i++)
  {
    PVector thisPoint = _dataSet.dataPoints[i];   
//      Serial.print(thisPoint.x); Serial.print(" "); Serial.println(thisPoint.y);
//    // Draw border around selected column

//    stroke(255, 0, 0); 
//    fill(255, 0, 0); 


    if (i == currentDataPoint) {
//      stroke(255, 255, 255);
//      fill(192, 192, 192, 64);
//      rect(startingX + (thisPoint.x*xFactor) - (xFactor/2), startingY - 130, xFactor, 150);  

      
//      _glcd->setColor(192,192,192);
//      
//      int thisX = startingX + (thisPoint.x*xFactor) - (xFactor/2);
//      _glcd->fillRect(
//      thisX,
//      startingY - 130, 
//      thisX + xFactor, 
//      150);


//      textFont(f2);  
//      stroke(0); 
//      fill(255);
//      String year = Integer.toString((int)(thisPoint.x) + 1990);  
//      text(year, 30, 35);
    }

    // Draw lines connecting dataPoints  
    if (i > 0) {

      PVector lastPoint = _dataSet.dataPoints[i-1];
      _glcd->setColor(255,255,255);
      _glcd->drawLine( (startingX + thisPoint.x * xFactor), (startingY - thisPoint.y), 
                       (startingX + lastPoint.x * xFactor), (startingY - lastPoint.y)  );
    }
  }

//  // Draw 5px circles for dataPoints
  for (int i=0; i<10; i++)
  {
    PVector thisPoint = _dataSet.dataPoints[i];
//    stroke(255, 0, 0);
//    fill(255, 0, 0);
    _glcd->setColor(255,0,0);
    _glcd->fillCircle( (startingX + thisPoint.x*xFactor), (startingY - thisPoint.y), 5 );
//    ellipse(
//    startingX + thisPoint.x*xFactor, 
//    startingY - thisPoint.y, 
//    5, 5
//      );
  }
}


void MapScreen::cycleColors()
{

  PVector thisPoint = (PVector)dataPoints[currentDataPoint];
//  Serial.print(currentColor.x); Serial.print("   "); Serial.print(currentColor.y); Serial.print("   "); Serial.println(currentColor.z);

  // Set the targetColor
  if (thisPoint.y >= minThresh && thisPoint.y <= maxThresh) {
    targetColor = middleColor;
  }  else if (thisPoint.y < minThresh) {
    targetColor = lowerColor;
  } else if (thisPoint.y > maxThresh) { 
    targetColor = upperColor;
  }
  currentColor = targetColor;
  
  //  print("CX:"); print(currentColor.x);
  //  print(" Y:"); print(currentColor.y);
  //  print(" Z:"); println(currentColor.z);
  //  print("TX:"); print(targetColor.x);
  //  print(" Y:"); print(targetColor.y);
  //  print(" Z:"); println(targetColor.z);  
  //  println("");

//  if (currentColor.x < targetColor.x) { 
//      int newValue = (currentColor.x + animColorStep > targetColor.x) ? targetColor.x : currentColor.x + animColorStep;
//      PVector newColor = {  newValue, currentColor.y, currentColor.z };
//      currentColor = newColor;
//  }
//
//  if (currentColor.x > targetColor.x) { 
//      int newValue = (currentColor.x - animColorStep < 0) ? 0 : currentColor.x - animColorStep;
//      PVector newColor = {  newValue, currentColor.y, currentColor.z };
//      currentColor = newColor;
//  }
//
//
//  if (currentColor.y < targetColor.y) { 
//      int newValue = (currentColor.y + animColorStep > targetColor.y) ? targetColor.y : currentColor.y + animColorStep;
//      PVector newColor = {  currentColor.x, newValue, currentColor.z };
//      currentColor = newColor;
//  }
//
//  if (currentColor.y > targetColor.y) { 
//      int newValue = (currentColor.y - animColorStep < 0) ? 0 : currentColor.y - animColorStep;
//      PVector newColor = {  currentColor.x, newValue, currentColor.z };
//      currentColor = newColor;
//  }
//
//
//  if (currentColor.z < targetColor.z) { 
//      int newValue = (currentColor.z + animColorStep > targetColor.z) ? targetColor.z : currentColor.z + animColorStep;
//      PVector newColor = {  currentColor.x, currentColor.y, newValue};
//      currentColor = newColor;
//  }
//
//  if (currentColor.z > targetColor.z) { 
//      int newValue = (currentColor.z - animColorStep < 0) ? 0 : currentColor.z - animColorStep;
//      PVector newColor = {  currentColor.x, currentColor.y, newValue };
//      currentColor = newColor;
//  }
}

void MapScreen::init()
{
//  Serial.println("initing..................");
  for (int i=0; i<10; i++)
  {
    PVector vect;
    vect.x = i; vect.y = random(0,125); vect.z = 0;
    dataPoints[i] = vect;
  }
}



int MapScreen::numDataPoints() { 
  return sizeof(dataPoints)/sizeof(PVector);
}


void MapScreen::nextDataPoint() {
  currentDataPoint = (currentDataPoint+1 < numDataPoints()) ? currentDataPoint+1 : 0;
}
void MapScreen::prevDataPoint() {
  currentDataPoint = (currentDataPoint-1 > 0) ? currentDataPoint-1 : numDataPoints() - 1;
}

void MapScreen::initDataSet()
{
  
  DataSet newDataSet;
    
  newDataSet.xDesc = "Year";    newDataSet.xMin = 1990; newDataSet.xMax = 2014;
  newDataSet.yDesc = "Dollars"; newDataSet.yMin = 0;    newDataSet.yMax = 200000;

  PVector lowerColor  = { 127.0f, 0, 0 }; newDataSet.lowerColor  = lowerColor;
  PVector middleColor = { 127.0f, 0, 0 }; newDataSet.middleColor = middleColor;
  PVector upperColor  = { 127.0f, 0, 0 }; newDataSet.upperColor  = upperColor;
//
//  for (int i=0; i<2; i++)
//  {
//    PVector thisVector = { i, random(0,125), 0 };
//    dataSet.dataPoints[i] = thisVector;
//  }
//
  PVector dataPoints[10] = { 
    {    0,  50.0f, 0 }, 
    { 1.0f, 100.0f, 0 }, 
    { 2.0f,  63.0f, 0 }, 
    { 3.0f, 111.0f, 0 }, 
    { 4.0f,  12.0f, 0 }, 
    { 5.0f,   7.0f, 0 },  
    { 6.0f,  14.0f, 0 },  
    { 7.0f,  12.0f, 0 }, 
    { 8.0f,  50.0f, 0 },  
    { 9.0f,  23.0f, 0 }
  };
  memcpy(newDataSet.dataPoints, dataPoints, 10*sizeof(PVector) );
  _dataSet = newDataSet;
  
//  Serial.println(newDataSet.xDesc);
}

