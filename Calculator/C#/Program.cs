using System;
using System.Linq;

namespace Calculator
{
    class Program
    {
        static void Main(string[] args)
        {
            #region Variables
            //variables used to store numbers from user input converted to floats or integers
            float x;
            float y;
            int z;

            //stores result of previous calculation for user to be able to use in next calculation
            float previousResult = 0f;

            //stores values of pi and e
            float pi = (float)Math.PI;
            float e = (float)Math.E;

            //used as condition for while loop to check if user wants to quit application
            bool quit = false;
            #endregion

            while (!quit)
            {
                #region User Input
                Console.WriteLine("Enter a calculation:");
                string userInput = Console.ReadLine(); //lets user enter a calculation
                string[] inputList = userInput.Split(' '); //splits user input into an array of strings where each element is a number or function input by the user
                #endregion


                if (inputList.Length == 1) //checks if array has one element
                {
                    if (inputList[0].ToLower() == "quit") //checks if user wants to quit application
                    {
                        quit = true; //sets bool to true so program leaves while loop
                    }
                    else if(inputList[0].ToLower() == "ac")
                    {
                        //resets result and previous result to 0
                        previousResult = 0;
                        Console.WriteLine(previousResult);
                    }
                    else
                    {
                        Console.WriteLine("Error: Invalid operation or number input"); //return error to user
                    }
                }
                else if (inputList.Length == 2) //checks if array has two elements
                {
                    switch (inputList[0].ToLower()) //checks if first element of array is a function
                    {
                        #region Square Root Check
                        case "root": //square root check
                            switch (inputList[1].ToLower()) //checks if second element of array is a number, e, pi or previous result
                            {
                                #region Previous Result Check
                                case "res": //checks if use wants to use previous result
                                    if(previousResult > -1) //checks if previous result is not a negative number
                                    {
                                        previousResult = SquareRoot(previousResult); //call square root function & sets previous result to result for next calculation
                                    }
                                    else
                                    {
                                        Console.WriteLine("Math Error: Negative root"); //returns error to user
                                    }
                                    break;
                                #endregion

                                #region e Check
                                case "e": //checks if use wants to use e
                                    previousResult = SquareRoot(e); //call square root function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region pi Check
                                case "pi": //checks if use wants to use pi
                                    previousResult = SquareRoot(pi); //call square root function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region Float Check
                                default:
                                    if (IsFloat(inputList[1])) //call function to check if user input is a float
                                    {
                                        x = (float)Convert.ToDouble(inputList[1]);

                                        if (x > -1) //checks if user input is not a negative number
                                        {
                                            previousResult = SquareRoot(x); //call square root function & sets previous result to result for next calculation
                                        }
                                        else
                                        {
                                            Console.WriteLine("Math Error: Negative root"); //returns error to user
                                        }
                                    }
                                    else
                                    {
                                        Console.WriteLine("Error: Invalid number input"); //returns error to user
                                    }
                                    break;
                                    #endregion
                            }
                            break;
                        #endregion

                        #region Inverse Check
                        case "inv": //inverse check
                            switch (inputList[1].ToLower()) //checks if second element of array is a number, e, pi or previous result
                            {
                                #region Previous Result Check
                                case "res": //checks if use wants to use previous result
                                    if (previousResult != 0) //checks if previous result is not 0
                                    {
                                        previousResult = Inverse(previousResult); //call inverse function & sets previous result to result for next calculation
                                    }
                                    else
                                    {
                                        Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                    }
                                    break;
                                #endregion

                                #region e Check
                                case "e": //checks if use wants to use e
                                    previousResult = Inverse(e); //call inverse function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region pi Check
                                case "pi": //checks if use wants to use pi
                                    previousResult = Inverse(pi); //call inverse function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region Float Check
                                default:
                                    if (IsFloat(inputList[1])) //call function to check if user input is a float
                                    {
                                        x = (float)Convert.ToDouble(inputList[1]);

                                        if(x != 0) //checks if user input is not 0
                                        {
                                            previousResult = Inverse(x); //call inverse function & sets previous result to result for next calculation
                                        }
                                        else
                                        {
                                            Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                        }

                                    }
                                    else
                                    {
                                        Console.WriteLine("Error: Invalid number input"); //return error to user
                                    }
                                    break;
                                #endregion
                            }
                            break;
                        #endregion

                        #region Sin Check
                        case "sin": //sin chack
                            switch (inputList[1].ToLower()) //checks if second element of array is a number, e, pi or previous result
                            {
                                #region Previous Result Check
                                case "res": //checks if use wants to use previous result
                                    previousResult = Sin(previousResult); //call sin function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region e Check
                                case "e": //checks if use wants to use e
                                    previousResult = Sin(e); //call sin function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region pi Check
                                case "pi": //checks if use wants to use pi
                                    previousResult = Sin(pi); //call sin function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region Float Check
                                default:
                                    if (IsFloat(inputList[1])) //call function to check if user input is a float
                                    {
                                        x = (float)Convert.ToDouble(inputList[1]);

                                        previousResult = Sin(x); //call sin function & sets previous result to result for next calculation
                                    }
                                    else
                                    {
                                        Console.WriteLine("Error: Invalid number input"); //returns error to user
                                    }
                                    break;
                                #endregion
                            }
                            break;
                        #endregion

                        #region Cos Check
                        case "cos": //cos check
                            switch (inputList[1].ToLower()) //checks if second element of array is a number, e, pi or previous result
                            {
                                #region Previous Result Check
                                case "res": //checks if use wants to use previous result
                                    previousResult = Cos(previousResult); //call cos function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region e Check
                                case "e": //checks if use wants to use e
                                    previousResult = Cos(e); //call cos function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region pi Check
                                case "pi": //checks if use wants to use pi
                                    previousResult = Cos(pi); //call cos function & sets previous result to result for next calculation
                                    break;
                                #endregion

                                #region Float Check
                                default:
                                    if (IsFloat(inputList[1])) //call function to check if user input is a float
                                    {
                                        x = (float)Convert.ToDouble(inputList[1]);

                                        previousResult = Cos(x); //call cos function & sets previous result to result for next calculation
                                    }
                                    else
                                    {
                                        Console.WriteLine("Error: Invalid number input"); //returns error to user
                                    }
                                    break;
                                #endregion
                            }
                            break;
                        #endregion

                        default:
                            #region Factorial Check
                            if (inputList[1] == "!") //checks if second element in array is the factorial function
                            {
                                if (inputList[0].ToLower() == "res") //checks if user wants to use previous calculation result
                                {
                                    if (previousResult > 0 && !previousResult.ToString().Contains('.')) //checks if number is greater than 0 and is an integer
                                    {
                                        z = Convert.ToInt32(previousResult); //converts previous result to integer type

                                        previousResult = Factorial(z); //calls factorial function & sets previous result to result for next calculation
                                    }
                                    else
                                    {
                                        Console.WriteLine("Math Error: Non-Integer or Negative Factorial"); //returns error to user
                                    }
                                }
                                else if (inputList[0].All(char.IsDigit)) //checks if number is a positive integer
                                {
                                    z = Convert.ToInt32(inputList[0]); //converts number input to integer type

                                    previousResult = Factorial(z); //calls factorial function & sets previous result to result for next calculation
                                }
                                else
                                {
                                    Console.WriteLine("Math Error: Non-Integer or Negative Factorial"); //returns error to user
                                }
                            }
                            #endregion
                            else
                            {
                                Console.WriteLine("Error: Invalid operation or number input"); //resturn error to user
                            }

                            break;
                    }
                }
                else if (inputList.Length == 3)
                {
                    switch (inputList[1]) //checks what function the second element in the array is
                    {
                        #region Add Check
                        case "+": //add check
                            switch (inputList[0].ToLower())  //checks if first element of array is a number, e, pi or previous result
                            {
                                #region Previous Result Check
                                case "res": //checks if use wants to use previous result
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if use wants to use previous result
                                            previousResult = Add(previousResult, previousResult); //calls add function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if use wants to use e
                                            previousResult = Add(previousResult, e); //calls add function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if use wants to use pi
                                            previousResult = Add(previousResult, pi); //calls add function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = Add(previousResult, y); //calls add function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                        #endregion
                                    }
                                    break;
                                #endregion

                                #region e Check
                                case "e": //checks if use wants to use e
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if use wants to use previous result
                                            previousResult = Add(e, previousResult); //calls add function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if use wants to use e
                                            previousResult = Add(e, e); //calls add function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if use wants to use pi
                                            previousResult = Add(e, pi); //calls add function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = Add(e, y); //calls add function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                        #endregion
                                    }
                                    break;
                                #endregion

                                #region pi Check
                                case "pi":
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if use wants to use previous result
                                            previousResult = Add(pi, previousResult); //calls add function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if use wants to use e
                                            previousResult = Add(pi, e); //calls add function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if use wants to use pi
                                            previousResult = Add(pi, pi); //calls add function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = Add(pi, y); //calls add function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                        #endregion
                                    }
                                    break;
                                #endregion

                                #region Float Check
                                default:
                                    if (IsFloat(inputList[0]))
                                    {
                                        x = (float)Convert.ToDouble(inputList[0]); //converts user input to float

                                        switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                        {
                                            #region Previous Result Check
                                            case "res": //checks if use wants to use previous result
                                                previousResult = Add(x, previousResult); //calls add function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region e Check
                                            case "e": //checks if use wants to use e
                                                previousResult = Add(x, e); //calls add function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region pi Check
                                            case "pi": //checks if use wants to use pi
                                                previousResult = Add(x, pi); //calls add function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region Float Check
                                            default:
                                                if (IsFloat(inputList[2])) //checks if user input is a float
                                                {
                                                    y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                    previousResult = Add(x, y); //calls add function & sets previous result to result for next calculation
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Error: Invalid number input"); //return error to user
                                                }
                                                break;
                                            #endregion
                                        }
                                    }
                                    else
                                    {
                                        Console.WriteLine("Error: Invalid number input"); //return error to user
                                    }
                                    break;
                                #endregion
                            }
                            break;
                        #endregion

                        #region Subtract Check
                        case "-": //subtract check
                            switch (inputList[0].ToLower())  //checks if first element of array is a number, e, pi or previous result
                            {
                                #region Previous Result Check
                                case "res": //checks if use wants to use previous result
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if use wants to use previous result
                                            previousResult = Subtract(previousResult, previousResult); //calls subtract function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if use wants to use e
                                            previousResult = Subtract(previousResult, e); //calls subtract function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if use wants to use pi
                                            previousResult = Subtract(previousResult, pi); //calls subtract function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = Subtract(previousResult, y); //calls subtract function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region e Check
                                case "e": //checks if use wants to use e
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if use wants to use previous result
                                            previousResult = Subtract(e, previousResult); //calls subtract function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if use wants to use e
                                            previousResult = Subtract(e, e); //calls subtract function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if use wants to use pi
                                            previousResult = Subtract(e, pi); //calls subtract function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = Subtract(e, y); //calls subtract function
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region pi Check
                                case "pi":
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if use wants to use previous result
                                            previousResult = Subtract(pi, previousResult); //calls subtract function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if use wants to use e
                                            previousResult = Subtract(pi, e); //calls subtract function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if use wants to use pi
                                            previousResult = Subtract(pi, pi); //calls subtract function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = Subtract(pi, y); //calls subtract function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region Float Check
                                default:
                                    if (IsFloat(inputList[0]))
                                    {
                                        x = (float)Convert.ToDouble(inputList[0]); //converts user input to float

                                        switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                        {
                                            #region Previous Result Check
                                            case "res": //checks if use wants to use previous result
                                                previousResult = Subtract(x, previousResult); //calls subtract function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region e Check
                                            case "e": //checks if use wants to use e
                                                previousResult = Subtract(x, e); //calls subtract function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region pi Check
                                            case "pi": //checks if use wants to use pi
                                                previousResult = Subtract(x, pi); //calls subtract function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region Float Check
                                            default:
                                                if (IsFloat(inputList[2])) //checks if user input is a float
                                                {
                                                    y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                    previousResult = Subtract(x, y); //calls subtract function & sets previous result to result for next calculation
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Error: Invalid number input"); //return error to user
                                                }
                                                break;
                                                #endregion
                                        }
                                    }
                                    else
                                    {
                                        Console.WriteLine("Error: Invalid number input"); //return error to user
                                    }
                                    break;
                                    #endregion
                            }
                            break;
                        #endregion

                        #region Multiply Check
                        case "*": //multiply check
                            switch (inputList[0].ToLower()) //checks if first element of array is a number, e, pi or previous result
                            {
                                #region Previous Result Check
                                case "res": //checks if user wants to use previous result
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if user wants to use previous result
                                            previousResult = Multiply(previousResult, previousResult); //calls multiply function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if user wants to use e
                                            previousResult = Multiply(previousResult, e); //calls multiply function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if user wants to use pi
                                            previousResult = Multiply(previousResult, pi); //calls multiply function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = Multiply(previousResult, y); //calls multiply function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region e Check
                                case "e": //checks if user wants to use e
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if user wants to use previous result
                                            previousResult = Multiply(e, previousResult); //calls multiply function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if user wants to use e
                                            previousResult = Multiply(e, e); //calls multiply function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if user wants to use pi
                                            previousResult = Multiply(e, pi); //calls multiply function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = Multiply(e, y); //calls multiply function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region pi Check
                                case "pi":
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if user wants to use previous result
                                            previousResult = Multiply(pi, previousResult); //calls multiply function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if user wants to use e
                                            previousResult = Multiply(pi, e); //calls multiply function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if user wants to use pi
                                            previousResult = Multiply(pi, pi); //calls multiply function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = Multiply(pi, y); //calls multiply function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region Float Check
                                default:
                                    if (IsFloat(inputList[0]))
                                    {
                                        x = (float)Convert.ToDouble(inputList[0]); //converts user input to float

                                        switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                        {
                                            #region Previous Result Check
                                            case "res": //checks if user wants to use previous result
                                                previousResult = Multiply(x, previousResult); //calls multiply function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region e Check
                                            case "e": //checks if user wants to use e
                                                previousResult = Multiply(x, e); //calls multiply function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region pi Check
                                            case "pi": //checks if user wants to use pi
                                                previousResult = Multiply(x, pi); //calls multiply function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region Float Check
                                            default:
                                                if (IsFloat(inputList[2])) //checks if user input is a float
                                                {
                                                    y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                    previousResult = Multiply(x, y); //calls multiply function & sets previous result to result for next calculation
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Error: Invalid number input"); //return error to user
                                                }
                                                break;
                                                #endregion
                                        }
                                    }
                                    else
                                    {
                                        Console.WriteLine("Error: Invalid number input"); //return error to user
                                    }
                                    break;
                                    #endregion
                            }
                            break;
                        #endregion

                        #region Divide Check
                        case "/":
                            switch (inputList[0].ToLower()) //checks if first element of array is a number, e, pi or previous result
                            {
                                #region Previous Result Check
                                case "res": //checks if use wants to use previous result
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if use wants to use previous result
                                            if(previousResult != 0) //checks if previous result is not 0
                                            {
                                                previousResult = Divide(previousResult, previousResult); //calls divide function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                            }
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if use wants to use e
                                            previousResult = Divide(previousResult, e); //calls divide function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if use wants to use pi
                                            previousResult = Divide(previousResult, pi); //calls divide function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                if(y != 0)
                                                {
                                                    previousResult = Divide(previousResult, y); //calls divide function & sets previous result to result for next calculation
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                                }
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region e Check
                                case "e": //checks if use wants to use e
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if use wants to use previous result
                                            if (previousResult != 0) //checks if previous result is not 0
                                            {
                                                previousResult = Divide(e, previousResult); //calls divide function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                            }
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if use wants to use e
                                            previousResult = Divide(e, e); //calls divide function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if use wants to use pi
                                            previousResult = Divide(e, pi); //calls divide function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                if (y != 0)
                                                {
                                                    previousResult = Divide(e, y); //calls divide function & sets previous result to result for next calculation
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                                }
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region pi Check
                                case "pi": //checks if user wants to use pi
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if user wants to use previous result
                                            if (previousResult != 0) //checks if previous result is not 0
                                            {
                                                previousResult = Divide(pi, previousResult); //calls divide function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                            }
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if user wants to use e
                                            previousResult = Divide(pi, e); //calls divide function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if user wants to use pi
                                            previousResult = Divide(pi, pi); //calls divide function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                if (y != 0)
                                                {
                                                    previousResult = Divide(pi, y); //calls divide function & sets previous result to result for next calculation
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                                }
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region Float Check
                                default:
                                    if (IsFloat(inputList[0]))
                                    {
                                        x = (float)Convert.ToDouble(inputList[0]); //converts user input to float

                                        switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                        {
                                            #region Previous Result Check
                                            case "res": //checks if use wants to use previous result
                                                if (previousResult != 0) //checks if previous result is not 0
                                                {
                                                    previousResult = Divide(x, previousResult); //calls divide function & sets previous result to result for next calculation
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                                }
                                                break;
                                            #endregion

                                            #region e Check
                                            case "e": //checks if use wants to use e
                                                previousResult = Divide(x, e); //calls divide function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region pi Check
                                            case "pi": //checks if use wants to use pi
                                                previousResult = Divide(x, pi); //calls divide function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region Float Check
                                            default:
                                                if (IsFloat(inputList[2])) //checks if user input is a float
                                                {
                                                    y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                    if (y != 0)
                                                    {
                                                        previousResult = Divide(x, y); //calls divide function & sets previous result to result for next calculation
                                                    }
                                                    else
                                                    {
                                                        Console.WriteLine("Math Error: Zero Division"); //return error if user tries to divide by 0
                                                    }
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Error: Invalid number input"); //return error to user
                                                }
                                                break;
                                                #endregion
                                        }
                                    }
                                    else
                                    {
                                        Console.WriteLine("Error: Invalid number input"); //return error to user
                                    }
                                    break;
                                    #endregion
                            }
                            break;
                        #endregion

                        #region Power Check
                        case "^":
                            switch (inputList[0].ToLower()) //checks if first element of array is a number, e, pi or previous result
                            {
                                #region Previous Result Check
                                case "res": //checks if user wants to use previous result
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if user wants to use previous result
                                            previousResult = RaiseToPower(previousResult, previousResult); //calls power function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if user wants to use e
                                            previousResult = RaiseToPower(previousResult, e); //calls power function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if user wants to use pi
                                            previousResult = RaiseToPower(previousResult, pi); //calls power function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = RaiseToPower(previousResult, y); //calls power function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region e Check
                                case "e": //checks if user wants to use e
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if user wants to use previous result
                                            previousResult = RaiseToPower(e, previousResult); //calls power function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if user wants to use e
                                            previousResult = RaiseToPower(e, e); //calls power function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if user wants to use pi
                                            previousResult = RaiseToPower(e, pi); //calls power function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = RaiseToPower(e, y); //calls power function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region pi Check
                                case "pi":
                                    switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                    {
                                        #region Previous Result Check
                                        case "res": //checks if user wants to use previous result
                                            previousResult = RaiseToPower(pi, previousResult); //calls power function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region e Check
                                        case "e": //checks if user wants to use e
                                            previousResult = RaiseToPower(pi, e); //calls power function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region pi Check
                                        case "pi": //checks if user wants to use pi
                                            previousResult = RaiseToPower(pi, pi); //calls power function & sets previous result to result for next calculation
                                            break;
                                        #endregion

                                        #region Float Check
                                        default:
                                            if (IsFloat(inputList[2])) //checks if user input is a float
                                            {
                                                y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                previousResult = RaiseToPower(pi, y); //calls power function & sets previous result to result for next calculation
                                            }
                                            else
                                            {
                                                Console.WriteLine("Error: Invalid number input"); //return error to user
                                            }
                                            break;
                                            #endregion
                                    }
                                    break;
                                #endregion

                                #region Float Check
                                default:
                                    if (IsFloat(inputList[0]))
                                    {
                                        x = (float)Convert.ToDouble(inputList[0]); //converts user input to float

                                        switch (inputList[2].ToLower()) //checks if third element of array is a number, e, pi or previous result
                                        {
                                            #region Previous Result Check
                                            case "res": //checks if user wants to use previous result
                                                previousResult = RaiseToPower(x, previousResult); //calls power function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region e Check
                                            case "e": //checks if user wants to use e
                                                previousResult = RaiseToPower(x, e); //calls power function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region pi Check
                                            case "pi": //checks if user wants to use pi
                                                previousResult = RaiseToPower(x, pi); //calls power function & sets previous result to result for next calculation
                                                break;
                                            #endregion

                                            #region Float Check
                                            default:
                                                if (IsFloat(inputList[2])) //checks if user input is a float
                                                {
                                                    y = (float)Convert.ToDouble(inputList[2]); //converts user input to float

                                                    previousResult = RaiseToPower(x, y); //calls power function & sets previous result to result for next calculation
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Error: Invalid number input"); //return error to user
                                                }
                                                break;
                                                #endregion
                                        }
                                    }
                                    else
                                    {
                                        Console.WriteLine("Error: Invalid number input"); //return error to user
                                    }
                                    break;
                                    #endregion
                            }
                            break;
                        #endregion

                        default:
                            Console.WriteLine("Error: Invalid operation or number input");
                            break;
                    }
                }
                else
                {
                    Console.WriteLine("Error: Invalid operation or number input"); //return error to user
                }
            }


            if (quit)
            {
                Console.WriteLine("Exiting Application..."); //tells the user they have exit the application
            }
        }

