#ifndef SUBTRACT_H
#define SUBTRACT_H

#include <iostream>

static double Subtract(double _x, double _y) //function to subtract 2 numbers
{
    double result = _x - _y;
    std::cout << result << std::endl;
    return result;
}


#endif