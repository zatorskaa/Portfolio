#include "GameEngine.h"

std::vector<GameObject*> GameEngine::objects;

int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;

bool GameEngine::gravity = false;

ForceGenerator GameEngine::forceGenerator;

enum GameEngine::object;
enum GameEngine::buffer;

unsigned int GameEngine::programId;
unsigned int GameEngine::vertexShaderId;
unsigned int GameEngine::fragmentShaderId;
unsigned int GameEngine::modelViewMatLoc;
unsigned int GameEngine::projMatLoc;
unsigned int GameEngine::ballLoc_0;
unsigned int GameEngine::ballTexLoc_0;
unsigned int GameEngine::ballLoc_1;
unsigned int GameEngine::ballTexLoc_1;
unsigned int GameEngine::ballLoc_2;
unsigned int GameEngine::ballTexLoc_2;
unsigned int GameEngine::ballLoc_3;
unsigned int GameEngine::ballTexLoc_3;
unsigned int GameEngine::ballLoc_4;
unsigned int GameEngine::ballTexLoc_4;
unsigned int GameEngine::ballLoc_5;
unsigned int GameEngine::ballTexLoc_5;
unsigned int GameEngine::ballLoc_6;
unsigned int GameEngine::ballTexLoc_6;
unsigned int GameEngine::ballLoc_7;
unsigned int GameEngine::ballTexLoc_7;
unsigned int GameEngine::ballLoc_8;
unsigned int GameEngine::ballTexLoc_8;
unsigned int GameEngine::ballLoc_9;
unsigned int GameEngine::ballTexLoc_9;
unsigned int GameEngine::ballLoc_10;
unsigned int GameEngine::ballTexLoc_10;
unsigned int GameEngine::ballLoc_11;
unsigned int GameEngine::ballTexLoc_11;
unsigned int GameEngine::ballLoc_12;
unsigned int GameEngine::ballTexLoc_12;
unsigned int GameEngine::ballLoc_13;
unsigned int GameEngine::ballTexLoc_13;
unsigned int GameEngine::ballLoc_14;
unsigned int GameEngine::ballTexLoc_14;
unsigned int GameEngine::ballLoc_15;
unsigned int GameEngine::ballTexLoc_15;
unsigned int GameEngine::roomLoc;
unsigned int GameEngine::roomTexLoc;
unsigned int GameEngine::tableLoc;
unsigned int GameEngine::tableTexLoc;
unsigned int GameEngine::stickLoc;
unsigned int GameEngine::stickTexLoc;
unsigned int GameEngine::triangleLoc;
unsigned int GameEngine::triangleTexLoc;
unsigned int GameEngine::buffer[20];
unsigned int GameEngine::vao[20];
unsigned int GameEngine::texture[19];

//initialise values
glm::mat4 GameEngine::modelViewMat = glm::mat4(1.0);
glm::mat4 GameEngine::projMat = glm::mat4(1.0);
glm::vec4 GameEngine::globAmb = glm::vec4(0.2, 0.2, 0.2, 1.0);

Camera GameEngine::camera;
glm::vec3 GameEngine::cameraLocation = glm::vec3(0, 0, 0);

Animation GameEngine::animation;

Material GameEngine::sphereFandB = 
{
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0),
		50.0f
};
Light GameEngine::light0 = 
{
		glm::vec4(0.0, 0.0, 0.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 0.0)
};

//texture file names
std::string GameEngine::TexNames[] = 
{
		"Textures/ball_white.png",
		"Textures/ball1.png",
		"Textures/ball2.png",
		"Textures/ball3.png",
		"Textures/ball4.png",
		"Textures/ball5.png",
		"Textures/ball6.png",
		"Textures/ball7.png",
		"Textures/ball8.png",
		"Textures/ball9.png",
		"Textures/ball10.png",
		"Textures/ball11.png",
		"Textures/ball12.png",
		"Textures/ball13.png",
		"Textures/ball14.png",
		"Textures/ball15.png",
		"Textures/room.png",
		"Textures/pool_table.png",
		"Textures/cue_stick.png",
};




