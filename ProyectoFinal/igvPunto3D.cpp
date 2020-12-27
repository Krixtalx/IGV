#include <stdio.h>
#include <math.h>

#include "igvPunto3D.h"

// Constructores
igvPunto3D::igvPunto3D() {
	c[X] = c[Y] = c[Z] = 0.0;
}

igvPunto3D::igvPunto3D(const double& x, const double& y, const double& z) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
}

// Constructor de copia
igvPunto3D::igvPunto3D(const igvPunto3D& p) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
}

// Operador de asignación
igvPunto3D& igvPunto3D::operator = (const igvPunto3D& p) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
	return(*this);
}

igvPunto3D igvPunto3D::operator+(const igvPunto3D& other)
{
	igvPunto3D aux;
	aux[0] = this->c[0] + other[0];
	aux[1] = this->c[1] + other[1];
	aux[2] = this->c[2] + other[2];
	return aux;
}

igvPunto3D igvPunto3D::operator-(const igvPunto3D& other)
{
	igvPunto3D aux;
	aux[0] = this->c[0] - other[0];
	aux[1] = this->c[1] - other[1];
	aux[2] = this->c[2] - other[2];
	return aux;
}

igvPunto3D igvPunto3D::operator*(const float& other)
{
	igvPunto3D aux;
	aux[0] = this->c[0] * other;
	aux[1] = this->c[1] * other;
	aux[2] = this->c[2] * other;
	return aux;
}

int igvPunto3D::operator == (const igvPunto3D& p) {
	return ((fabs(c[X] - p[X]) < IGV_EPSILON) && (fabs(c[Y] - p[Y]) < IGV_EPSILON) && (fabs(c[Z] - p[Z]) < IGV_EPSILON));
}

int igvPunto3D::operator != (const igvPunto3D& p) {
	return ((fabs(c[X] - p[X]) >= IGV_EPSILON) || (fabs(c[Y] - p[Y]) >= IGV_EPSILON) || (fabs(c[Z] - p[Z]) >= IGV_EPSILON));
}

// Destructor
igvPunto3D::~igvPunto3D() {
}

// Operadores

void igvPunto3D::set(const double& x, const double& y, const double& z) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
}

float* igvPunto3D::cloneToFloatArray() const
{
	float* res = new float[4]{ (float)c[0], (float)c[1], (float)c[2], 1.0 };
	return res;
}

igvPunto3D& igvPunto3D::normalize()
{
	float modulo = sqrt(pow(c[0], 2) + pow(c[1], 2) + pow(c[2], 2));
	c[X] /= modulo;
	c[Y] /= modulo;
	c[Z] /= modulo;
	return *this;
}

igvPunto3D igvPunto3D::cross(igvPunto3D y)
{
	igvPunto3D aux;
	aux[0] = this->c[1] * y[2] - y[1] * this->c[2];
	aux[1] = -(this->c[2] * y[0] - y[2] * this->c[0]);
	aux[2] = this->c[0] * y[1] - y[0] * this->c[1];
	return aux;
}
