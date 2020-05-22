#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"]
#include "SceneObject.h"

class Sun : public SceneObject
{
private:
	Camera* camera;

	GLfloat _rotation;
	Vector3 _position;

	//Material
	Material* _material;

public:
	Sun(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Sun();

	void DrawPyramid();

	virtual void Update();
	virtual void Draw();
	void InitMaterial();
};
