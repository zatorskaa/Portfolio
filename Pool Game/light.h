#pragma once

#include <glm/glm.hpp>

struct Light
{
	glm::vec4 ambCols;
	glm::vec4 difCols;
	glm::vec4 specCols;
	glm::vec4 coords;
};