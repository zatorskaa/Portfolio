#ifndef ROOT_H
#define ROOT_H

#include <cmath>
#include <iostream>

static double SquareRoot(double _x) //function to get square root of x
{
    double result = std::sqrt(_x);
    std::cout << result << std::endl;
    return result;
}

static double CubeRoot(double _x) //function to get cube root of x
{
    double result =  std::cbrt(_x);
    std::cout << result << std::endl;
    return result;
}

#endif