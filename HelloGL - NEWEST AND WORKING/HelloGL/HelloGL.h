#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL Utilities
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Sun.h"
#include "MeshLoader.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "objLoader.h"

#define REFRESHRATE 16

class HelloGL
{
public:
	//Constructor definition
	HelloGL(int argc, char* argv[]);
	void Update();
	void Display();

	void DrawString(const char* text, Vector3* position, Color* color);

	void Keyboard(unsigned char key, int x, int y);

	void InitObjects();
	void InitLighting();
	
	void InitGL(int argc, char* argv[]);

	//destructor
	~HelloGL(void);
	
private:
	float rotation;
	Camera* camera;
	SceneObject* objects[1000];

	//Lighting variables 
	Vector4* _lightPosition;
	Lighting* _lightData;
};



