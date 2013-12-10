import java.util.List;
import processing.serial.*;

Serial serial;

PFont f1, f2, f3;

int xAxisY = 205;
int yAxisX = 35;
int startingX = yAxisX + 10;
int startingY = xAxisY - 10;
int xFactor = 25;
int rectRadius = 10;
int animColorStep = 10;

PVector lowerColor = new PVector(128.0f, 0, 0);
PVector middleColor = new PVector(0, 128.0f, 0f);
PVector upperColor = new PVector(255.0f, 128.0f, 0);

PVector currentColor = new PVector(0, 0, 0);
PVector targetColor = new PVector(middleColor.x, middleColor.y, middleColor.z);
;

float minThresh = 45.0f;
float maxThresh = 105.0f;

ArrayList dataPoints = new ArrayList();

int currentDataPoint = 0;
int currentHighlightX = 0;
int targetHighlightX = 0;
int targetDataPoint = 0;

int numDataPoints() { 
  return dataPoints.size();
}

long updateInterval = 2000;
long animInterval = 1000/60;

long lastUpdateTime;
long lastAnimTime;

boolean shouldUpdateNow = false;


void setup()
{
  println(Serial.list());
//  serial = new Serial(this, "/dev/tty.slave", 9600);
  //  ser
  size(320, 240);

  f1 = createFont("courier", 8);
  f2 = createFont("courier", 16);
  f3 = createFont("courier", 24);

  for (int i=0; i<10; i++)
  {
    dataPoints.add(new PVector(i, random(0, 125)));
  }
}








void draw()
{
  update();
  drawGUI();
}

void update()
{
  while (serial.available () > 0) {
    char input = serial.readChar(); // serial.readStringUntil('\n');
    println(input);
  }

  long now = millis();
  boolean intervalElapsed = (now-lastUpdateTime > updateInterval);
  boolean animationTicked = (now - lastAnimTime > animInterval);

  if (animationTicked) {
    cycleColors();
    lastAnimTime = now;
  }

  if (shouldUpdateNow || intervalElapsed) {
    nextDataPoint();
    lastUpdateTime = now;
    shouldUpdateNow = false;
  }
}




void drawGUI()
{
  // Init background
  background(0, 0, 0, 32); //_glcd.fillScr(0,0,0);  

  fill(currentColor.x, currentColor.y, currentColor.z); 

  // Colored inset area
  stroke(255, 255, 255);
  //  fill(255,0,0);
  rect(10, 10, 300, 220, rectRadius);

  // Dividing Line
  stroke(0);
  line(11, 50, 309, 50);

  // Header
  fill(0);
  rect(20, 15, 60, 30, rectRadius);

  //  textFont(f2);  
  //  stroke(0); fill(255);  
  //  text("2013", 30, 35);


  textFont(f3);  
  text("Economic Data", 100, 37);


  // Graph Area 
  fill(0);
  stroke(255);
  rect(21, 60, 278, 160);

  stroke(255);

  line(yAxisX, 70, yAxisX, 210);   // Vertical
  line(30, xAxisY, 290, xAxisY); // Horizontal


  // Draw min and max lines, and set color based on if current item breaks threshold
  stroke(lowerColor.x, lowerColor.y, lowerColor.z); 
  fill(lowerColor.x, lowerColor.y, lowerColor.z);
  line(
  25, startingY - (int)minThresh, 
  295, startingY - (int)minThresh 
    );

  stroke(upperColor.x, upperColor.y, upperColor.z); 
  fill(upperColor.x, upperColor.y, upperColor.z);
  line(
  25, startingY - (int)maxThresh, 
  295, startingY - (int)maxThresh 
    );


  for (int i=0; i<numDataPoints(); i++)
  {
    PVector thisPoint = (PVector)dataPoints.get(i);   

    // Draw border around selected column
    stroke(255, 0, 0); 
    fill(255, 0, 0); 
    if (i == currentDataPoint) {
      stroke(255, 255, 255);
      fill(192, 192, 192, 64);
      rect(
      startingX + (thisPoint.x*xFactor) - (xFactor/2), 
      startingY - 130, 
      xFactor, 
      150
        );  

      textFont(f2);  

      stroke(0); 
      fill(255);

      String year = Integer.toString((int)(thisPoint.x) + 1990);  
      text(year, 30, 35);
    }

    // Draw lines connecting dataPoints  
    if (dataPoints.indexOf(thisPoint) > 0) {
      PVector lastPoint = (PVector)dataPoints.get(i-1);
      stroke(255); 
      fill(255);  
      line(
      startingX + thisPoint.x*xFactor, 
      startingY - thisPoint.y, 
      startingX + lastPoint.x*xFactor, 
      startingY - lastPoint.y
        );
    }
  }

  // Draw 5px circles for dataPoints
  for (int i=0; i<10; i++)
  {
    PVector thisPoint = (PVector)dataPoints.get(i);
    stroke(255, 0, 0);
    fill(255, 0, 0);
    ellipse(
    startingX + thisPoint.x*xFactor, 
    startingY - thisPoint.y, 
    5, 5
      );
  }
}



void cycleColors()
{

  PVector thisPoint = (PVector)dataPoints.get(currentDataPoint);
  if (thisPoint.y >= minThresh && thisPoint.y <= maxThresh) {
    targetColor = new PVector(middleColor.x, middleColor.y, middleColor.z);
  } 
  else if (thisPoint.y < minThresh) {
    targetColor = new PVector(lowerColor.x, lowerColor.y, lowerColor.z);
  } 
  else if (thisPoint.y > maxThresh) { 
    targetColor = new PVector(upperColor.x, upperColor.y, upperColor.z);
  }

  //  print("CX:"); print(currentColor.x);
  //  print(" Y:"); print(currentColor.y);
  //  print(" Z:"); println(currentColor.z);
  //  print("TX:"); print(targetColor.x);
  //  print(" Y:"); print(targetColor.y);
  //  print(" Z:"); println(targetColor.z);  
  //  println("");

  if (currentColor.x < targetColor.x) { 
    currentColor.x += animColorStep; 
    if (currentColor.x > targetColor.x) currentColor.x = targetColor.x;
  }

  if (currentColor.x > targetColor.x) { 
    currentColor.x -= animColorStep;
    if (currentColor.x < targetColor.x) currentColor.x = targetColor.x;
  } 

  if (currentColor.y < targetColor.y) {
    currentColor.y += animColorStep; 
    if (currentColor.y > targetColor.y) currentColor.y = targetColor.y;
  }
  if (currentColor.y > targetColor.y) { 
    currentColor.y -= animColorStep;
    if (currentColor.y < targetColor.y) currentColor.y = targetColor.y;
  }

  if (currentColor.z < targetColor.z) { 
    println("zup");
    currentColor.z += animColorStep;
    if (currentColor.z > targetColor.z) currentColor.z = targetColor.z;
  }

  if (currentColor.z > targetColor.z) { 
    println("zdn");
    currentColor.z -= animColorStep;
    if (currentColor.z < targetColor.z) currentColor.z = targetColor.z;
  }
}

void nextDataPoint() {
  currentDataPoint = (currentDataPoint+1 < numDataPoints()) ? currentDataPoint+1 : 0;
}
void prevDataPoint() {
  currentDataPoint = (currentDataPoint-1 > 0) ? currentDataPoint-1 : numDataPoints() - 1;
}