void GameEngine::UpdateGame()
{
	//calculate delta time
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (newTimeSinceStart - oldTimeSinceStart);
	deltaTime /= 1000.f;

	//reset forces for all objects at start of frame
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->rigidBody->ResetForces();
	}

	//check for collisions
	CollisionDetection(deltaTime);

	//add gravity to objects
	if (gravity)
	{
		forceGenerator.Update();
	}

	//update position, velocity & acceleration for all game objects
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Update(deltaTime);
	}

	//play animations
	Animations();

	glutPostRedisplay();
}

void GameEngine::CollisionDetection(float _deltaTime)
{
	//check all game objects for collisions
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects.size(); j++)
		{
			if (i != j)
			{
				//don't check triangle object for collisions, and don't check for AABB-AABB collisions
				if (i != 19 && j != 19 && !(objects[i]->collider->GetID() == 1 && objects[j]->collider->GetID() == 1)) 
				{
					//call function to check for collisions
					bool collision = objects[i]->collider->CollideCheck(objects[j]->collider);

					if (collision)
					{
						//initialise variables
						float impulse = 0;
						float angularImpulse = 0;
						glm::vec3 pos1 = glm::vec3(0);
						glm::vec3 pos2 = glm::vec3(0);

						//calculate impulse, angular impulse & position of objects
						impulse = objects[i]->collider->CalculateLinearImpulse(objects[i]->rigidBody->GetLinearVelocity(), objects[j]->rigidBody->GetLinearVelocity(), 0.7f, objects[i]->collider->collisionInfo.collisionNormal, objects[i]->rigidBody->GetMass(), objects[j]->rigidBody->GetMass());

						//position(+) = position(-) +- (penetration depth * normal)
						pos1 = objects[i]->rigidBody->GetPosition() + (objects[i]->collider->collisionInfo.penetrationDepth * objects[i]->collider->collisionInfo.collisionNormal);
						pos2 = objects[j]->rigidBody->GetPosition() - (objects[i]->collider->collisionInfo.penetrationDepth * objects[i]->collider->collisionInfo.collisionNormal);

						angularImpulse = objects[i]->collider->CalculateAngularImpulse(objects[i]->rigidBody->GetLinearVelocity(), objects[j]->rigidBody->GetLinearVelocity(), 0.6f, objects[i]->collider->collisionInfo.collisionNormal,
							objects[i]->rigidBody->GetMass(), objects[j]->rigidBody->GetMass(), objects[i]->rigidBody->GetInverseInertia(), objects[j]->rigidBody->GetInverseInertia(),
							(objects[i]->rigidBody->GetPosition() - objects[i]->collider->collisionInfo.collisionPoint), (objects[j]->rigidBody->GetPosition() - objects[i]->collider->collisionInfo.collisionPoint));



						if (objects[i]->collider->GetID() == 0 && objects[j]->collider->GetID() == 0)
						{
							//divide by deltatime to the balls rotate more
							angularImpulse /= _deltaTime;
						}


						//don't move/rotate room, table & cue
						if (i != 17 && i != 18 && i != 16 && i != 20 && i != 21 && i != 22 && i != 23 && i != 24 && i != 25)
						{
							//move collision objects away from each other
							objects[i]->rigidBody->SetPosition(pos1);
						}
						if (j != 17 && j != 18 && j != 16 && j != 20 && j != 21 && j != 22 && j != 23 && j != 24 && j != 25)
						{
							//move collision objects away from each other
							objects[j]->rigidBody->SetPosition(pos2);
						}
						if (i != 17 && i != 18 && i != 16 && i != 20 && i != 21 && i != 22 && i != 23 && i != 24 && i != 25)
						{
							//set linear & angular velocity and then update object position
							objects[i]->rigidBody->SetLinearVelocity(impulse, objects[i]->collider->collisionInfo.collisionNormal);
							objects[i]->rigidBody->SetAngularVelocity(angularImpulse, objects[i]->collider->collisionInfo.collisionNormal, objects[i]->rigidBody->GetPosition() - objects[i]->collider->collisionInfo.collisionPoint);
							objects[i]->Update(_deltaTime);
							objects[i]->rigidBody->ResetForces();
						}
						if (j != 17 && j != 18 && j != 16 && j != 20 && j != 21 && j != 22 && j != 23 && j != 24 && j != 25)
						{
							//set linear & angular velocity and then update object position
							objects[j]->rigidBody->SetLinearVelocity(-impulse, objects[i]->collider->collisionInfo.collisionNormal);
							objects[j]->rigidBody->SetAngularVelocity(-angularImpulse, objects[i]->collider->collisionInfo.collisionNormal, objects[j]->rigidBody->GetPosition() - objects[i]->collider->collisionInfo.collisionPoint);
							objects[j]->Update(_deltaTime);
							objects[j]->rigidBody->ResetForces();
						}
					}
				}
			}
		}
	}
}

