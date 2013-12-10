//struct DataPoint { float x; float y; };

struct color { uint8_t r,g,b; };

typedef struct {
  float x;
  float y;
  float z;
} PVector;

typedef struct {
  float xMin, xMax, yMin, yMax; // Axis scales
  char *xDesc, *yDesc;

  PVector lowerColor;  float lowerThreshold;
  PVector middleColor;
  PVector upperColor;  float upperThreshold; 

  PVector dataPoints[10];
} DataSet;


