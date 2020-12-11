#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"

class igvEscena3D {
	protected:
		// Atributos
		igvColor Ka = { 0.15,0,0 }; // coeficiente reflexión luz ambiental
		igvColor Kd = { 0.5,0,0 }; // coeficiente reflexión difuso
		igvColor Ks = { 0.5,0,0 }; // coeficiente reflexión especular
		double   Ns = 120; // exponente de Phong

		igvPunto3D pos = {3,1,1};
		bool ejes;

	public:

		// Constructores por defecto y destructor
		igvEscena3D();
		~igvEscena3D();

		// Metodos estáticos

		// Métodos
		// método con las llamadas OpenGL para visualizar la escena
    void visualizar();

		bool get_ejes() {return ejes;};
		void set_ejes(bool _ejes){ejes = _ejes;};
		void incKa(float val);
		void incKd(float val);
		void incKs(float val);
		void incNs(double val);
		void incX(float val);
		void incY(float val);
};

#endif