void GameEngine::DrawGame(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelViewMat = glm::mat4(1.0);

	glm::vec3 center;

	//check which camera is active and set up the camera position (eye) and center depending on the active camera
	if (camera.GetNumber() == 1)
	{
		cameraLocation = glm::vec3(0.0 + camera.GetPosition().x, 10.0 + camera.GetPosition().y, 15.0 + camera.GetPosition().z);
		center = glm::vec3(0.0, 5.0, 0.0);
	}
	else if (camera.GetNumber() == 2)
	{
		cameraLocation = glm::vec3(0.0 + camera.GetPosition().x, 10.0 + camera.GetPosition().y, -15.0 + camera.GetPosition().z);
		center = glm::vec3(0.0, 5.0, 0.0);
	}
	else if (camera.GetNumber() == 3)
	{
		cameraLocation = glm::vec3(0.0 + camera.GetPosition().x, 11.0 + camera.GetPosition().y, 0.2);
		center = glm::vec3(0.0, 5.0, 0.0);
	}
	else if (camera.GetNumber() == 4)
	{
		//cue ball cam will follow cue ball using the cue ball position as center
		cameraLocation = glm::vec3(objects[0]->rigidBody->GetPosition().x + camera.GetPosition().x, 10.0 + camera.GetPosition().y, objects[0]->rigidBody->GetPosition().z + 0.1 + camera.GetPosition().z);
		center = objects[0]->rigidBody->GetPosition();
	}
	//pass camera vaue to cue stick to change control keys
	objects[18]->SetCamera(camera.GetNumber());

	//update modelViewMat eye & center positions
	modelViewMat = lookAt(cameraLocation, center, glm::vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, value_ptr(modelViewMat));

	//for each object pass in the model view matrix, object position & rotation, camera location & center (to update model matrix)
	glUniform1ui(ballLoc_0, BALL_0);
	objects[0]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[0]->rigidBody->GetPosition(), objects[0]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[0]->Draw();
	glUniform1ui(ballLoc_1, BALL_1);
	objects[1]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[1]->rigidBody->GetPosition(), objects[1]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[1]->Draw();
	glUniform1ui(ballLoc_2, BALL_2);
	objects[2]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[2]->rigidBody->GetPosition(), objects[2]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[2]->Draw();
	glUniform1ui(ballLoc_3, BALL_3);
	objects[3]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[3]->rigidBody->GetPosition(), objects[3]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[3]->Draw();
	glUniform1ui(ballLoc_4, BALL_4);
	objects[4]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[4]->rigidBody->GetPosition(), objects[4]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[4]->Draw();
	glUniform1ui(ballLoc_5, BALL_5);
	objects[5]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[5]->rigidBody->GetPosition(), objects[5]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[5]->Draw();
	glUniform1ui(ballLoc_6, BALL_6);
	objects[6]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[6]->rigidBody->GetPosition(), objects[6]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[6]->Draw();
	glUniform1ui(ballLoc_7, BALL_7);
	objects[7]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[7]->rigidBody->GetPosition(), objects[7]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[7]->Draw();
	glUniform1ui(ballLoc_8, BALL_8);
	objects[8]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[8]->rigidBody->GetPosition(), objects[8]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[8]->Draw();
	glUniform1ui(ballLoc_9, BALL_9);
	objects[9]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[9]->rigidBody->GetPosition(), objects[9]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[9]->Draw();
	glUniform1ui(ballLoc_10, BALL_10);
	objects[10]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[10]->rigidBody->GetPosition(), objects[10]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[10]->Draw();
	glUniform1ui(ballLoc_11, BALL_11);
	objects[11]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[11]->rigidBody->GetPosition(), objects[11]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[11]->Draw();
	glUniform1ui(ballLoc_12, BALL_12);
	objects[12]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[12]->rigidBody->GetPosition(), objects[12]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[12]->Draw();
	glUniform1ui(ballLoc_13, BALL_13);
	objects[13]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[13]->rigidBody->GetPosition(), objects[13]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[13]->Draw();
	glUniform1ui(ballLoc_14, BALL_14);
	objects[14]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[14]->rigidBody->GetPosition(), objects[14]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[14]->Draw();
	glUniform1ui(ballLoc_15, BALL_15);
	objects[15]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[15]->rigidBody->GetPosition(), objects[15]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[15]->Draw();
	glUniform1ui(roomLoc, ROOM);
	objects[16]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[16]->rigidBody->GetPosition(), objects[16]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[16]->Draw();
	glUniform1ui(tableLoc, TABLE);
	objects[17]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[17]->rigidBody->GetPosition(), objects[17]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[17]->Draw();
	glUniform1ui(stickLoc, STICK);
	objects[18]->model->UpdateModelMatrix(modelViewMatLoc, 5.0f, objects[18]->rigidBody->GetPosition(), objects[18]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[18]->Draw();
	glUniform1ui(triangleLoc, TRIANGLE);
	objects[19]->model->UpdateModelMatrix(modelViewMatLoc, 7.0f, objects[19]->rigidBody->GetPosition(), objects[19]->rigidBody->GetOrientation(), cameraLocation, center);
	objects[19]->Draw();

	glutSwapBuffers();
}

void GameEngine::Animations()
{
	if (gravity)
	{
		animation.AnimateUpMovement(objects[19], 20.0f);
	}
}

void GameEngine::CleanupEngine()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		delete objects[i];
	}
}

