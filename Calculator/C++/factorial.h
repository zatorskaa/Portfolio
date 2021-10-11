#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <iostream>

static double Factorial(int _x) //function to get factorial of x
{
    int result = 1;

    for (int i = _x; i > 0; i--)
    {
        result *= i;
    }

    std::cout << result << std::endl;
    return static_cast<double>(result);
}

#endif