#ifndef POWER_H
#define POWER_H

#include <cmath>
#include <iostream>

static double RaiseToPower(double _x, double _y) //function to raise x to power of y
{
    double result =  std::pow(_x, _y);
    std::cout << result << std::endl;
    return result;
}

#endif