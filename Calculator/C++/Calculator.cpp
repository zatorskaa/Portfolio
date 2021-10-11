#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "multiply.h"
#include "divide.h"
#include "add.h"
#include "subtract.h"
#include "power.h"
#include "root.h"
#include "factorial.h"
#include "inverse.h"
#include "trigonometry.h"
#include "error.h"
#include "is_number.h"



int main()
{
#pragma region Variables
    //variables to store numbers from user input
    double x;
    double y;
    int z;

    //stores result from previous calculation for user to be able to use in next calculation
    double previousResult = 0;

    //stores values of pi and e
    const double pi = std::acos(-1);
    const double e = std::exp(1);

    //used as condition for while loop to check if user want to quit application
    bool quit = false;

    //stores user input
    std::string userInput;
    std::vector<std::string> userInputList = { "" };
    int numberOfWords = 0;
#pragma endregion




    while (!quit)
    {
#pragma region User Input
        //resets variables
        numberOfWords = 0;
        userInput = "";
        userInputList = { "" };

        std::cout << "Enter a calculation: " << std::endl; //tell user to enter a calculation
        std::getline(std::cin, userInput); //store user input

        for (char i : userInput) //for each character in user input
        {
            if (i != ' ') //check if character is not a whitespace
            {
                userInputList[numberOfWords] += std::tolower(i); //add that character to the current word in vector
            }
            else
            {
                numberOfWords++; //increase number of words if whitespace is found
                userInputList.push_back(""); //add a new element in vector to store next word
            }
        }
#pragma endregion




        if (userInputList.size() == 1) //checks if vector has one element
        {
            if (userInputList[0] == "quit") //checks if user wants to quit the application
            {
                quit = true; //sets bool to true to leave while loop
            }
            else if (userInputList[0] == "ac")
            {
                //resets previous result to 0
                previousResult = 0;
                std::cout << previousResult << std::endl;
            }
            else
            {
                InvalidInputError(); //returns error to user if they didn't input a valid calculation
            }
        }


        else if (userInputList.size() == 2)
        {
#pragma region  Square Root
            if (userInputList[0] == "sqrt") //square root check
            {
                if (userInputList[1] == "res") //previous result check
                {
                    if (previousResult >= 0) //check if previous result is not a negative number
                    {
                        previousResult = SquareRoot(previousResult); //call square root function with the previous result as the parameter, and set the return value as the new previous result
                    }
                    else
                    {
                        NegativeRootError(); //returns error to user if they tried to do a negative root
                    }
                }
                else if (userInputList[1] == "e") //e check
                {
                    previousResult = SquareRoot(e); //call square root function with e as the parameter, and set the return value as the new previous result
                }
                else if (userInputList[1] == "pi") //pi check
                {
                    previousResult = SquareRoot(pi); //call square root function with pi as the parameter, and set the return value as the new previous result
                }
                else if (IsNumber(userInputList[1])) //number check
                {
                    x = std::stod(userInputList[1]); //convert user input into a double

                    if (x >= 0) //if user input is not a negative number
                    {
                        previousResult = SquareRoot(x); //call square root function with user input as parameter, and set the return value as the new previous result
                    }
                    else
                    {
                        NegativeRootError(); //returns error to user if they tried to do a negative root
                    }
                }
                else
                {
                    InvalidInputError(); //returns error to user if they didn't input a number
                }
            }
#pragma endregion


#pragma region Cube Root
            else if (userInputList[0] == "cbrt") //square root check
            {
                if (userInputList[1] == "res") //previous result check
                {
                    previousResult = CubeRoot(previousResult);
                }
                else if (userInputList[1] == "e") //e check
                {
                    previousResult = CubeRoot(e); //call cube root function with e as the parameter, and set the return value as the new previous result
                }
                else if (userInputList[1] == "pi") //pi check
                {
                    previousResult = CubeRoot(pi); //call cube root function with pi as the parameter, and set the return value as the new previous result
                }
                else if (IsNumber(userInputList[1])) //number check
                {
                    x = std::stod(userInputList[1]); //convert user input into a double

                    previousResult = CubeRoot(x); //call cube root function with user input as parameter, and set the return value as the new previous result
                }
                else
                {
                    InvalidInputError(); //returns error to user if they didn't input a number
                }
            }
#pragma endregion


#pragma region Inverse
            else if (userInputList[0] == "inv") //inverse check
            {
                if (userInputList[1] == "res") //previous result check
                {
                    if (previousResult != 0) //check if previous result is not zero
                    {
                        previousResult = Inverse(previousResult); //call inverse function with the previous result as the parameter, and set the return value as the new previous result
                    }
                    else
                    {
                        ZeroDivisionError(); //returns error to user if they tried to divide by zero
                    }
                }
                else if (userInputList[1] == "e") //e check
                {
                    previousResult = Inverse(e); //call inverse function with e as the parameter, and set the return value as the new previous result
                }
                else if (userInputList[1] == "pi") //pi check
                {
                    previousResult = Inverse(pi); //call inverse function with pi as the parameter, and set the return value as the new previous result
                }
                else if (IsNumber(userInputList[1])) //number check
                {
                    x = std::stod(userInputList[1]); //convert user input into a double

                    if (x != 0) //if user input is not zero
                    {
                        previousResult = Inverse(x); //call inverse function with user input as parameter, and set the return value as the new previous result
                    }
                    else
                    {
                        ZeroDivisionError(); //returns error to user if they tried to divide by zero
                    }
                }
                else
                {
                    InvalidInputError(); //returns error to user if they didn't input a number
                }
            }
#pragma endregion


#pragma region Sin
            else if (userInputList[0] == "sin") //sin check
            {
                if (userInputList[1] == "res") //previous result check
                {
                    previousResult = Sin(previousResult); //call sin function with the previous result as the parameter, and set the return value as the new previous result
                }
                else if (userInputList[1] == "e") //e check
                {
                    previousResult = Sin(e); //call sin function with e as the parameter, and set the return value as the new previous result
                }
                else if (userInputList[1] == "pi") //pi check
                {
                    previousResult = Sin(pi); //call sin function with pi as the parameter, and set the return value as the new previous result
                }
                else if (IsNumber(userInputList[1])) //number check
                {
                    x = std::stod(userInputList[1]); //convert user input into a double

                    previousResult = Sin(x); //call sin function with user input as parameter, and set the return value as the new previous result
                }
                else
                {
                    InvalidInputError(); //returns error to user if they didn't input a number
                }
            }
#pragma endregion


#pragma region Cos
            else if (userInputList[0] == "cos") //cos check
            {
                if (userInputList[1] == "res") //previous result check
                {
                    previousResult = Cos(previousResult); //call cos function with the previous result as the parameter, and set the return value as the new previous result
                }
                else if (userInputList[1] == "e") //e check
                {
                    previousResult = Cos(e); //call cos function with e as the parameter, and set the return value as the new previous result
                }
                else if (userInputList[1] == "pi") //pi check
                {
                    previousResult = Cos(pi); //call cos function with pi as the parameter, and set the return value as the new previous result
                }
                else if (IsNumber(userInputList[1])) //number check
                {
                    x = std::stod(userInputList[1]); //convert user input into a double

                    previousResult = Cos(x); //call cos function with user input as parameter, and set the return value as the new previous result
                }
                else
                {
                    InvalidInputError(); //returns error to user if they didn't input a number
                }
            }
#pragma endregion


#pragma region Factorial
            else if (userInputList[1] == "!") //factorial check
            {
                if (userInputList[0] == "res") //previous result check
                {
                    if (previousResult > 0 && IsInt(std::to_string(previousResult))) //check if previous result is a positive integer
                    {
                        z = static_cast<int>(previousResult); //convert previous result to integer

                        previousResult = Factorial(z); //call factorial function with the previous result as the parameter, and set the return value as the new previous result
                    }
                    else
                    {
                        FactorialError(); //returns error to user if they tried to input a negative or non-integer number
                    }
                }
                else if (IsNumber(userInputList[0])) //number check
                {
                    if (IsInt(userInputList[0])) //call function to check if user input is an integer
                    {
                        z = std::stoi(userInputList[0]); //convert user input into an int

                        previousResult = Factorial(z); //call factorial function with user input as parameter, and set the return value as the new previous result
                    }
                    else
                    {
                        FactorialError(); //returns error to user if they tried to input a negative or non-integer number
                    }
                }
                else
                {
                    InvalidInputError(); //return error to user if they didn't input a valid operator or number
                }
            }
#pragma endregion


            else
            {
                InvalidInputError(); //return error to user if they didn't input a valid operator or number
            }
        }


        else if (userInputList.size() == 3)
        {
#pragma region Add
            if (userInputList[1] == "+") //add check
            {
                if (userInputList[0] == "res") //previous result check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Add(previousResult, previousResult); //call add function with previous result and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Add(previousResult, e); //call add function with previous result and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Add(previousResult, pi); //call add function with previous result and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Add(previousResult, y); //call add function with previous result and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "e") //e check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Add(e, previousResult); //call add function with e and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Add(e, e); //call add function with e and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Add(e, pi); //call add function with e and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Add(e, y); //call add function with e and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "pi") //pi check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Add(pi, previousResult); //call add function with pi and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Add(pi, e); //call add function with pi and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Add(pi, pi); //call add function with pi and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Add(pi, y); //call add function with pi and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (IsNumber(userInputList[0])) //number check
                {
                    x = std::stod(userInputList[0]); //convert user input to double

                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Add(x, previousResult); //call add function with x variable and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Add(x, e); //call add function with x variable and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Add(x, pi); //call add function with x variable and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Add(x, y); //call add function with x variable and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else
                {
                    InvalidInputError(); //return error to user if they didn't input a valid operator or number
                }
            }
#pragma endregion



#pragma region Subtract
            else if (userInputList[1] == "-") //subtract check
            {
                if (userInputList[0] == "res") //previous result check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Subtract(previousResult, previousResult); //call subtract function with previous result and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Subtract(previousResult, e); //call Subtract function with previous result and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Subtract(previousResult, pi); //call Subtract function with previous result and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Subtract(previousResult, y); //call Subtract function with previous result and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "e") //e check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Subtract(e, previousResult); //call Subtract function with e and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Subtract(e, e); //call Subtract function with e and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Subtract(e, pi); //call Subtract function with e and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Subtract(e, y); //call Subtract function with e and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "pi") //pi check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Subtract(pi, previousResult); //call Subtract function with pi and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Subtract(pi, e); //call Subtract function with pi and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Subtract(pi, pi); //call Subtract function with pi and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Subtract(pi, y); //call Subtract function with pi and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (IsNumber(userInputList[0])) //number check
                {
                    x = std::stod(userInputList[0]); //convert user input to double

                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Subtract(x, previousResult); //call Subtract function with x variable and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Subtract(x, e); //call Subtract function with x variable and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Subtract(x, pi); //call Subtract function with x variable and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Subtract(x, y); //call Subtract function with x variable and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else
                {
                    InvalidInputError(); //return error to user if they didn't input a valid operator or number
                }
            }
#pragma endregion



#pragma region Multiply
            else if (userInputList[1] == "*") //multiply check
            {
                if (userInputList[0] == "res") //previous result check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Multiply(previousResult, previousResult); //call Multiply function with previous result and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Multiply(previousResult, e); //call Multiply function with previous result and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Multiply(previousResult, pi); //call Multiply function with previous result and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Multiply(previousResult, y); //call Multiply function with previous result and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "e") //e check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Multiply(e, previousResult); //call Multiply function with e and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Multiply(e, e); //call Multiply function with e and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Multiply(e, pi); //call Multiply function with e and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Multiply(e, y); //call Multiply function with e and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "pi") //pi check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Multiply(pi, previousResult); //call Multiply function with pi and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Multiply(pi, e); //call Multiply function with pi and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Multiply(pi, pi); //call Multiply function with pi and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Multiply(pi, y); //call Multiply function with pi and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (IsNumber(userInputList[0])) //number check
                {
                    x = std::stod(userInputList[0]); //convert user input to double

                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = Multiply(x, previousResult); //call Multiply function with x variable and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Multiply(x, e); //call Multiply function with x variable and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Multiply(x, pi); //call Multiply function with x variable and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = Multiply(x, y); //call Multiply function with x variable and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else
                {
                    InvalidInputError(); //return error to user if they didn't input a valid operator or number
                }
            }
#pragma endregion



#pragma region Divide
            else if (userInputList[1] == "/") //divide check
            {
                if (userInputList[0] == "res") //previous result check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        if (previousResult != 0)
                        {
                            previousResult = Divide(previousResult, previousResult); //call Divide function with previous result and previous result as parameters
                        }
                        else
                        {
                            ZeroDivisionError();
                        }
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Divide(previousResult, e); //call Divide function with previous result and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Divide(previousResult, pi); //call Divide function with previous result and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        if (y != 0)
                        {
                            previousResult = Divide(previousResult, y); //call Divide function with previous result and y variable as parameters
                        }
                        else
                        {
                            ZeroDivisionError();
                        }
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "e") //e check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        if (previousResult != 0)
                        {
                            previousResult = Divide(e, previousResult); //call Divide function with e and previous result as parameters
                        }
                        else
                        {
                            ZeroDivisionError();
                        }
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Divide(e, e); //call Divide function with e and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Divide(e, pi); //call Divide function with e and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        if (y != 0)
                        {
                            previousResult = Divide(e, y); //call Divide function with e and y variable as parameters
                        }
                        else
                        {
                            ZeroDivisionError();
                        }
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "pi") //pi check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        if (previousResult != 0)
                        {
                            previousResult = Divide(pi, previousResult); //call Divide function with pi and previous result as parameters
                        }
                        else
                        {
                            ZeroDivisionError();
                        }
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Divide(pi, e); //call Divide function with pi and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Divide(pi, pi); //call Divide function with pi and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        if (y != 0)
                        {
                            previousResult = Divide(pi, y); //call Divide function with pi and y variable as parameters
                        }
                        else
                        {
                            ZeroDivisionError();
                        }
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (IsNumber(userInputList[0])) //number check
                {
                    x = std::stod(userInputList[0]); //convert user input to double

                    if (userInputList[2] == "res") //previous result check
                    {
                        if (previousResult != 0)
                        {
                            previousResult = Divide(x, previousResult); //call Divide function with x variable and previous result as parameters
                        }
                        else
                        {
                            ZeroDivisionError();
                        }
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = Divide(x, e); //call Divide function with x variable and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = Divide(x, pi); //call Divide function with x variable and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        if (y != 0)
                        {
                            previousResult = Divide(x, y); //call Divide function with x variable and y variable as parameters
                        }
                        else
                        {
                            ZeroDivisionError();
                        }
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else
                {
                    InvalidInputError(); //return error to user if they didn't input a valid operator or number
                }
            }
#pragma endregion



#pragma region Raise to Power
            else if (userInputList[1] == "^") //power check
            {
                if (userInputList[0] == "res") //previous result check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = RaiseToPower(previousResult, previousResult); //call RaiseToPower function with previous result and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = RaiseToPower(previousResult, e); //call RaiseToPower function with previous result and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = RaiseToPower(previousResult, pi); //call RaiseToPower function with previous result and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = RaiseToPower(previousResult, y); //call RaiseToPower function with previous result and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "e") //e check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = RaiseToPower(e, previousResult); //call RaiseToPower function with e and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = RaiseToPower(e, e); //call RaiseToPower function with e and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = RaiseToPower(e, pi); //call RaiseToPower function with e and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = RaiseToPower(e, y); //call RaiseToPower function with e and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (userInputList[0] == "pi") //pi check
                {
                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = RaiseToPower(pi, previousResult); //call RaiseToPower function with pi and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = RaiseToPower(pi, e); //call RaiseToPower function with pi and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = RaiseToPower(pi, pi); //call RaiseToPower function with pi and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = RaiseToPower(pi, y); //call RaiseToPower function with pi and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else if (IsNumber(userInputList[0])) //number check
                {
                    x = std::stod(userInputList[0]); //convert user input to double

                    if (userInputList[2] == "res") //previous result check
                    {
                        previousResult = RaiseToPower(x, previousResult); //call RaiseToPower function with x variable and previous result as parameters
                    }
                    else if (userInputList[2] == "e") //e check
                    {
                        previousResult = RaiseToPower(x, e); //call RaiseToPower function with x variable and e as parameters
                    }
                    else if (userInputList[2] == "pi") //pi check
                    {
                        previousResult = RaiseToPower(x, pi); //call RaiseToPower function with x variable and pi as parameters
                    }
                    else if (IsNumber(userInputList[2])) //number check
                    {
                        y = std::stod(userInputList[2]); //convert user input to double

                        previousResult = RaiseToPower(x, y); //call RaiseToPower function with x variable and y variable as parameters
                    }
                    else
                    {
                        InvalidInputError(); //return error to user if they didn't input a valid operator or number
                    }
                }

                else
                {
                    InvalidInputError(); //return error to user if they didn't input a valid operator or number
                }
            }
#pragma endregion

            else
            {
                InvalidInputError(); //returns error to user if they didn't input a valid calculation
            }
        }

        else
        {
            InvalidInputError(); //return error to user if they didn't input a valid operator or number
        }
    }



    if (quit)
    {
        std::cout << "Exiting Application...";
    }


    return 0;
}
