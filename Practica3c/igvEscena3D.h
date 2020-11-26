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
#include "igvCaja.h"

class igvEscena3D {
protected:
	// Otros atributos		
	bool ejes;
	std::vector<igvCaja*> cajas; //Array con todas los objetos de la escena
	int cajasX = 3, cajasY = 3, cajasZ = 3;

public:

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// método con las llamadas OpenGL para visualizar la escena
	void visualizar(void);
	void visualizarVB(void);

	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };
	std::vector<igvCaja*>& getCajas() { return cajas; };
	int encontrar(GLubyte pixel[3]);
	void addCajaX(int num);
	void addCajaY(int num);
	void addCajaZ(int num);

};

#endif