void GameEngine::ResizeWindow(int _w, int _h)
{
	glViewport(0, 0, _w, _h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)_w / (float)_h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void GameEngine::Setup()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Create shader program executable.
	vertexShaderId = setShader("vertex", "vertexShader.glsl");
	fragmentShaderId = setShader("fragment", "fragmentShader.glsl");
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glUseProgram(programId);

	//codes for OpenGL lighting
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.ambRefl"), 1, &sphereFandB.ambRefl[0]);
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.difRefl"), 1, &sphereFandB.difRefl[0]);
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.specRefl"), 1, &sphereFandB.specRefl[0]);
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.emitCols"), 1, &sphereFandB.emitCols[0]);
	glUniform1f(glGetUniformLocation(programId, "sphereFandB.shininess"), sphereFandB.shininess);

	glUniform4fv(glGetUniformLocation(programId, "globAmb"), 1, &globAmb[0]);

	glUniform4fv(glGetUniformLocation(programId, "light0.ambCols"), 1, &light0.ambCols[0]);
	glUniform4fv(glGetUniformLocation(programId, "light0.difCols"), 1, &light0.difCols[0]);
	glUniform4fv(glGetUniformLocation(programId, "light0.specCols"), 1, &light0.specCols[0]);
	glUniform4fv(glGetUniformLocation(programId, "light0.coords"), 1, &light0.coords[0]);

	// Create VAOs and VBOs... 
	glGenVertexArrays(20, vao);
	glGenBuffers(20, buffer);

	// Obtain projection matrix uniform location and set value.
	projMatLoc = glGetUniformLocation(programId, "projMat");   //uniform mat4 projMat;
	projMat = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMat));
	
	glGenTextures(19, texture);


	//model setup
	Ball0Setup();
	Ball1Setup();
	Ball2Setup();
	Ball3Setup();
	Ball4Setup();
	Ball5Setup();
	Ball6Setup();
	Ball7Setup();
	Ball8Setup();
	Ball9Setup();
	Ball10Setup();
	Ball11Setup();
	Ball12Setup();
	Ball13Setup();
	Ball14Setup();
	Ball15Setup();
	RoomSetup();
	TableSetup();
	StickSetup();
	TriangleSetup();
}

