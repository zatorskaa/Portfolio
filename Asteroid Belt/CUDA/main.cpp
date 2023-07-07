#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>

#include "SFML/Graphics.hpp" //SFML version 2.5.1 Visual C++ 15 (2017) - 64-bit
#include "../Coursework/cuda.cuh"


//constants
const double AU = 1.496e+11;
const double pi = 3.141592653589793238462643;

//torus
const double torusMin = AU - (0.1 * AU); //minimum radius of torus (1.1AU)
const double torusMax = AU + (0.1 * AU); //maximum radius of torus (0.9AU)


//Asteroid Variables
const unsigned int numberOfAsteroids = 10000; //number of asteroids in simulation
const unsigned int cAsteroids = (numberOfAsteroids * 75) / 100; //number of C-type asteroids (75% of asteroids in asteroid belt)
const unsigned int sAsteroids = (numberOfAsteroids * 15) / 100; //number of S-type asteroids (15% of asteroids in asteroid belt)

double mass[numberOfAsteroids] = { 0 }; //array to store mass of each asteroid
double radius[numberOfAsteroids] = { 0 }; //array to store radius of each asteroid

//x-axis is left/right, y-axis is forward/backwards, z-axis is up/down
double xPos[numberOfAsteroids] = { 0 }; //array to store position of each asteroid on x axis
double yPos[numberOfAsteroids] = { 0 }; //array to store position of each asteroid on y axis
double zPos[numberOfAsteroids] = { 0 }; //array to store position of each asteroid on z axis

double xVel[numberOfAsteroids] = { 0 }; //array to store velocity of each asteroid on x axis
double yVel[numberOfAsteroids] = { 0 }; //array to store velocity of each asteroid on y axis
double zVel[numberOfAsteroids] = { 0 }; //array to store velocity of each asteroid on z axis

double distanceFromSun[numberOfAsteroids] = { 0 }; //array to store the distance away from the sun where each asteroid will start (between 0.9AU to 1.1AU radius of torus)
double angle[numberOfAsteroids] = { 0 }; //array to store the angle around the torus where each asteroid will start


const unsigned int cRadiusMin = 75000; //minimum radius value for c-type asteroids
const unsigned int cRadiusMax = 225000; //maximum radius value for c-type asteroids
const unsigned int cRadiusDif = cRadiusMax - cRadiusMin; //max radius value - min radius value for c-type asteroids (for random radius calculation)
const unsigned int sRadiusMin = 50000; //minimum radius value for s-type asteroids
const unsigned int sRadiusMax = 150000; //maximum radius value for s-type asteroids
const unsigned int sRadiusDif = sRadiusMax - sRadiusMin; //max radius value - min radius value for s-type asteroids (for random radius calculation)
const unsigned int mRadiusMin = 25000; //minimum radius value for m-type asteroids
const unsigned int mRadiusMax = 100000; //maximum radius value for m-type asteroids
const unsigned int mRadiusDif = mRadiusMax - mRadiusMin; //max radius value - min radius value for m-type asteroids (for random radius calculation)

const unsigned int cDensity = 1700; //density of c-type asteroids
const unsigned int sDensity = 3000; //density of s-type asteroids
const unsigned int mDensity = 6000; //density of m-type asteroids


//sfml
//can uncomment 4K window size for 4K monitors and comment out 1080p
sf::Vector2f windowSize = sf::Vector2f(1920, 1080); //1080p window size
//sf::Vector2f windowSize = sf::Vector2f(3840, 2160); //4K window size

sf::Vector2f center = sf::Vector2f(windowSize.x / 2, windowSize.y / 2); //center position of the window
//sfml circles for drawing asteroids and sun
sf::CircleShape circle;
sf::CircleShape circle2;
sf::CircleShape circle3;

//time
std::chrono::steady_clock::time_point start, end;
std::chrono::microseconds duration;


//functions
//calculate forces between asteroids and sun and calculate new positions
cudaError_t CalculatePosition(double* xPos, double* yPos, double* zPos, double* xVel, double* yVel, double* zVel, double* mass, unsigned int numberOfAsteroids);
//calculate the inital velocity that the asteroids start at
cudaError_t CalculateStartVelocity(double* xPos, double* yPos, double* zPos, double* xVel, double* yVel, double* zVel, unsigned int numberOfAsteroids);

