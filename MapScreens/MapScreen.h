#include <vector>
#include <UTFT.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <LPD8806.h>
#include "Util.h"
class NoTFT;

class MapScreen {

public:
  MapScreen();
  MapScreen(UTFT *gLCD);
  
  void load(DataSet theSet);
  void update();
  void draw(); 

  void nextDataPoint();
  void prevDataPoint();

  int getNumDataPoints();
   void init();
   void cycleColors();  
   
private:  
        void drawGUI();
         void outputSerial(char* message);
         void outputGraphicalLCD(char* message);
         void outputCharLCD(char* message);
         void outputLedStrip(uint32_t color);
          void initDataSet();
         int numDataPoints();
        PVector currentColor;
        PVector targetColor;

               UTFT *_glcd;
//  LiquidCrystal_I2C *_clcd;
//            LPD8806 *_ledstrip;

             DataSet _dataSet;
             uint8_t _currentDataPointIndex;
};
