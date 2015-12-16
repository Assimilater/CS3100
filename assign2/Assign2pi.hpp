#pragma once
#include <string>

//---------------------------------------------------------------------------------+
// double pi                                                                       |
// Uses the second algorithm: http://en.wikipedia.org/wiki/Pi#Rate_of_convergence  |
// Stop case for iterating is when the difference after n + 1 digits == 0          |
// This is only actually truly accurate up to 7 digits, then it diverges from pi   |
// I avoid infinite loops with to_string instead of more accurate comparisons      |
//---------------------------------------------------------------------------------+
double pi(int n);
