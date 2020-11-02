#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "igvMallaTriangulos.h"

igvMallaTriangulos::igvMallaTriangulos() :num_vertices(0), vertices(nullptr), num_triangulos(0), triangulos(nullptr), normales(nullptr)
{
}

igvMallaTriangulos::igvMallaTriangulos(long int _num_vertices, float* _vertices, long int _num_triangulos, unsigned int* _triangulos) {

	num_vertices = _num_vertices;
	vertices = new float[num_vertices * 3];
	for (long int i = 0; i < (num_vertices * 3); ++i) {
		vertices[i] = _vertices[i];
	}

	normales = nullptr;

	num_triangulos = _num_triangulos;
	triangulos = new unsigned int[num_triangulos * 3];
	for (long int i = 0; i < (num_triangulos * 3); ++i) {
		triangulos[i] = _triangulos[i];
	}


}

igvMallaTriangulos::~igvMallaTriangulos() {
	if (vertices)
		delete[]vertices;
	if (normales)
		delete[]normales;
	if (triangulos)
		delete[]triangulos;
}


void igvMallaTriangulos::visualizar(void) {
	if (smooth)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);

	/* Apartado B: TODO */

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (normal)
		glEnable(GL_NORMALIZE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, this->vertices);

	if (normal) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, normales);
	}

	glDrawElements(GL_TRIANGLES, this->num_triangulos * 3, GL_UNSIGNED_INT, this->triangulos);
	glDisableClientState(GL_VERTEX_ARRAY);
	if (normal)
		glDisableClientState(GL_NORMAL_ARRAY);

}

void igvMallaTriangulos::setNormal()
{
	normal = !normal;
}

void igvMallaTriangulos::setSmooth()
{
	smooth = !smooth;
}



