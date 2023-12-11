
#include <windows.h>
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GraphicObject.h"
#include "Camera.h"
#include "Light.h"
//#include "PhongMaterial.h"
//#include "Header.h"

// ���������� ������������ ���� ����������� ����������
using namespace std;
using namespace glm;

// ��������� ��� ����������������� �������� ���������� �����
const int colorCounter = 5;
vector<vec3> teapotColors = { {0.01, 0.01, 0.01}, {1, 1, 1}, {0.1, 0.02, 0.99 },{1, 0, 0},{0.57, 0, 1 } };
vec3 tempColorArray = { 0, 0, 0 };
// ������ ����������� ��������
vector<GraphicObject*> graphicObjects;

GraphicObject* obj1 = new GraphicObject();
GraphicObject* obj2 = new GraphicObject();
GraphicObject* obj3 = new GraphicObject();
GraphicObject* obj4 = new GraphicObject();

// ������ ����������� ��������
Camera camera(10, 10, 0);


double GetExecutionTime()
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	// ��������� ������� �������� ������������������
	QueryPerformanceFrequency(&frequency);

	// ������ �������� ������������������
	QueryPerformanceCounter(&start);

	// ���������� ����������� 

	// ��� ��� ����������� ������� �����

	// ��������� �������� ������������������
	QueryPerformanceCounter(&end);

	// ���������� ������� ����������
	double executionTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	return executionTime;
}

/// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};



// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// ������������� ����� ������� ������������
	GLfloat globalAmbientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);


	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	camera.apply();


	// ������� ��� ����������� �������
	for (auto go : graphicObjects) {
		//go->setAngle(0);
		go->draw();
	}

	// ����� ��������� � ������� �������
	glutSwapBuffers();

};

void rotateTeapots(float angle)
{
	for (auto go : graphicObjects) {
		//go->setAngle(0);
		go->rotate(angle);
	}
}

void cameraSimulation() {
	if (GetAsyncKeyState(VK_RIGHT)) {
		rotateTeapots(-1.0 / 10);
		camera.rotateLeftRight(-1.0 / 10);
	};
	if (GetAsyncKeyState(VK_LEFT)) {
		rotateTeapots(1.0 / 10);
		camera.rotateLeftRight(1.0 / 10);
	}
	if (GetAsyncKeyState(VK_UP)) camera.rotateUpDown(1.0 / 10);
	if (GetAsyncKeyState(VK_DOWN)) camera.rotateUpDown(-1.0 / 10);
	if (GetAsyncKeyState(VK_ADD)) camera.zoomInOut(0.02);
	if (GetAsyncKeyState(VK_SUBTRACT)) camera.zoomInOut(-0.02);

}
void simulation()
{
	// ����������� ������� ���������
	//float simulationTime = getSimulationTime();
	// ������������ ������
	cameraSimulation();
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();

};






void main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");
	vector<string> names;
	names.reserve(10);


	// 1 -----------------------------------------
	obj1->setPosition(vec3(4.0, 0.0, 0.0));
	obj1->setAngle(0);
	obj1->set�olor(teapotColors[1]);
	graphicObjects.push_back(obj1);

	// 2 -----------------------------------------

	obj2->setAngle(0);
	obj2->setPosition(vec3(-4.0, 0.0, 0.0));
	obj2->set�olor(teapotColors[2]);
	graphicObjects.push_back(obj2);

	// 3 -----------------------------------------

	obj3->setAngle(0);
	obj3->setPosition(vec3(-1.0, 0.0, 4.0));
	obj3->set�olor(teapotColors[3]);
	graphicObjects.push_back(obj3);

	// 4 -----------------------------------------

	obj4->setAngle(0);
	obj4->setPosition(vec3(0.0, 0.0, -4.0));
	obj4->set�olor(teapotColors[4]);
	graphicObjects.push_back(obj4);


	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);
	// 2. ������������� ������ ����
	glutInitWindowSize(800, 600);
	// 3. ������� ����
	glutCreateWindow("Laba_01");
	// ������������� ����������� ��������

	// ��������� ������� ��������� ������
	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(reshape);
	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	//glutKeyboardFunc(keyboard);
	glutIdleFunc(simulation);
	// �������� ���� ��������� ��������� ��
	glutMainLoop();


	//cout << "Execution Time: " << time << " seconds" << endl;

};
