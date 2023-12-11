
#include "Light.h"

Light::Light() {
	this->position = vec4(0.0, 0.0, 0.0, 1.0);
}

Light::Light(vec3 position) {
	this->position = vec4(position, 1.0);
}

Light::Light(float x, float y, float z) {
	this->position = vec4(x, y, z, 1.0);
}

void Light::setPosition(vec3 position) {
	this->position = vec4(position, 1.0);
}

void Light::setDiffuse(vec4 color) {
	this->diffuse = color;
}

void Light::setAmbient(vec4 color) {
	this->ambient = color;
}

void Light::setSpecular(vec4 color) {
	this->specular = color;
}

vec4 Light::getPosition() {
	return this->position;
}

void Light::apply(GLenum LightNumber) {
	glEnable(LightNumber);
	GLfloat ambient_[] = { this->ambient.r, this->ambient.g, this->ambient.b, this->ambient.w };
	glLightfv(LightNumber, GL_AMBIENT, ambient_);
	GLfloat diffuse_[] = { this->diffuse.r, this->diffuse.g, this->diffuse.b, this->diffuse.w };
	glLightfv(LightNumber, GL_DIFFUSE, diffuse_);
	GLfloat specular_[] = { this->specular.r, this->specular.g, this->specular.b, this->specular.w };
	glLightfv(LightNumber, GL_SPECULAR, specular_);
	GLfloat position_[] = { this->position.x, this->position.y, this->position.z, 1.0f };
	glLightfv(LightNumber, GL_POSITION, position_);
}