void GameEngine::Ball0Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_0 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_0]);
	glGenBuffers(1, &buffer[BALL_VERTICES_0]);

	objects[0]->model->SetIDs(vao[BALL_0], buffer[BALL_VERTICES_0], 0, 0);
	objects[0]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	data = SOIL_load_image(TexNames[0].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_0 = glGetUniformLocation(programId, "ballTex_0");
	glUniform1i(ballTexLoc_0, 0); //send texture to shader
}

void GameEngine::Ball1Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_1 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_1]);
	glGenBuffers(1, &buffer[BALL_VERTICES_1]);

	objects[1]->model->SetIDs(vao[BALL_1], buffer[BALL_VERTICES_1], 0, 0);
	objects[1]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	data = SOIL_load_image(TexNames[1].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_1 = glGetUniformLocation(programId, "ballTex_1");
	glUniform1i(ballTexLoc_1, 1); //send texture to shader
}

void GameEngine::Ball2Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_2 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_2]);
	glGenBuffers(1, &buffer[BALL_VERTICES_2]);

	objects[2]->model->SetIDs(vao[BALL_2], buffer[BALL_VERTICES_2], 0, 0);
	objects[2]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	data = SOIL_load_image(TexNames[2].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_2 = glGetUniformLocation(programId, "ballTex_2");
	glUniform1i(ballTexLoc_2, 2); //send texture to shader
}

void GameEngine::Ball3Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_3 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_3]);
	glGenBuffers(1, &buffer[BALL_VERTICES_3]);

	objects[3]->model->SetIDs(vao[BALL_3], buffer[BALL_VERTICES_3], 0, 0);
	objects[3]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture[3]);

	data = SOIL_load_image(TexNames[3].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_3 = glGetUniformLocation(programId, "ballTex_3");
	glUniform1i(ballTexLoc_3, 3); //send texture to shader
}

void GameEngine::Ball4Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_4 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_4]);
	glGenBuffers(1, &buffer[BALL_VERTICES_4]);

	objects[4]->model->SetIDs(vao[BALL_4], buffer[BALL_VERTICES_4], 0, 0);
	objects[4]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture[4]);

	data = SOIL_load_image(TexNames[4].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_4 = glGetUniformLocation(programId, "ballTex_4");
	glUniform1i(ballTexLoc_4, 4); //send texture to shader
}

void GameEngine::Ball5Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_5 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_5]);
	glGenBuffers(1, &buffer[BALL_VERTICES_5]);

	objects[5]->model->SetIDs(vao[BALL_5], buffer[BALL_VERTICES_5], 0, 0);
	objects[5]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture[5]);

	data = SOIL_load_image(TexNames[5].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_5 = glGetUniformLocation(programId, "ballTex_5");
	glUniform1i(ballTexLoc_5, 5); //send texture to shader
}

void GameEngine::Ball6Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_6 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_6]);
	glGenBuffers(1, &buffer[BALL_VERTICES_6]);

	objects[6]->model->SetIDs(vao[BALL_6], buffer[BALL_VERTICES_6], 0, 0);
	objects[6]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, texture[6]);

	data = SOIL_load_image(TexNames[6].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_6 = glGetUniformLocation(programId, "ballTex_6");
	glUniform1i(ballTexLoc_6, 6); //send texture to shader
}

void GameEngine::Ball7Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_7 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_7]);
	glGenBuffers(1, &buffer[BALL_VERTICES_7]);

	objects[7]->model->SetIDs(vao[BALL_7], buffer[BALL_VERTICES_7], 0, 0);
	objects[7]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture[7]);

	data = SOIL_load_image(TexNames[7].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_7 = glGetUniformLocation(programId, "ballTex_7");
	glUniform1i(ballTexLoc_7, 7); //send texture to shader
}

void GameEngine::Ball8Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_8 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_8]);
	glGenBuffers(1, &buffer[BALL_VERTICES_8]);

	objects[8]->model->SetIDs(vao[BALL_8], buffer[BALL_VERTICES_8], 0, 0);
	objects[8]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture[8]);

	data = SOIL_load_image(TexNames[8].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_8 = glGetUniformLocation(programId, "ballTex_8");
	glUniform1i(ballTexLoc_8, 8); //send texture to shader
}