void RandomRadiusC(); //generate radius and mass values for c-type asteroids
void RandomRadiusS(); //generate radius and mass values for s-type asteroids
void RandomRadiusM(); //generate radius and mass values for m-type asteroids
void RandomPosXY(); //generate x and y positions for each asteroid
void RandomPosZ(); //generate z positions for each asteroid


int main()
{
    //create window for drawing asteroids
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Asteroid Belt");
    window.setFramerateLimit(60);
    //seed for random values
    srand(9993961);

    //run each function for generating radius, mass and position values on a separate CPU thread
    start = std::chrono::high_resolution_clock::now();
    std::thread thread_A(RandomRadiusC);
    std::thread thread_B(RandomRadiusS);
    std::thread thread_C(RandomRadiusM);
    std::thread thread_D(RandomPosXY);
    std::thread thread_E(RandomPosZ);

    thread_A.join();
    thread_B.join();
    thread_C.join();
    thread_D.join();
    thread_E.join();

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Creating Asteroid Belt: " << duration.count() / 1000000.0f << " seconds" << std::endl << std::endl;


    start = std::chrono::high_resolution_clock::now();
    //call kernel to calculate start velocity of asteroids
    cudaError_t cudaStatus = CalculateStartVelocity(xPos, yPos, zPos, xVel, yVel, zVel, numberOfAsteroids);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Calculating Initial Velocity: " << duration.count() / 1000000.0f << " seconds" << std::endl << std::endl;

    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "addWithCuda failed!");
        return 1;
    }

    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }



    //while the sfml window is open
    while (window.isOpen())
    {
        //check if window has been closed
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }


        start = std::chrono::high_resolution_clock::now();

        //call kernel for each frame to update velocity and position of asteroids
        cudaError_t cudaStatus2 = CalculatePosition(xPos, yPos, zPos, xVel, yVel, zVel, mass, numberOfAsteroids);

        if (cudaStatus2 != cudaSuccess)
        {
            fprintf(stderr, "addWithCuda failed!");
            return 1;
        }

        cudaStatus2 = cudaDeviceReset();
        if (cudaStatus2 != cudaSuccess)
        {
            fprintf(stderr, "cudaDeviceReset failed!");
            return 1;
        }

        //render asteroids
        window.clear(); //clear the window for each frame

        //check which window size is being used
        if (windowSize == sf::Vector2f(3840, 2160)) //4K window size
        {
            for (int i = 0; i < numberOfAsteroids; i++)
            {
                //draw top-down view of asteroid belt
                circle.setPosition(center.x - 900 + (xPos[i] * 5e-9), center.y + (yPos[i] * 5e-9));
                circle.setRadius(radius[i] * 2e-5);
                window.draw(circle);

                //draw front view of asteroid belt
                circle2.setPosition(center.x + 900 + (xPos[i] * 5e-9), center.y + (zPos[i] * 5e-9));
                circle2.setRadius(radius[i] * 2e-5);
                window.draw(circle2);
            }

            //draw sun in center of asteroid belt for top-down view
            circle3.setPosition(center.x - 900, center.y);
            circle3.setRadius(6.96340e+5 * 2e-5);
            window.draw(circle3);
        }
        else //1080p window size
        {
            for (int i = 0; i < numberOfAsteroids; i++) 
            {
                //draw top-down view of asteroid belt
                circle.setPosition(center.x - 450 + (xPos[i] * 2.5e-9), center.y + (yPos[i] * 2.5e-9));
                circle.setRadius(radius[i] * 1e-5);
                window.draw(circle);

                //draw front view of asteroid belt
                circle2.setPosition(center.x + 450 + (xPos[i] * 2.5e-9), center.y + (zPos[i] * 2.5e-9));
                circle2.setRadius(radius[i] * 1e-5);
                window.draw(circle2);
            }

            //draw sun in center of asteroid belt for top-down view
            circle3.setPosition(center.x - 450, center.y);
            circle3.setRadius(6.96340e+5 * 1e-5);
            window.draw(circle3);
        }


        window.display();

        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Moving Asteroids: " << duration.count() / 1000000.0f << " seconds" << std::endl;
    }

    return 0;
}




