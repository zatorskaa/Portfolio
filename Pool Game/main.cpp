#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#pragma comment(lib, "glew32.lib") 

#include "GameEngine.h"
#include "GameObject.h"
#include "ForceGenerator.h"
#include "Sphere.h"
#include "Cube.h"
#include "CueStick.h"

//creating game objects
GameEngine gameEngine;
Sphere* ball0 = new Sphere(0.2f, glm::vec3(4, 4, 0), 1.0f, 0.15f, "ball.obj");
Sphere* ball1 = new Sphere(0.1f, glm::vec3(-2, 4, 0), 1.0f, 0.15f, "ball.obj");
Sphere* ball2 = new Sphere(0.1f, glm::vec3(-2.25, 4, -0.2), 1.0f, 0.15f, "ball.obj");
Sphere* ball3 = new Sphere(0.1f, glm::vec3(-2.25, 4, 0.2), 1.0f, 0.15f, "ball.obj");
Sphere* ball4 = new Sphere(0.1f, glm::vec3(-2.5, 4, -0.4), 1.0f, 0.15f, "ball.obj");
Sphere* ball5 = new Sphere(0.1f, glm::vec3(-2.5, 4, 0.0), 1.0f, 0.15f, "ball.obj");
Sphere* ball6 = new Sphere(0.1f, glm::vec3(-2.5, 4, 0.4), 1.0f, 0.15f, "ball.obj");
Sphere* ball7 = new Sphere(0.1f, glm::vec3(-2.75, 4, -0.6), 1.0f, 0.15f, "ball.obj");
Sphere* ball8 = new Sphere(0.1f, glm::vec3(-2.75, 4, -0.2), 1.0f, 0.15f, "ball.obj");
Sphere* ball9 = new Sphere(0.1f, glm::vec3(-2.75, 4, 0.2), 1.0f, 0.15f, "ball.obj");
Sphere* ball10 = new Sphere(0.1f, glm::vec3(-2.75, 4, 0.6), 1.0f, 0.15f, "ball.obj");
Sphere* ball11 = new Sphere(0.1f, glm::vec3(-3, 4, -0.8), 1.0f, 0.15f, "ball.obj");
Sphere* ball12 = new Sphere(0.1f, glm::vec3(-3, 4, -0.4), 1.0f, 0.15f, "ball.obj");
Sphere* ball13 = new Sphere(0.1f, glm::vec3(-3, 4, 0), 1.0f, 0.15f, "ball.obj");
Sphere* ball14 = new Sphere(0.1f, glm::vec3(-3, 4, 0.4), 1.0f, 0.15f, "ball.obj");
Sphere* ball15 = new Sphere(0.1f, glm::vec3(-3, 4, 0.8), 1.0f, 0.15f, "ball.obj");
Cube* room = new Cube(1.0f, glm::vec3(0, 0, 0), 1.0f, 10.0f * 5, 0.1f, 10.0f * 5, "room.obj", 1);
Cube* table = new Cube(10000.0f, glm::vec3(0, 0, 0), 1.0f, 12.4f, 3.75f, 6.2f, "pool_table.obj", 1);
CueStick* cueStick = new CueStick(10.0f, glm::vec3(5, 3.9, 0), 0.5f, 1.32f * 5, 0.025f * 5, 0.025f * 5, "cue_stick.obj", 0);
Cube* triangle = new Cube(1.0f, glm::vec3(-2.4, 3.8, 0), 1.0f, 0.3f, 0.3f, 0.02f, "triangle.obj", 1);
//game objects for colliders only (models not rendered in game)
Cube* tableEdge1 = new Cube(1000.0f, glm::vec3(-3.1f, 3.75, -3.7), 1.0f, 5.4f, 0.5f, 1.0f, "pool_table.obj", 1);
Cube* tableEdge2 = new Cube(1000.0f, glm::vec3(3.1f, 3.75, -3.7), 1.0f, 5.4f, 0.5f, 1.0f, "pool_table.obj", 1);
Cube* tableEdge3 = new Cube(1000.0f, glm::vec3(-3.1f, 3.75, 3.7), 1.0f, 5.4f, 0.5f, 1.0f, "pool_table.obj", 1);
Cube* tableEdge4 = new Cube(1000.0f, glm::vec3(3.1f, 3.75, 3.7), 1.0f, 5.4f, 0.5f, 1.0f, "pool_table.obj", 1);
Cube* tableEdge5 = new Cube(1000.0f, glm::vec3(-6.7f, 3.75, 0), 1.0f, 1.0f, 0.5f, 5.4f, "pool_table.obj", 1);
Cube* tableEdge6 = new Cube(1000.0f, glm::vec3(6.7f, 3.75, 0), 1.0f, 1.0f, 0.5f, 5.4f, "pool_table.obj", 1);


int main(int argc, char** argv)
{
	//initialise game engine
	gameEngine.InitEngine(argc, argv, "Pool Game", 1000, 1000);

	//add objects to game engine
	gameEngine.AddGameObject(ball0);
	gameEngine.AddGameObject(ball1);
	gameEngine.AddGameObject(ball2);
	gameEngine.AddGameObject(ball3);
	gameEngine.AddGameObject(ball4);
	gameEngine.AddGameObject(ball5);
	gameEngine.AddGameObject(ball6);
	gameEngine.AddGameObject(ball7);
	gameEngine.AddGameObject(ball8);
	gameEngine.AddGameObject(ball9);
	gameEngine.AddGameObject(ball10);
	gameEngine.AddGameObject(ball11);
	gameEngine.AddGameObject(ball12);
	gameEngine.AddGameObject(ball13);
	gameEngine.AddGameObject(ball14);
	gameEngine.AddGameObject(ball15);

	gameEngine.AddGameObject(room);
	gameEngine.AddGameObject(table);
	gameEngine.AddGameObject(cueStick);
	gameEngine.AddGameObject(triangle);
	gameEngine.AddGameObject(tableEdge1);
	gameEngine.AddGameObject(tableEdge2);
	gameEngine.AddGameObject(tableEdge3);
	gameEngine.AddGameObject(tableEdge4);
	gameEngine.AddGameObject(tableEdge5);
	gameEngine.AddGameObject(tableEdge6);


	//add balls to force generator (to add gravity)
	gameEngine.forceGenerator.AddGravityObject(ball0);
	gameEngine.forceGenerator.AddGravityObject(ball1);
	gameEngine.forceGenerator.AddGravityObject(ball2);
	gameEngine.forceGenerator.AddGravityObject(ball3);
	gameEngine.forceGenerator.AddGravityObject(ball4);
	gameEngine.forceGenerator.AddGravityObject(ball5);
	gameEngine.forceGenerator.AddGravityObject(ball6);
	gameEngine.forceGenerator.AddGravityObject(ball7);
	gameEngine.forceGenerator.AddGravityObject(ball8);
	gameEngine.forceGenerator.AddGravityObject(ball9);
	gameEngine.forceGenerator.AddGravityObject(ball10);
	gameEngine.forceGenerator.AddGravityObject(ball11);
	gameEngine.forceGenerator.AddGravityObject(ball12);
	gameEngine.forceGenerator.AddGravityObject(ball13);
	gameEngine.forceGenerator.AddGravityObject(ball14);
	gameEngine.forceGenerator.AddGravityObject(ball15);

	//setup game engine
	gameEngine.StartEngine();

	return 0;
}