#include <math.h>

const double PI = 3.1415926535897932384626433892795;
double radians(double deg) { return deg * PI / 180; }

extern "C" double mySin(double deg) { return sin(radians(deg)); }
extern "C" double myCos(double deg) { return cos(radians(deg)); }
extern "C" double myTan(double deg) { return tan(radians(deg)); }
extern "C" void init() {}
