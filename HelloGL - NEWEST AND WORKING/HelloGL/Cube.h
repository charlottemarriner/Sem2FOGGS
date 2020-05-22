#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	Camera* camera;

	GLfloat _rotation;
	Vector3 _position;

	//Material
	Material* _material;

public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	void DrawIndexedCubeAlt();
	void InitMaterial();
	void SetRotation(float rotation);
};


	

	