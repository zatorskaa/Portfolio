#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "GameObject.h"

class Animation
{
public:
	static void AnimateUpMovement(GameObject*, float);
};

