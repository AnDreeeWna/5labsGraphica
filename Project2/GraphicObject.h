#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "PhongMaterial.h"
using namespace glm;
// ����� ��� ������������� ������ ������������ �������
class GraphicObject
{
public:

	GraphicObject();
	// ��������� � ��������� ������� �������
	void setPosition(vec3 position);
	vec3 getPosition();
	// ��������� � ��������� ���� �������� � ��������
	// ������� �������������� � �������������� ���������
	// ������ ��� Oy �� ������� �������
	void setAngle(float grad);
	float getAngle();
	// ��������� �������� ����� �������
	void set�olor(vec3 color);
	vec3 getColor();
	// ������� ������
	void draw();
	void rotate(float a);
	// ��������� ������������� ���������
	void setMaterial(PhongMaterial* material);
private:
	// ������� ������� � ���������� ������� ���������
	vec3 position;
	// ���� �������� � �������������� ��������� (� ��������)
	float angle;
	// ���� ������
	vec3 color;
	// ������� ������ - ���� �� ��������� ������ ���
	GLfloat* modelMatrix;
	// ������������ ��������
	PhongMaterial* material;

private:
	// ������ ������� modelMatrix �� ������ position � angle
	void recalculateModelMatrix();

};



