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

in vec2 texCoordsExport;
in vec3 normalExport;

struct Light
{
   vec4 ambCols;
   vec4 difCols;
   vec4 specCols;
   vec4 coords;
};

struct Material
{
   vec4 ambRefl;
   vec4 difRefl;
   vec4 specRefl;
   vec4 emitCols;
   float shininess;
};

uniform Light light0;
uniform vec4 globAmb;
uniform Material sphereFandB;

uniform sampler2D ballTex_0;
uniform sampler2D ballTex_1;
uniform sampler2D ballTex_2;
uniform sampler2D ballTex_3;
uniform sampler2D ballTex_4;
uniform sampler2D ballTex_5;
uniform sampler2D ballTex_6;
uniform sampler2D ballTex_7;
uniform sampler2D ballTex_8;
uniform sampler2D ballTex_9;
uniform sampler2D ballTex_10;
uniform sampler2D ballTex_11;
uniform sampler2D ballTex_12;
uniform sampler2D ballTex_13;
uniform sampler2D ballTex_14;
uniform sampler2D ballTex_15;
uniform sampler2D roomTex;
uniform sampler2D tableTex;
uniform sampler2D stickTex;
uniform uint object;

out vec4 colorsOut;

vec4 ballTexColor_0, 
    ballTexColor_1, 
    ballTexColor_2, 
    ballTexColor_3,
    ballTexColor_4,
    ballTexColor_5,
    ballTexColor_6,
    ballTexColor_7,
    ballTexColor_8, 
    ballTexColor_9, 
    ballTexColor_10, 
    ballTexColor_11,
    ballTexColor_12,
    ballTexColor_13,
    ballTexColor_14,
    ballTexColor_15,
    roomTexColor, 
    tableTexColor, 
    stickTexColor,
	triangleTexColor;
vec3 normal, lightDirection;
vec4 fAndBDif;

void main(void)
{  
   //setup textures
   ballTexColor_0 = texture(ballTex_0, texCoordsExport);
   ballTexColor_1 = texture(ballTex_1, texCoordsExport);
   ballTexColor_2 = texture(ballTex_2, texCoordsExport);
   ballTexColor_3 = texture(ballTex_3, texCoordsExport);
   ballTexColor_4 = texture(ballTex_4, texCoordsExport);
   ballTexColor_5 = texture(ballTex_5, texCoordsExport);
   ballTexColor_6 = texture(ballTex_6, texCoordsExport);
   ballTexColor_7 = texture(ballTex_7, texCoordsExport);
   ballTexColor_8 = texture(ballTex_8, texCoordsExport);
   ballTexColor_9 = texture(ballTex_9, texCoordsExport);
   ballTexColor_10 = texture(ballTex_10, texCoordsExport);
   ballTexColor_11 = texture(ballTex_11, texCoordsExport);
   ballTexColor_12 = texture(ballTex_12, texCoordsExport);
   ballTexColor_13 = texture(ballTex_13, texCoordsExport);
   ballTexColor_14 = texture(ballTex_14, texCoordsExport);
   ballTexColor_15 = texture(ballTex_15, texCoordsExport);
   roomTexColor = texture(roomTex, texCoordsExport);
   tableTexColor = texture(tableTex, texCoordsExport);
   stickTexColor = texture(stickTex, texCoordsExport);
   triangleTexColor = texture(stickTex, texCoordsExport);
   
   //assign textures to each model with lighting
   if (object == BALL_0)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_0 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_1)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_1 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_2)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_2 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_3)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_3 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_4)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_4 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_5)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_5 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_6)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_6 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_7)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_7 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_8)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_8 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_9)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_9 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_10)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_10 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_11)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_11 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_12)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_12 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_13)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_13 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_14)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_14 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == BALL_15)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  ballTexColor_15 * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == ROOM)
   {
	colorsOut =  roomTexColor;
   }
   if (object == TABLE)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  tableTexColor * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == STICK)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  stickTexColor * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == TRIANGLE)
   {
	normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  triangleTexColor * vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
}