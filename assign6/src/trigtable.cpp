#include <math.h>

const int NUM_DEGS = 360;
const double PI = 3.1415926535897932384626433892795;
double sin_table[NUM_DEGS], cos_table[NUM_DEGS], tan_table[NUM_DEGS];

double radians(int deg) { return deg * PI / 180; }
double linterp(double* table, double deg) {
    int left, right;
    double dx, dy;

    // Get angle boundaries
    left = (int)(deg) % NUM_DEGS;
    right = (left + 1) % NUM_DEGS;

    // Get differentials
    dx = deg - (int)(deg);
    dy = table[right] - table[left];

    // Return linear interprolation
    return table[left] + dy*dx;
}

extern "C" double mySin(double deg) { return linterp(sin_table, deg); }
extern "C" double myCos(double deg) { return linterp(cos_table, deg); }
extern "C" double myTan(double deg) { return linterp(tan_table, deg); }
extern "C" void init() {
    for (int deg = 0; deg < NUM_DEGS; ++deg) {
        double rad = radians(deg);
        sin_table[deg] = sin(rad);
        cos_table[deg] = cos(rad);
        tan_table[deg] = tan(rad);
    }
}
