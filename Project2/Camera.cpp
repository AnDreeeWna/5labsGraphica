
#include "Camera.h"
#include "GraphicObject.h"
using namespace std;
Camera::Camera()
{
	this->r = 0;
	this->angleX = 0;
	this->angleY = 0;
	// позиция камеры
	this->position = { 0, 0, 0 };
}

Camera::Camera(vec3 position)
{
	this->r = 0;
	this->angleX = 0;
	this->angleY = 0;
	setPosition(position);
}

Camera::Camera(float x, float y, float z)

{
	this->r = 0;
	this->angleX = 0;
	this->angleY = 0;
	setPosition(vec3(x, y, z));

}

// установка позиции камеры
void Camera::setPosition(vec3 position)
{
	// определяем радиус - расстояние от начала системы координат до заданной позиции
	r = length(position);
	// определяем вертикальный угол:
	// это угол между вектором из начала координат к наблюдателю (v1)
	// и проекцией этого вектора на горизонтальную плоскость (v2)
	// для определения угла используется скалярное произведение нормализованных векторов
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = 90 - degrees(acos(cos_y));
	// аналогичным образом определяем горизонтальный угол:
	// это угол между проекцией (v2) и единичным вектором вдоль оси Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// пересчитываем позицию (для корректировок ошибок округления)
	recalculatePosition();
}

vec3 Camera::getPosition()
{
	return this->position;
}

void Camera::rotateLeftRight(float degree)
{
	angleX = angleX + degree;
	if (angleX >= 360) {
		angleX = angleX - 360;
	}
	if (angleX <= -360) {
		angleX = angleX + 360;
	}

	recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{
	angleY = angleY - degree;
	if (angleY == 0) {
		angleY = angleY + 3;
	}
	if (angleY < 5)angleY = 5;
	if (angleY > 90)angleY = 90;
	recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
	r = r - distance;
	recalculatePosition();
}

void Camera::apply()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalculatePosition()
{
	position.x = r * cos(3.1415 * angleX / 180) * sin(angleY * 3.1415 / 180);
	position.y = r * cos(3.1415 * angleY / 180);
	position.z = r * sin(3.1415 * angleX / 180) * sin(angleY * 3.1415 / 180);

}

