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

//========Valores configurables=========
	const unsigned col = 15, fil = 15;
	const int semilla = 15;
	bool terror = true;
//======================================

	bool puertaAbierta = false;
	bool victoria = false;
	bool resuelto = false;
	
	int posXPilar = 0;
	int posYPilar = 0;

	void generarLaberinto();
	void crearLaberinto();
	void mostrarLaberinto();
	bool factible(unsigned posFil, unsigned posCol);
	void resolverLaberinto(unsigned posFil, unsigned posCol, bool& encontrado);
	void crearPilar();

public:
	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// M�todos
	// m�todo con las llamadas OpenGL para visualizar la escena
	void visualizar();
	const unsigned getCol();
	const unsigned getFil();
	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };
	void resolverLaberinto(unsigned posFil, unsigned posCol);
	void comprobarColision(igvPunto3D current, igvPunto3D& target);
	void abrirPuerta();
};

#endif