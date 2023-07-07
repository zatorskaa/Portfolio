#include "Model.h"
#include "OBJloader.h"
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

void Model::CreateObject(const char* _name)
{
	std::vector<VertexWithAll> mesh = loadOBJ(_name); //Import OBJ file data into a vector array
	NumVert = mesh.size();

	this->VerticesData = new VertexWithAll[NumVert];
	for (size_t i = 0; i < NumVert; i++)
	{
		this->VerticesData[i] = mesh[i];
	}
}

void Model::SetIDs(unsigned int _vao, unsigned int _vbo, unsigned int _ibo, unsigned int _locationIndex)
{
	//set vao, vbo, ibo & locationIndex values
	VAO = _vao;
	VBO = _vbo;
	IBO = _ibo;
	locationIndex = _locationIndex;
}


void Model::Setup()
{
	//set up model vao, vbo & locationIndex for shaders
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexWithAll) * NumVert, VerticesData, GL_STATIC_DRAW);

	glVertexAttribPointer(locationIndex, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, position));
	glEnableVertexAttribArray(locationIndex);
	glVertexAttribPointer(locationIndex + 1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, normal));
	glEnableVertexAttribArray(locationIndex + 1);
	glVertexAttribPointer(locationIndex + 2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, textcoord));
	glEnableVertexAttribArray(locationIndex + 2);
}

void Model::UpdateModelMatrix(unsigned int _modelViewMatLoc, float _scale, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _cam, glm::vec3 _center)
{
	ModelMatrix = glm::mat4(1.0);
	ModelMatrix = lookAt(_cam, _center, glm::vec3(0.0, 1.0, 0.0)); //camera matrix, apply first
	
	//move model matrix to object's rigidbody position
	ModelMatrix = glm::translate(ModelMatrix, _pos);
	
	//rotate model matrix by object's rigidbody orientation
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	
	//scale the model
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(_scale, _scale, _scale));  

	glUniformMatrix4fv(_modelViewMatLoc, 1, GL_FALSE, value_ptr(ModelMatrix));  //send modelview matrix to the shader
}

void Model::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, NumVert);
}


Model::Model(const char* _name, glm::vec3 _pos)
{
	//initialise variables
	position = _pos;
	VAO = 0;
	VBO = 0;

	VerticesData = NULL;
	NumVert = 0;

	CreateObject(_name);
}

Model::~Model()
{
	free(VerticesData);
}