        static float Add(float x, float y)
        {
            float result = x + y; //add two numbers
            Console.WriteLine(result); //returns result to user
            return result;
        }

        static float Subtract(float x, float y)
        {
            float result = x - y; //subtract two numbers
            Console.WriteLine(result); //returns result to user
            return result;
        }

        static float Multiply(float x, float y)
        {
            float result = x * y; //multiply two numbers
            Console.WriteLine(result); //returns result to user
            return result;
        }

        static float Divide(float x, float y)
        {
            float result = x / y; //divide two numbers
            Console.WriteLine(result); //returns result to user
            return result;
        }

        static float RaiseToPower(float x, float y)
        {
            double result = Math.Pow(Convert.ToDouble(x), Convert.ToDouble(y)); //do x to the power of y
            Console.WriteLine((float)result); //returns result to user
            return (float)result;
        }

        static float SquareRoot(float x)
        {
            double result = Math.Sqrt(Convert.ToDouble(x)); //do square root of x
            Console.WriteLine((float)result); //returns result to user
            return (float)result;
        }

        static float Factorial(int z)
        {
            int result = 1;


            for(int i = z; i > 0; i--)
            {
                result = result * i; //times i by i-1 times by i-2 ... until i=1
            }

            Console.WriteLine(result); //returns result to user
            return (float)Convert.ToDouble(result);
        }

