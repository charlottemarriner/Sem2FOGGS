#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include <ctime>
#include <iostream>

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);

	InitObjects();
	InitLighting();
	
	//Start Main Game Loop
	glutMainLoop();
}


HelloGL::~HelloGL(void)
{
	delete camera;
	delete objects;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //this clears the scene

	Vector3 v = { -1.4f, 0.7f, -1.0f };
	Color c = { 0.0f, 1.0f, 0.0f };
	DrawString("Hello there", &v, &c);
	for (int i = 0; i < 1000; i++)
	{
		objects[i]->Draw();
	}
	glFlush(); //flushes the scene drawn to the graphics card
	glutSwapBuffers();
	
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y,
		camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR , &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));


	for (int i = 0; i < 1000; i++)
	{
		objects[i]->Update();
	}

	
	glutPostRedisplay();
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
	{
		camera->eye.x -= 0.5f;
	}
	else if (key == 'a')
	{
		camera->eye.x += 0.5f;
	}
	if (key == 'w')
	{
		camera->eye.z -= 0.5f;
	}
	else if (key == 's')
	{
		camera->eye.z += 0.5f;
	}
	else if (key == 'r')
	{
		objects[4]->SetRotation(10);
	}
}

void HelloGL::InitObjects()
{
	Mesh* cubeMesh = MeshLoader::LoadTextureMesh((char*)("cube.txt"));
	Mesh* pyramidMesh = MeshLoader::LoadColorMesh((char*)("pyramid.txt"));

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);

	Texture2D* texture2 = new Texture2D();
	texture2->Load((char*)"stars.raw", 512, 512);

	std::cout << texture->GetID() << "THINGY" << std::endl;

	srand(time(NULL));
	//Initialise camera
	camera = new Camera();
	for (int i = 0; i < 200; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);

	}
	for (int i = 200; i < 1000; i++)
	{
		objects[i] = new Sun(pyramidMesh, texture2, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;

}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Horrible OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Set the viewport to be the entire window
	glViewport(0, 0, 800, 800);


	//Set the correct perspective
	gluPerspective(45, 1, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);

	//Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Enable textures
	glEnable(GL_TEXTURE_2D);

	//Initialise back face culling and depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}




