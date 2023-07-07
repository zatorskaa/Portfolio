#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <cmath>

#include "../Coursework/cuda.cuh"

//constants
__device__ __constant__ double gravConst = 6.6743e-11; //gravitational constant
__device__ __constant__ double sunMass = 1.98847e+31;
__device__ __constant__ double AU = 1.496e+11;
__device__ __constant__ double timeStep = 60 * 60 * 24; //amount of time between each frame
__device__ __constant__ double pi = 3.141592653589793238462643;
__device__ __constant__ double minDistance = 5e+3; //minimum distance between two asteroids to calculate force
__device__ __constant__ double minDistanceSquared = 2.5e+7;


__global__ void StartVelocity(double* xPos, double* yPos, double* zPos, double* xVel, double* yVel, double* zVel, unsigned int numberOfAsteroids)
{
    //assign a thread on a block to an index number of the arrays
    int i = threadIdx.x + (blockDim.x * blockIdx.x);

    if (i < numberOfAsteroids)
    {
        /*
        direction vector from asteroid to sun

        direction = sunPosition - asteroidPosition
        sun is at center 0,0,0
        */
        double xDirAsteroidToSun = 0 - xPos[i];
        double yDirAsteroidToSun = 0 - yPos[i];
        double zDirAsteroidToSun = 0 - zPos[i];

        /*
        direction vector of asteroid

        rotating vectors
        x2 = cos(a) * x1 - sin(a) * y1
        y2 = sin(a) * x1 - cos(a) * y1

        rotated by 90 degrees to find tangent of circle
        x2 = cos(90) * x1 - sin(90) * y1
        y2 = sin(90) * x1 - cos(90) * y1

        simplifies to
        x2 = -y1
        y2 = x1
        */
        double xDirOfAsteroid = -yDirAsteroidToSun;
        double yDirOfAsteroid = xDirAsteroidToSun;
        double zDirOfAsteroid = zDirAsteroidToSun;


        //distance of asteroid from sun = sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
        double distance = sqrt((xDirAsteroidToSun * xDirAsteroidToSun) + (yDirAsteroidToSun * yDirAsteroidToSun) + (zDirAsteroidToSun * zDirAsteroidToSun));
        //v = sqrt(GM / r)
        //v = inital speed, G = gravitational constant, M = mass of sun, r = distance between asteroid and sun
        double speed = sqrt((gravConst * sunMass) / distance);
        //magnitude of direction vector of asteroid = sqrt(x^2 + y^2 + z^2)
        double magnitude = sqrt(((xDirOfAsteroid) * (xDirOfAsteroid)) + ((yDirOfAsteroid) * (yDirOfAsteroid)) + ((zDirOfAsteroid) * (zDirOfAsteroid)));

        //initial velocity of asteroid = (speed / magnitude) * direction of asteroid vector
        xVel[i] = (speed / magnitude) * xDirOfAsteroid;
        yVel[i] = (speed / magnitude) * yDirOfAsteroid;
        zVel[i] = (speed / magnitude) * zDirOfAsteroid;

        //new position = old position + (velocity * time)
        //s = vt
        //s = position, v = velocity, t = time
        xPos[i] += xVel[i] * timeStep;
        yPos[i] += yVel[i] * timeStep;
        zPos[i] += zVel[i] * timeStep;
    }

}

__global__ void CalculateForce(double* xPos, double* yPos, double* zPos, double* xVel, double* yVel, double* zVel, double* mass, unsigned int numberOfAsteroids)
{
    //assign a thread on a block to an index number of the arrays
    int i = threadIdx.x + (blockDim.x * blockIdx.x);

    double xForce = 0;
    double yForce = 0;
    double zForce = 0;

    double xDistance;
    double yDistance;
    double zDistance;
    double distanceSqaured;
    double distance;


    if (i < numberOfAsteroids)
    {
        for (int j = 0; j < numberOfAsteroids; j++)
        {
            if (i != j)
            {
                //calculate the distance between two asteroids on each axis
                //distance = pos2- pos1
                xDistance = xPos[j] - xPos[i];
                yDistance = yPos[j] - yPos[i];
                zDistance = zPos[j] - zPos[i];
                //distance between asteroids = sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
                distanceSqaured = (xDistance * xDistance) + (yDistance * yDistance) + (zDistance * zDistance);
                distance = sqrt(distanceSqaured);


                //check if the two asteroids are less than 0.05AU  apart
                if (distanceSqaured < ((0.05 * AU) * (0.05 * AU)))
                {
                    /*
                    calculate force between asteroids
                    F = (G * M1 * M2) / r^2 - scalaer force
                    F-> = (G * M1 * M2 * r->) / r^3 - vector force

                    F-> = force vector, G = gravitational constant, M1 & M2 = masses of the two asteroids, r-> = vector distance, r = scalar distance
                    */

                    //check if distance is less than minimum distance
                    if (distanceSqaured < minDistanceSquared)
                    {
                        //use the minimum distance for the calculation
                        xForce += (gravConst * mass[i] * mass[j] * minDistance) / (minDistance * minDistance * minDistance);
                        yForce += (gravConst * mass[i] * mass[j] * minDistance) / (minDistance * minDistance * minDistance);
                        zForce += (gravConst * mass[i] * mass[j] * minDistance) / (minDistance * minDistance * minDistance);
                    }
                    else
                    {
                        //use the distance for the calculation
                        xForce += (gravConst * mass[i] * mass[j] * xDistance) / (distance * distance * distance);
                        yForce += (gravConst * mass[i] * mass[j] * yDistance) / (distance * distance * distance);
                        zForce += (gravConst * mass[i] * mass[j] * zDistance) / (distance * distance * distance);
                    }

                }


            }

        }

        //calculate the distance between asteroid and sun on each axis
        //distance = pos2- pos1
        //sun is at center 0,0,0
        xDistance = 0 - xPos[i];
        yDistance = 0 - yPos[i];
        zDistance = 0 - zPos[i];
        //distance between asteroids = sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
        distance = sqrt((xDistance * xDistance) + (yDistance * yDistance) + (zDistance * zDistance));


        //check for zero division
        if (distance > 0)
        {
            /*
            calculate force between asteroid and sun
            F = (G * M1 * M2) / r^2 - scalaer force
            F-> = (G * M1 * M2 * r->) / r^3 - vector force

            F-> = force vector, G = gravitational constant, M1 & M2 = masses of the asteroid and sun, r-> = vector distance, r = scalar distance
            */
            xForce += (gravConst * mass[i] * sunMass * xDistance) / (distance * distance * distance);
            yForce += (gravConst * mass[i] * sunMass * yDistance) / (distance * distance * distance);
            zForce += (gravConst * mass[i] * sunMass * zDistance) / (distance * distance * distance);
        }


        /*
        calculate new velocityand position of asteroid
        a = F/m
        v = at

        a = acceleration, F = force, m = mass, v = velocity, t = time
        */
        xVel[i] += (xForce / mass[i]) * timeStep;
        yVel[i] += (yForce / mass[i]) * timeStep;
        zVel[i] = (zForce / mass[i]) * timeStep;

        //s = vt
        //s = position, v = velocity, t = time
        xPos[i] += xVel[i] * timeStep;
        yPos[i] += yVel[i] * timeStep;
        zPos[i] += zVel[i] * timeStep;


        xForce = 0;
        yForce = 0;
        zForce = 0;


        //printf("%f , %f, %f \n", xForce1, yForce1, zForce1);
        //printf("%f, %f, %f \n", xPos[0], yPos[0], zPos[0]);
    }

}



