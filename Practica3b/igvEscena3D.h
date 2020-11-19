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
#include "igvPunto3D.h"
#include "Nodo.h"
#include <map>


class igvEscena3D {
protected:
	// Otros atributos		
	bool ejes;
	Nodo* raiz;
	Nodo* nodoSeleccionado; //Para realizar la rotacion
	igvPunto3D rotacionSeleccionado;
	igvPunto3D posicionSeleccionado;
	////// Apartado C: añadir quí los atributos para el control de los grados de libertad del modelo
	std::map<Nodo*, int*> restricciones;

public:

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// método con las llamadas OpenGL para visualizar la escena
	void visualizar(void);

	///// Apartado B: Métodos para visualizar cada parte del modelo
	void dibujarGrafoEscena();

	////// Apartado C: añadir aquí los métodos para modificar los grados de libertad del modelo
	void setSeleccionado(std::string nombre);
	void modificarAnguloSeleccionado(igvPunto3D rotacion);
	void modificarPosicionSeleccionado(igvPunto3D posicion);
	void resetearModelo();
	std::string getNombreNodoSel();
	igvPunto3D checkRestricciones(igvPunto3D rotacion);

	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

};

#endif
