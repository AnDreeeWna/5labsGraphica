#include "GraphicObject.h"

GraphicObject::GraphicObject()
{
	// ������� ������� � ���������� ������� ���������
	this->position = { 0, 0, 0 };
	// ���� �������� � �������������� ��������� (� ��������)
	this->angle = 0;
	// ���� ������
	this->color = { 1, 1, 1 };
	// ������� ������ - ���� �� ��������� ������ ���

	this->modelMatrix = new GLfloat[16]{
		1.0, 0.0, 0.0, 0.0, // ��� Ox
		0.0, 1.0, 0.0, 0.0, // ��� Oy
		0.0, 0.0, 1.0, 0.0, // ��� Oz
		0.0, 0.0, 0.0, 1.0  // ������� ������� (������ ������� ���������)
	};

}

void GraphicObject::setPosition(vec3 position)
{
	this->position = position;
}

vec3 GraphicObject::getPosition()
{
	return this->position;
}

void GraphicObject::setAngle(float grad)
{
	angle = grad / 180 * 3.1415;
}

float GraphicObject::getAngle()
{
	return angle;
}

void GraphicObject::set�olor(vec3 color)
{
	this->color = color;
}

vec3 GraphicObject::getColor()
{
	return color;
}

void GraphicObject::draw()
{
	glColor3f(this->color[0], this->color[1], this->color[2]);
	if (material != nullptr) {
		material->apply();
	}
	glPushMatrix();
	recalculateModelMatrix();
	glMultMatrixf(modelMatrix);
	glutWireTeapot(1.0);
	glPopMatrix();

}


void GraphicObject::recalculateModelMatrix()
{
	for (int i = 0; i < 3; i++) modelMatrix[12 + i] = position[i];
	//����������� ���� ��� �������� ������������ ��� Y
	modelMatrix[0] = cos(angle);
	modelMatrix[2] = sin(angle);
	modelMatrix[8] = -sin(angle);
	modelMatrix[10] = cos(angle);


}


void GraphicObject::rotate(float angleInDegrees)
{
	// �������������� ���� � �������
	float angleInRadians = angleInDegrees * 3.14159 / 180.0;

	// ��������� ���� �������� �������
	this->angle += angleInRadians;

	// �������� ������� ������ ��� ����� ��������
	recalculateModelMatrix();
}

void GraphicObject::setMaterial(PhongMaterial* material)
{
	this->material = material;
}

