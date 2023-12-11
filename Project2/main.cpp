
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

// используем пространство имен стандартной библиотеки
using namespace std;
using namespace glm;

// Контейнер для последовательного хранения нескольких строк
const int colorCounter = 5;
vector<vec3> teapotColors = { {0.01, 0.01, 0.01}, {1, 1, 1}, {0.1, 0.02, 0.99 },{1, 0, 0},{0.57, 0, 1 } };
vec3 tempColorArray = { 0, 0, 0 };
// список графических объектов
vector<GraphicObject*> graphicObjects;

GraphicObject* obj1 = new GraphicObject();
GraphicObject* obj2 = new GraphicObject();
GraphicObject* obj3 = new GraphicObject();
GraphicObject* obj4 = new GraphicObject();

// список графических объектов
Camera camera(10, 10, 0);


double GetExecutionTime()
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	// Получение частоты счетчика производительности
	QueryPerformanceFrequency(&frequency);

	// Запуск счетчика производительности
	QueryPerformanceCounter(&start);

	// Выполнение тестируемой 

	// Ваш код тестируемой функции здесь

	// Остановка счетчика производительности
	QueryPerformanceCounter(&end);

	// Вычисление времени выполнения
	double executionTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	return executionTime;
}

/// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};



// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// устанавливаем общую фоновую освещенность
	GLfloat globalAmbientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);


	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	camera.apply();


	// выводим все графические объекты
	for (auto go : graphicObjects) {
		//go->setAngle(0);
		go->draw();
	}

	// смена переднего и заднего буферов
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
	// определение времени симуляции
	//float simulationTime = getSimulationTime();
	// передвижение камеры
	cameraSimulation();
	// устанавливаем признак того, что окно нуждается в перерисовке
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
	obj1->setСolor(teapotColors[1]);
	graphicObjects.push_back(obj1);

	// 2 -----------------------------------------

	obj2->setAngle(0);
	obj2->setPosition(vec3(-4.0, 0.0, 0.0));
	obj2->setСolor(teapotColors[2]);
	graphicObjects.push_back(obj2);

	// 3 -----------------------------------------

	obj3->setAngle(0);
	obj3->setPosition(vec3(-1.0, 0.0, 4.0));
	obj3->setСolor(teapotColors[3]);
	graphicObjects.push_back(obj3);

	// 4 -----------------------------------------

	obj4->setAngle(0);
	obj4->setPosition(vec3(0.0, 0.0, -4.0));
	obj4->setСolor(teapotColors[4]);
	graphicObjects.push_back(obj4);


	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("Laba_01");
	// инициализация графических объектов

	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	//glutKeyboardFunc(keyboard);
	glutIdleFunc(simulation);
	// основной цикл обработки сообщений ОС
	glutMainLoop();


	//cout << "Execution Time: " << time << " seconds" << endl;

};