cudaError_t CalculatePosition(double* xPos, double* yPos, double* zPos, double* xVel, double* yVel, double* zVel, double* mass, unsigned int numberOfAsteroids)
{
    double *dev_xPos = 0;
    double *dev_yPos = 0;
    double *dev_zPos = 0;
    double *dev_xVel = 0;
    double *dev_yVel = 0;
    double *dev_zVel = 0;
    double *dev_mass = 0;
    cudaError_t cudaStatus;


    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }



    // Allocate GPU buffers
    cudaStatus = cudaMalloc((void**)&dev_xPos, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_yPos, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_zPos, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_xVel, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_yVel, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_zVel, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_mass, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }



    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_xPos, xPos, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_yPos, yPos, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_zPos, zPos, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_xVel, xVel, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_yVel, yVel, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_zVel, zVel, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_mass, mass, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }


    int numberOfBlocks = 1;
    if (numberOfAsteroids > 512)
        numberOfBlocks = (numberOfAsteroids / 512) + 1;
    // Launch a kernel on the GPU with one thread for each element.
    CalculateForce << < numberOfBlocks, 512 >> > (dev_xPos, dev_yPos, dev_zPos, dev_xVel, dev_yVel, dev_zVel, dev_mass, numberOfAsteroids);
    // Check for any errors launching the kernel 
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }

    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }


    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(xPos, dev_xPos, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(yPos, dev_yPos, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(zPos, dev_zPos, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(xVel, dev_xVel, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(yVel, dev_yVel, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(zVel, dev_zVel, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(mass, dev_mass, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }


Error:
    cudaFree(dev_xPos);
    cudaFree(dev_yPos);
    cudaFree(dev_zPos);
    cudaFree(dev_xVel);
    cudaFree(dev_yVel);
    cudaFree(dev_zVel);
    cudaFree(dev_mass);

    return cudaStatus;
}


cudaError_t CalculateStartVelocity(double* xPos, double* yPos, double* zPos, double* xVel, double* yVel, double* zVel, unsigned int numberOfAsteroids)
{
    double* dev_xPos = 0;
    double* dev_yPos = 0;
    double* dev_zPos = 0;
    double* dev_xVel = 0;
    double* dev_yVel = 0;
    double* dev_zVel = 0;
    cudaError_t cudaStatus;


    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }



    // Allocate GPU buffers
    cudaStatus = cudaMalloc((void**)&dev_xPos, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_yPos, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_zPos, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_xVel, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_yVel, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_zVel, numberOfAsteroids * sizeof(double));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }



    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_xPos, xPos, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_yPos, yPos, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_zPos, zPos, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_xVel, xVel, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_yVel, yVel, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_zVel, zVel, numberOfAsteroids * sizeof(double), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }



    int numberOfBlocks = 1;
    if (numberOfAsteroids > 512)
        numberOfBlocks = (numberOfAsteroids / 512) + 1;
    //Launch a kernel on the GPU with one thread for each element.
    StartVelocity << < numberOfBlocks, 512 >> > (dev_xPos, dev_yPos, dev_zPos, dev_xVel, dev_yVel, dev_zVel, numberOfAsteroids);
    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }

    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }


    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(xPos, dev_xPos, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(yPos, dev_yPos, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(zPos, dev_zPos, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(xVel, dev_xVel, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(yVel, dev_yVel, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(zVel, dev_zVel, numberOfAsteroids * sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }



Error:
    cudaFree(dev_xPos);
    cudaFree(dev_yPos);
    cudaFree(dev_zPos);
    cudaFree(dev_xVel);
    cudaFree(dev_yVel);
    cudaFree(dev_zVel);

    return cudaStatus;
}
