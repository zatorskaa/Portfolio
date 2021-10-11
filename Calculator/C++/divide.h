#ifndef DIVIDE_H
#define DIVIDE_H

#include <iostream>

static double Divide(double _x, double _y) //function to divide 2 numbers
{
    double result = _x / _y;
    std::cout << result << std::endl;
    return result;
}


#endif