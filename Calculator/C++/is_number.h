#ifndef IS_NUMBER_H
#define IS_NUMBER_H

#include <typeinfo>
#include <string>
#include <stdexcept>
#include <cctype>

static bool IsNumber(std::string _userInput)
{
	try
	{
		double x = std::stod(_userInput); //check if user input can be converted into a number
		return true; //if input is a number return true
	}
	catch (const std::invalid_argument)
	{
		return false; //if input is not a number return false
	}
}


static bool IsInt(std::string _userInput)
{
	for (unsigned int i = 0; i < _userInput.size(); i++)
	{
		if(!std::isdigit(_userInput[i])) //check if each character is not a number
		{
			return false; //if it is not a number return false
		}
	}

	return true; //if all characters are numbers return true
}

#endif