        static float Inverse(float x)
        {
            float result = 1 / x; //divide 1 by x
            Console.WriteLine(result); //returns result to user
            return result;
        }

        static float Sin(float angleDegrees)
        {
            double result;

            if(angleDegrees % 180 == 0) //check if angle is a multiple of 180
            {
                result = 0; //if yes set result to 0
            }
            else
            {
                double angleRandians = Convert.ToDouble(angleDegrees) * Math.PI / 180; //convert angle input from degrees to radians
                result = Math.Sin(angleRandians); //do sin of x
            }

            Console.WriteLine((float)result); //returns result to user
            return (float)result;
        }

        static float Cos(float angleDegrees)
        {
            double result;

            if ((angleDegrees + 90) % 180 == 0) //check if angle is a multiple of 180
            {
                result = 0; //if yes set result to 0
            }
            else
            {
                double angleRandians = Convert.ToDouble(angleDegrees) * Math.PI / 180; //convert angle input from degrees to radians
                result = Math.Cos(angleRandians); //do sin of x
            }

            Console.WriteLine((float)result); //returns result to user
            return (float)result;
        }

        static bool IsFloat(string userInput)
        {
            try
            {
                float x = (float)Convert.ToDouble(userInput); //checks if user input can be converted to a float
                return true; //if yes return true
            }
            catch(Exception ex) when (ex is InvalidCastException || ex is FormatException)
            {
                return false; //if no return false
            }
        }
    }
}