#version 430 core

#define BALL_0 0
#define BALL_1 1
#define BALL_2 2
#define BALL_3 3
#define BALL_4 4
#define BALL_5 5
#define BALL_6 6
#define BALL_7 7
#define BALL_8 8
#define BALL_9 9
#define BALL_10 10
#define BALL_11 11
#define BALL_12 12
#define BALL_13 13
#define BALL_14 14
#define BALL_15 15
#define ROOM 16
#define TABLE 17
#define STICK 18
#define TRIANGLE 19

layout(location=0) in vec3 ballCoords;
layout(location=1) in vec3 ballNormals;
layout(location=2) in vec2 ballTexCoords;
layout(location=3) in vec3 objCoords;
layout(location=4) in vec3 objNormals;
layout(location=5) in vec2 objTexCoords;


uniform mat4 modelViewMat;
uniform mat4 projMat;
uniform uint object;

out vec2 texCoordsExport;
out vec3 normalExport;

vec4 coords, RotCoords;


void main(void)
{   
   if (object == BALL_0)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_1)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_2)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_3)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_4)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_5)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_6)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_7)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_8)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_9)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_10)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_11)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_12)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_13)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_14)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
    if (object == BALL_15)
    {
      coords = vec4(ballCoords, 1.0f);
      normalExport = ballNormals;
      texCoordsExport = ballTexCoords;
    }
	if (object == ROOM)
    {
      coords = vec4(objCoords, 1.0f);
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }
	if (object == TABLE)
    {
      coords = vec4(objCoords, 1.0f);
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }
	if (object == STICK)
    {
      coords = vec4(objCoords, 1.0f);
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }
	if (object == TRIANGLE)
    {
      coords = vec4(objCoords, 1.0f);
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }
   
   gl_Position = projMat * modelViewMat * coords;
}
