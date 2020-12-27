#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include "Pared.h"

class igvEscena3D {
protected:
	// Atributos
	bool ejes;
	std::vector<Pared> paredes;
	igvTextura* texParedes = 0;
	int** matrizLaberinto;
	const unsigned col = 20, fil = 20;
	const int semilla = 15;
	bool resuelto = false;

	void generarLaberinto();
	void crearLaberinto();
	void mostrarLaberinto();
	bool factible(unsigned posFil, unsigned posCol);
	void resolverLaberinto(unsigned posFil, unsigned posCol, bool& encontrado);

public:
	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// Métodos
	// método con las llamadas OpenGL para visualizar la escena
	void visualizar();
	const unsigned getCol();
	const unsigned getFil();
	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };
	void resolverLaberinto();
	void comprobarColision(igvPunto3D current, igvPunto3D& target);
};

#endif
