#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "vertex.h"


class Model
{
protected:
	VertexWithAll* VerticesData;  //Data with vertices, normal, texCoords

	unsigned int locationIndex;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO; //for triangle indices buffer

	glm::mat4 ModelMatrix;
	int NumVert;
	glm::vec3 position;

	void CreateObject(const char*);;
public:
	void SetIDs(unsigned int, unsigned int, unsigned int, unsigned int);

	//update position & rotation of model
	void UpdateModelMatrix(unsigned int, float, glm::vec3, glm::vec3, glm::vec3, glm::vec3);

	//setup voa, vbo & locationIndex
	void Setup();
	//show model on screen
	void Draw();

	Model(const char*, glm::vec3);
	~Model();
};

