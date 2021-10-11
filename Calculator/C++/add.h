#ifndef ADD_H
#define ADD_H

#include <iostream>

static double Add(double _x, double _y) //function to add 2 numbers
{
    double result =  _x + _y;
    std::cout << result << std::endl;
    return result;
}


#endif