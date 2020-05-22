#include "Sun.h"

Sun::Sun(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_rotation = 0.0f;

	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Sun::~Sun()
{
	delete _material;
}

void Sun::Update()
{
	_rotation += 0.1f;

	if (_rotation >= 360.0f)
	{
		_rotation = 0.0f;
	}
}

void Sun::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Color != nullptr && _mesh->indices != nullptr)
	{
		DrawPyramid();
	}
}

void Sun::InitMaterial()
{
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05; _material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05; _material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

void Sun::DrawPyramid()
{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->Color);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotation*2.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(_rotation / 2.0f, 0, 0, 1.0f);
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->indices);
		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
}
