#ifndef ERROR_H
#define ERROR_H

#include <iostream>

//functions to show error messages to user

static void InvalidInputError()
{
    std::cout << "Error: Invalid operation or number input" << std::endl;
}

static void NegativeRootError()
{
    std::cout << "Math Error: Negative root" << std::endl;
}

static void ZeroDivisionError()
{
    std::cout << "Math Error: Zero division" << std::endl;
}

static void FactorialError()
{
    std::cout << "Math Error: Non-integer or negative factorial" << std::endl;
}

#endif