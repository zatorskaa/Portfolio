#ifndef MULTIPLY_H
#define MULTIPLY_H

#include <iostream>

static double Multiply(double _x, double _y) //function to multiply 2 numbers
{
    double result =  _x * _y;
    std::cout << result << std::endl;
    return result;
}

#endif