void GameEngine::Ball9Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_9 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_9]);
	glGenBuffers(1, &buffer[BALL_VERTICES_9]);

	objects[9]->model->SetIDs(vao[BALL_9], buffer[BALL_VERTICES_9], 0, 0);
	objects[9]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture[9]);

	data = SOIL_load_image(TexNames[9].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_9 = glGetUniformLocation(programId, "ballTex_9");
	glUniform1i(ballTexLoc_9, 9); //send texture to shader
}

void GameEngine::Ball10Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_10 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_10]);
	glGenBuffers(1, &buffer[BALL_VERTICES_10]);

	objects[10]->model->SetIDs(vao[BALL_10], buffer[BALL_VERTICES_10], 0, 0);
	objects[10]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, texture[10]);

	data = SOIL_load_image(TexNames[10].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_10 = glGetUniformLocation(programId, "ballTex_10");
	glUniform1i(ballTexLoc_10, 10); //send texture to shader
}

void GameEngine::Ball11Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_11 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_11]);
	glGenBuffers(1, &buffer[BALL_VERTICES_11]);

	objects[11]->model->SetIDs(vao[BALL_11], buffer[BALL_VERTICES_11], 0, 0);
	objects[11]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, texture[11]);

	data = SOIL_load_image(TexNames[11].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_11 = glGetUniformLocation(programId, "ballTex_11");
	glUniform1i(ballTexLoc_11, 11); //send texture to shader
}

void GameEngine::Ball12Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_12 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_12]);
	glGenBuffers(1, &buffer[BALL_VERTICES_12]);

	objects[12]->model->SetIDs(vao[BALL_12], buffer[BALL_VERTICES_12], 0, 0);
	objects[12]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, texture[12]);

	data = SOIL_load_image(TexNames[12].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_12 = glGetUniformLocation(programId, "ballTex_12");
	glUniform1i(ballTexLoc_12, 12); //send texture to shader
}

void GameEngine::Ball13Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_13 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_13]);
	glGenBuffers(1, &buffer[BALL_VERTICES_13]);

	objects[13]->model->SetIDs(vao[BALL_13], buffer[BALL_VERTICES_13], 0, 0);
	objects[13]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_2D, texture[13]);

	data = SOIL_load_image(TexNames[13].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_13 = glGetUniformLocation(programId, "ballTex_13");
	glUniform1i(ballTexLoc_13, 13); //send texture to shader
}

void GameEngine::Ball14Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_14 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_14]);
	glGenBuffers(1, &buffer[BALL_VERTICES_14]);

	objects[14]->model->SetIDs(vao[BALL_14], buffer[BALL_VERTICES_14], 0, 0);
	objects[14]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE14);
	glBindTexture(GL_TEXTURE_2D, texture[14]);

	data = SOIL_load_image(TexNames[14].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_14 = glGetUniformLocation(programId, "ballTex_14");
	glUniform1i(ballTexLoc_14, 14); //send texture to shader
}

void GameEngine::Ball15Setup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	ballLoc_15 = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[BALL_15]);
	glGenBuffers(1, &buffer[BALL_VERTICES_15]);

	objects[15]->model->SetIDs(vao[BALL_15], buffer[BALL_VERTICES_15], 0, 0);
	objects[15]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE15);
	glBindTexture(GL_TEXTURE_2D, texture[15]);

	data = SOIL_load_image(TexNames[15].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	ballTexLoc_15 = glGetUniformLocation(programId, "ballTex_15");
	glUniform1i(ballTexLoc_15, 15); //send texture to shader
}

void GameEngine::RoomSetup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	roomLoc = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[ROOM]);
	glGenBuffers(1, &buffer[ROOM_VERTICES]);

	objects[16]->model->SetIDs(vao[ROOM], buffer[ROOM_VERTICES], 0, 3);
	objects[16]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE16);
	glBindTexture(GL_TEXTURE_2D, texture[16]);

	data = SOIL_load_image(TexNames[16].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	roomTexLoc = glGetUniformLocation(programId, "roomTex");
	glUniform1i(roomTexLoc, 16); //send texture to shader
}

