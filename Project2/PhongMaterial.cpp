#include "PhongMaterial.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
PhongMaterial::PhongMaterial() {
	this->ambient = vec4(0.0f);
	this->diffuse = vec4(0.0f);
	this->emission = vec4(0.0f);
	this->specular = vec4(0.0f);
	this->shininess = 0;
}

void PhongMaterial::setAmbient(vec4 color) {
	this->ambient = color;
}

void PhongMaterial::setDiffuse(vec4 color) {
	this->diffuse = color;
}

void PhongMaterial::setSpecular(vec4 color) {
	this->specular = color;
}

void PhongMaterial::setEmission(vec4 color) {
	this->emission = color;
}

void PhongMaterial::setShininess(float p) {
	this->shininess = p;
}
void PhongMaterial::load(std::string filename) {
	ifstream input(filename);
	string component;
	while (input >> component) {
		if (component == "diffuse:") {
			vec4 dif;
			input >> dif.r;
			input >> dif.g;
			input >> dif.b;
			input >> dif.w;
			this->setDiffuse(dif);
		}
		else if (component == "ambient:") {
			vec4 amb;
			input >> amb.r;
			input >> amb.g;
			input >> amb.b;
			input >> amb.w;
			this->setAmbient(amb);
		}
		else if (component == "specular:") {
			vec4 spec;
			input >> spec.r;
			input >> spec.g;
			input >> spec.b;
			input >> spec.w;
			this->setSpecular(spec);
		}
		else if (component == "emission:") {
			vec4 emis;
			input >> emis.r;
			input >> emis.g;
			input >> emis.b;
			input >> emis.w;
			this->setEmission(emis);
		}
		else if (component == "shininess:") {
			float shin = 0.64;
			this->setShininess(shin);
		}

	}
	input.close();
}

void PhongMaterial::apply() {

	GLfloat ambient_[] = { this->ambient.r, this->ambient.g, this->ambient.b, this->ambient.w };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_);

	GLfloat diffuse_[] = { this->diffuse.r, this->diffuse.g, this->diffuse.b, this->diffuse.w };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_);

	GLfloat specular_[] = { this->specular.r, this->specular.g, this->specular.b, this->specular.w };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_);

	GLfloat emission_[] = { this->emission.r, this->emission.g, this->emission.b, this->emission.w };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_);

	glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);
}