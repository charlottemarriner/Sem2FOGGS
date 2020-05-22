#include "Cube.h"
#include "GLUTCallbacks.h"
#include <iostream>
#include <fstream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_rotation = 0.0f;
	
	_position.x = x; 
	_position.y = y; 
	_position.z = z;

}

Cube::~Cube()
{
	delete _material;
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->indices != nullptr)
	{
		DrawIndexedCubeAlt();
	}
}

void Cube::Update()
{
	_rotation += 0.1f;

	if (_rotation >= 360.0f)
	{
		_rotation = 0.0f;
	}
}

void Cube::DrawIndexedCubeAlt()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
	glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

	//Call material
	InitMaterial();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

	glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotation*2.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(_rotation / 2.0f, 0, 0, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Cube::InitMaterial()
{
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05; _material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05; _material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

void Cube::SetRotation(float rotation)
{
	_rotation += rotation;
}
