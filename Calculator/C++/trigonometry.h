#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H

#include <cmath>
#include <iostream>

static double Sin(double _angle) //function to get sin of an angle
{
    const double pi = std::acos(-1); //get value of pi
    double result;

    if (std::fmod(_angle, 180) == 0) //if angle is a multiple of 180 (fmod returns remainder)
    {
        result = 0;
    }
    else
    {
        _angle = (_angle * pi) / 180; //convert to radians
        result = std::sin(_angle);
    }

    std::cout << result << std::endl;
    return result;
}

static double Cos(double _angle) //function to get cos of a value
{
    const double pi = std::acos(-1); //get value of pi
    double result;

    if (std::fmod((_angle + 90), 180) == 0) //if angle is a multiple of 180 (fmod returns remainder)
    {
        result = 0;
    }
    else
    {
        _angle = (_angle * pi) / 180; //convert to radians
        result = std::cos(_angle);
    }

    std::cout << result << std::endl;
    return result;
}

#endif