void GameEngine::TableSetup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	tableLoc = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[TABLE]);
	glGenBuffers(1, &buffer[TABLE_VERTICES]);

	objects[17]->model->SetIDs(vao[TABLE], buffer[TABLE_VERTICES], 0, 3);
	objects[17]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE17);
	glBindTexture(GL_TEXTURE_2D, texture[17]);

	data = SOIL_load_image(TexNames[17].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	tableTexLoc = glGetUniformLocation(programId, "tableTex");
	glUniform1i(tableTexLoc, 17); //send texture to shader
}

void GameEngine::StickSetup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	stickLoc = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[STICK]);
	glGenBuffers(1, &buffer[STICK_VERTICES]);

	objects[18]->model->SetIDs(vao[STICK], buffer[STICK_VERTICES], 0, 3);
	objects[18]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE18);
	glBindTexture(GL_TEXTURE_2D, texture[18]);

	data = SOIL_load_image(TexNames[18].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	stickTexLoc = glGetUniformLocation(programId, "stickTex");
	glUniform1i(stickTexLoc, 18); //send texture to shader
}

void GameEngine::TriangleSetup()
{
	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	triangleLoc = glGetUniformLocation(programId, "object");  //uniform uint object;

	glGenVertexArrays(1, &vao[TRIANGLE]);
	glGenBuffers(1, &buffer[TRIANGLE_VERTICES]);

	objects[19]->model->SetIDs(vao[TRIANGLE], buffer[TRIANGLE_VERTICES], 0, 3);
	objects[19]->model->Setup();


	//texture
	int width, height;
	unsigned char* data;

	glActiveTexture(GL_TEXTURE18);
	glBindTexture(GL_TEXTURE_2D, texture[18]);

	data = SOIL_load_image(TexNames[18].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	stickTexLoc = glGetUniformLocation(programId, "stickTex");
	glUniform1i(stickTexLoc, 18); //send texture to shader
}

void GameEngine::InitEngine(int _argc, char** _argv, const char* _windowTitle, int _width, int _height)
{
	glutInit(&_argc, _argv);

	/*glutInitContextVersion(2, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);*/
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(_width, _height);
	glutInitWindowPosition(100, 0);
	glutCreateWindow(_windowTitle);
	glutDisplayFunc(DrawGame);
	glutReshapeFunc(ResizeWindow);


	glutKeyboardFunc([](unsigned char _key, int _x, int _y)
		{
			//keys
			GameObject::keys[_key] = true;
			Camera::keys[_key] = true;
			std::cout << "Key pressed: " << _key << " : " << GameObject::keys[_key] << std::endl;

			if (_key == 27)
			{
				CleanupEngine();
				exit(0);
			}

			if (_key == 'g')
			{
				gravity = !gravity;
			}
			if (_key == 'r')
			{
				objects[0]->rigidBody->ResetObject(glm::vec3(4, 4, 0));
			}

			camera.MoveCamera();
		}
	);
	glutSpecialFunc([](int _key, int _x, int _y)
		{
			//arrow keys
			GameObject::specialKeys[_key] = true;
			Camera::specialKeys[_key] = true;
			std::cout << "Key pressed: " << _key << " : " << GameObject::specialKeys[_key] << std::endl;
		}
	);
	glutKeyboardUpFunc([](unsigned char _key, int _x, int _y)
		{
			//stop pressing keys
			GameObject::keys[_key] = false;
			Camera::keys[_key] = false;
			std::cout << "Key pressed: " << _key << " : " << GameObject::keys[_key] << std::endl;
		}
	);
	glutSpecialUpFunc([](int _key, int _x, int _y)
	{
		//stop pressing arrow keys
		GameObject::specialKeys[_key] = false;
		Camera::specialKeys[_key] = false;
		std::cout << "Key pressed: " << _key << " : " << GameObject::specialKeys[_key] << std::endl;
	}
	);


	glutIdleFunc(UpdateGame);

	glewExperimental = GL_TRUE;
	glewInit();
}

void GameEngine::AddGameObject(GameObject* _gameObject)
{
	objects.push_back(_gameObject);
}

void GameEngine::StartEngine()
{
	Setup();

	glutMainLoop();
}
