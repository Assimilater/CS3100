#pragma once

//---------------------------------------------------------------------------------+
// double e                                                                        |
// Uses taylor expansion e^x = 1 + x/1! + x^2/2! + x^3/3! + ...                    |
// Re-written as e^x = 1 + (x/1)(1 + (x/2)(1 + (x/3)(...)))                        |
// I don't understand this math reduction, but it appears to work for x = 1:       |
// http://www.geeksforgeeks.org/program-to-efficiently-calculate-ex/               |
//---------------------------------------------------------------------------------+
double e(int n);
