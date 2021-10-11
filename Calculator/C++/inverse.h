#ifndef INVERSE_H
#define INVERSE_H

#include <iostream>

static double Inverse(double _x) //function to get inverse of x
{
    double result = 1 / _x;
    std::cout << result << std::endl;
    return result;
}

#endif