void RandomRadiusC()
{
    //c type asteroids
    for (int i = 0; i < cAsteroids; i++)
    {
        /*
        generate random radius in meters
        generate random number from 0 to the (max-min radius value) then add the minimum radius value
        */
        radius[i] = (rand() % (cRadiusDif)) + cRadiusMin; 

        /*
        calculate mass in kg
        mass = density * volume
        volume of sphere = 4/3 * pi * r^3
        mass = density * 4/3 * pi * radius^3
        */
        mass[i] = cDensity * (4.0 / 3.0) * pi * radius[i] * radius[i] * radius[i];


        //std::cout << radius[i] << std::endl;
        //std::cout << mass[i] << std::endl;
    }
}

void RandomRadiusS()
{
    //s type asteroids
    for (int i = cAsteroids; i < cAsteroids + sAsteroids; i++)
    {
        /*
        generate random radius in meters
        generate random number from 0 to the (max-min radius value) then add the minimum radius value
        */
        radius[i] = (rand() % sRadiusDif) + sRadiusMin;

        /*
        calculate mass in kg
        mass = density * volume
        volume of sphere = 4/3 * pi * r^3
        mass = density * 4/3 * pi * radius^3
        */
        mass[i] = sDensity * (4.0 / 3.0) * pi * radius[i] * radius[i] * radius[i];

        //std::cout << radius[i] << std::endl;
        //std::cout << mass[i] << std::endl;
    }
}

void RandomRadiusM()
{
    //m type asteroids
    for (int i = cAsteroids + sAsteroids; i < numberOfAsteroids; i++)
    {
        /*
        generate random radius in meters
        generate random number from 0 to the (max-min radius value) then add the minimum radius value
        */
        radius[i] = (rand() % mRadiusDif) + mRadiusMin;

        /*
        calculate mass in kg
        mass = density * volume
        volume of sphere = 4/3 * pi * r^3
        mass = density * 4/3 * pi * radius^3
        */
        mass[i] = mDensity * (4.0 / 3.0) * pi * radius[i] * radius[i] * radius[i];

        //std::cout << radius[i] << std::endl;
        //std::cout << mass[i] << std::endl;
    }
}


void RandomPosXY()
{
    for (int i = 0; i < numberOfAsteroids; i++)
    {
        //generate random distance from the sun between torus limits (between 0.9 to 1.1 AU) in meters
        //                   lower limit                                                                  higher - lower limit
        distanceFromSun[i] = torusMin + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (torusMax - torusMin)));
        //generate random angle in radians between 0 to 2*pi
        angle[i] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (2 * pi)));

        //calculate x and y positions of asteroid based on the radius and angle values
        //x = r * cos(a), y = r * sin(a)
        xPos[i] = distanceFromSun[i] * cos(angle[i]);
        yPos[i] = distanceFromSun[i] * sin(angle[i]);


        //std::cout << distanceFromSun[i] << std::endl;
        //std::cout << angle[i] << std::endl;
        //std::cout << xPos[i] << std::endl;
        //std::cout << yPos[i] << std::endl;
    }

}

void RandomPosZ()
{
    for (int i = 0; i < numberOfAsteroids; i++)
    {
        /*
        calculate the min/max z position that the asteroid can have based on its x and y values
        first find the center point of the cross-section of the torus for each asteroid using 1AU radius and the asteroid's angle (point on torus 1AU away from the sun in the same direction as the asteroid)
        torus cross-section is a circle so the center of the circle

        center point of torus cross-section = AU*sin(a), AU*cos(a)
        */
        double xPoint = AU * cos(angle[i]);
        double yPoint = AU * sin(angle[i]);


        //distance from center point of torus cross-section to asteroid (squared) = (x2 - x1)^2 + (y2 - y1)^2 
        double distanceSquared = pow((xPoint - xPos[i]), 2) + pow((yPoint - yPos[i]), 2);

        /*
        pythagoras theorem a ^ 2 + b ^ 2 = c ^ 2
        a^2 = c^2 - b^2
        radius of torus cross-section = 0.1AU
        max z position of asteroid = sqrt( (0.1AU)^2 - distancePointToAsteroid^2
        */
        double zLimit = sqrt(pow((0.1 * AU), 2) - distanceSquared);

        //random z position based on the z limit
        zPos[i] = (-zLimit) + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (zLimit - (-zLimit))));

        //std::cout << zPos[i] << std::endl;
    }
}