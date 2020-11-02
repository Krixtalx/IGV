#ifndef __IGVMALLATRIANGULOS
#define __IGVMALLATRIANGULOS

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <string>

class igvMallaTriangulos {
	protected:
		// Atributos

		long int num_vertices; // número de vértices de la malla de triángulos
		float *vertices; // array con las (num_vertices * 3) coordenadas de los vértices
		float *normales; // array con las (num_vertices * 3) coordenadas de la normal a cada vértice (sólo para la generación de la esfera)

		long int num_triangulos; // número de triángulos de la malla de triángulos
		unsigned int *triangulos; // array con los (num_triangulos * 3) índices a los vértices de cada triángulo
		bool normal = false;
		bool smooth = false;

	public:
		// Constructor y destructor
		
		igvMallaTriangulos();

		igvMallaTriangulos(long int _num_vertices, float *_vertices, long int _num_triangulos, unsigned int *_triangulos);

		~igvMallaTriangulos();

		// Método con las llamadas OpenGL para visualizar la malla de triángulos
		void visualizar();

		void setNormal();

		void setSmooth();

};

#endif
