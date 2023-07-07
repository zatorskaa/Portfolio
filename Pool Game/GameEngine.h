#pragma once

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "shader.h"
#include "light.h"
#include "material.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "ForceGenerator.h"
#include "Camera.h"
#include "Animation.h"
#include "SphereCollider.h"

#include "soil/SOIL.h"
#pragma comment(lib, "soil.lib")


class GameEngine
{
private:
	//array of gameobject pointers
	static std::vector<GameObject*> objects;

	//variables to calculate deltatime
	static int oldTimeSinceStart;
	static int newTimeSinceStart;

	static bool gravity;

	//VAO
	static enum object 
	{ 
		BALL_0, 
		BALL_1, 
		BALL_2, 
		BALL_3, 
		BALL_4,
		BALL_5,
		BALL_6,
		BALL_7,
		BALL_8,
		BALL_9,
		BALL_10,
		BALL_11,
		BALL_12,
		BALL_13,
		BALL_14,
		BALL_15,
		ROOM, 
		TABLE, 
		STICK,
		TRIANGLE
	};

	//VBO
	static enum buffer 
	{ 
		BALL_VERTICES_0, 
		BALL_VERTICES_1, 
		BALL_VERTICES_2, 
		BALL_VERTICES_3, 
		BALL_VERTICES_4,
		BALL_VERTICES_5,
		BALL_VERTICES_6,
		BALL_VERTICES_7,
		BALL_VERTICES_8,
		BALL_VERTICES_9,
		BALL_VERTICES_10,
		BALL_VERTICES_11,
		BALL_VERTICES_12,
		BALL_VERTICES_13,
		BALL_VERTICES_14,
		BALL_VERTICES_15,
		ROOM_VERTICES, 
		TABLE_VERTICES, 
		STICK_VERTICES,
		TRIANGLE_VERTICES
	};

	static unsigned int
		//id locations
		programId,
		vertexShaderId,
		fragmentShaderId,
		//matrix locations
		modelViewMatLoc,
		projMatLoc,

		//object and texture locations
		ballLoc_0,
		ballTexLoc_0,
		ballLoc_1,
		ballTexLoc_1,
		ballLoc_2,
		ballTexLoc_2,
		ballLoc_3,
		ballTexLoc_3,
		ballLoc_4,
		ballTexLoc_4,
		ballLoc_5,
		ballTexLoc_5,
		ballLoc_6,
		ballTexLoc_6,
		ballLoc_7,
		ballTexLoc_7,
		ballLoc_8,
		ballTexLoc_8,
		ballLoc_9,
		ballTexLoc_9,
		ballLoc_10,
		ballTexLoc_10,
		ballLoc_11,
		ballTexLoc_11,
		ballLoc_12,
		ballTexLoc_12,
		ballLoc_13,
		ballTexLoc_13,
		ballLoc_14,
		ballTexLoc_14,
		ballLoc_15,
		ballTexLoc_15,
		roomLoc,
		roomTexLoc,
		tableLoc,
		tableTexLoc,
		stickLoc,
		stickTexLoc,
		triangleLoc,
		triangleTexLoc,

		//vao, vbo and texture arrays
		buffer[20],
		vao[20],
		texture[19];

	//matrixes
	static glm::mat4 modelViewMat;
	static glm::mat4 projMat;
	static glm::vec4 globAmb;


	//camera
	static Camera camera;
	static glm::vec3 cameraLocation; //used to update eye location for modelViewMat

	//animation
	static Animation animation;

	//light
	static Material sphereFandB;
	static Light light0;

	//textures
	static std::string TexNames[];

	//update all object rigidbody positiions, orientation, velocity etc (physics stuff)
	static void UpdateGame();
	//detect collisions between objects (physics stuff)
	static void CollisionDetection(float);

	//update all object model positions, modelviewat, etc (opengl stuff)
	static void DrawGame(void);
	//animate objects in scene (opengl stuff)
	static void Animations();

	//delete objects from engine when game is closed
	static void CleanupEngine();
	//change game window size
	static void ResizeWindow(int _w, int _h);


	//setup shaders & light
	static void Setup();

	//set up texture and shaders for each object
	static void Ball0Setup();
	static void Ball1Setup();
	static void Ball2Setup();
	static void Ball3Setup();
	static void Ball4Setup();
	static void Ball5Setup();
	static void Ball6Setup();
	static void Ball7Setup();
	static void Ball8Setup();
	static void Ball9Setup();
	static void Ball10Setup();
	static void Ball11Setup();
	static void Ball12Setup();
	static void Ball13Setup();
	static void Ball14Setup();
	static void Ball15Setup();
	static void RoomSetup();
	static void TableSetup();
	static void StickSetup();
	static void TriangleSetup();

public:
	//force generator to add gravity to objects
	static ForceGenerator forceGenerator;

	//call functions to initialise game engine (draw functions, key presses)
	void InitEngine(int _argc, char** _argv, const char* _windowTitle, int _width, int _height);

	//add a game object to the engine
	void AddGameObject(GameObject*);

	//call set up functions for shaders, light & textures
	void StartEngine();
};
