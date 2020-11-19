#include <cstdlib>
#include <stdio.h>
#include <iostream>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

	//Creamos las distintas partes de nuestro modelo.
	raiz = new Nodo("Cintura", { 0.0, 3.6, 0.0 }, { 0,0,0 }, { 1.5, 1.25, 1 }, 1.5);

	Nodo* tronco = new Nodo("Tronco", { 0.0, 2.4, 0.0 }, { 0, 0, 0 }, { 1.5, 1, 1 }, 3);
	raiz->addHijo(tronco);

	Nodo* cabeza = new Nodo("Cabeza", { 0.0, 0.0, 2 }, 1.5);
	tronco->addHijo(cabeza);

	Nodo* ojoDer = new Nodo("OjoDer", { -0.45, 0.4, 0.8 }, 0.25);
	Nodo* ojoIzq = new Nodo("OjoIzq", { 0.45, 0.4, 0.8 }, 0.25);
	Nodo* boca1 = new Nodo("Boca1", { -0.45, -0.5, 0.7 }, { 0, 0, 0 }, { 0.5, 3, 1 }, 0.25);
	Nodo* boca2 = new Nodo("Boca2", { 0, -0.5, 0.7 }, { 0, 0, 0 }, { 0.5, 3, 1 }, 0.25);
	Nodo* boca3 = new Nodo("Boca3", { 0.45, -0.5, 0.7 }, { 0, 0, 0 }, { 0.5, 3, 1 }, 0.25);
	cabeza->addHijo(ojoDer);
	cabeza->addHijo(ojoIzq);
	cabeza->addHijo(boca1);
	cabeza->addHijo(boca2);
	cabeza->addHijo(boca3);

	Nodo* hombroIzq = new Nodo("HombroIzq", { 2.9, 0, 0.0 }, 1);
	Nodo* hombroDer = new Nodo("HombroDer", { -2.9, 0, 0.0 }, 1);

	tronco->addHijo(hombroDer);
	tronco->addHijo(hombroIzq);

	Nodo* brazoIzq = new Nodo("BrazoIzq", { 0.0, -1.75, 0.0 }, { 0,0,0 }, { 1, 2.2, 1 }, 1);
	Nodo* brazoDer = new Nodo("BrazoDer", { 0.0, -1.75, 0.0 }, { 0,0,0 }, { 1, 2.2, 1 }, 1);
	hombroDer->addHijo(brazoDer);
	hombroIzq->addHijo(brazoIzq);

	Nodo* piernaIzq = new Nodo("PiernaIzq", { 1.7, -0.85, 0.0 }, { 0,0,0 }, { 1, 1.75, 1 }, 1);
	Nodo* piernaDer = new Nodo("PiernaDer", { -1.7, -0.85, 0.0 }, { 0,0,0 }, { 1, 1.75, 1 }, 1);
	raiz->addHijo(piernaDer);
	raiz->addHijo(piernaIzq);

	Nodo* piernaIzq2 = new Nodo("PiernaIzq2", { 0, -1.6, 0.0 }, { 0,0,0 }, { 1, 1.25, 1 }, 1);
	Nodo* piernaDer2 = new Nodo("PiernaDer2", { 0, -1.6, 0.0 }, { 0,0,0 }, { 1, 1.25, 1 }, 1);
	piernaDer->addHijo(piernaDer2);
	piernaIzq->addHijo(piernaIzq2);

	Nodo* pieIzq = new Nodo("PieIzq", { 0, -0.9, 0.25 }, { 0,0,0 }, { 2.5, 1, 4 }, 0.5);
	Nodo* pieDer = new Nodo("PieDer", { 0, -0.9, 0.25 }, { 0,0,0 }, { 2.5, 1, 4 }, 0.5);
	piernaDer2->addHijo(pieDer);
	piernaIzq2->addHijo(pieIzq);

	nodoSeleccionado = raiz;

	// Apartado C: inicializar los atributos para el control de los grados de libertad del modelo
	//{xMin, xMax, yMin, yMax, zMin, zMax}
	restricciones.insert(std::pair<Nodo*, int*>(raiz, new int[6]{ -180, 180,-180, 180, -180, 180 }));
	restricciones.insert(std::pair<Nodo*, int*>(tronco, new int[6]{ -25, 25, -45, 45, -10, 10 }));
	restricciones.insert(std::pair<Nodo*, int*>(cabeza, new int[6]{ -30, 30,-30, 30, -30, 30 }));
	restricciones.insert(std::pair<Nodo*, int*>(hombroDer, new int[6]{ -180, 180,-10, 10, -180, 0 }));
	restricciones.insert(std::pair<Nodo*, int*>(hombroIzq, new int[6]{ -180, 180,-10, 10, 0, 180 }));
	restricciones.insert(std::pair<Nodo*, int*>(piernaDer, new int[6]{ -90, 90,-15, 15, -60, 0 }));
	restricciones.insert(std::pair<Nodo*, int*>(piernaIzq, new int[6]{ -90, 90,-15, 15, 0, 60 }));
	restricciones.insert(std::pair<Nodo*, int*>(piernaDer2, new int[6]{ -15, 90,-15, 15, -15, 15 }));
	restricciones.insert(std::pair<Nodo*, int*>(piernaIzq2, new int[6]{ -15, 90,-15, 15, -15, 15 }));
	restricciones.insert(std::pair<Nodo*, int*>(brazoDer, new int[6]{ -180, 180,-90, 90, -90, 0 }));
	restricciones.insert(std::pair<Nodo*, int*>(brazoIzq, new int[6]{ -180, 180,-90, 90, 0, 90 }));
	restricciones.insert(std::pair<Nodo*, int*>(pieDer, new int[6]{ -45, 45,-20, 20, -20, 20 }));
	restricciones.insert(std::pair<Nodo*, int*>(pieIzq, new int[6]{ -45, 45,-20, 20, -20, 20 }));
	//No se añaden restricciones a los ojos y boca ya que nunca se van a rotar. En caso de que se desee rotar, habría que añadir la restricción
}

igvEscena3D::~igvEscena3D() {
	delete raiz;
	std::map<Nodo*, int*>::iterator it = restricciones.begin();
	while (it != restricciones.end()) {
		delete[] it->second;
		it++;
	}
}


// Metodos publicos 

void pintar_ejes(void) {
	GLfloat rojo[] = { 1,0,0,1.0 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glBegin(GL_LINES);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glBegin(GL_LINES);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}

///// Apartado B: Métodos para visualizar cada parte del modelo
void igvEscena3D::dibujarGrafoEscena()
{
	raiz->dibujar();
}



////// Apartado C: añadir aquí los métodos para modificar los grados de libertad del modelo
void igvEscena3D::modificarAnguloSeleccionado(igvPunto3D rotacion)
{
	if (nodoSeleccionado == 0)
		std::cerr << "No hay ningun nodo seleccionado." << std::endl;
	else {
		rotacionSeleccionado[X] += rotacion[X];
		rotacionSeleccionado[Y] += rotacion[Y];
		rotacionSeleccionado[Z] += rotacion[Z];
		rotacionSeleccionado = checkRestricciones(rotacionSeleccionado);
		nodoSeleccionado->setRotacion(rotacionSeleccionado);
	}
}

void igvEscena3D::modificarPosicionSeleccionado(igvPunto3D posicion)
{
	if (nodoSeleccionado == 0)
		std::cerr << "No hay ningun nodo seleccionado." << std::endl;
	else {
		posicionSeleccionado[X] += posicion[X];
		posicionSeleccionado[Y] += posicion[Y];
		posicionSeleccionado[Z] += posicion[Z];
		nodoSeleccionado->setPosicion(posicionSeleccionado);
	}
}

void igvEscena3D::resetearModelo()
{
	raiz->reset();
}



igvPunto3D igvEscena3D::checkRestricciones(igvPunto3D rotacion)
{
	std::map<Nodo*, int*>::iterator it = restricciones.find(nodoSeleccionado);

	if (rotacion[X] < it->second[0])
		rotacion[X] = it->second[0];
	else if (rotacion[X] > it->second[1])
		rotacion[X] = it->second[1];

	if (rotacion[Y] < it->second[2])
		rotacion[Y] = it->second[2];
	else if (rotacion[Y] > it->second[3])
		rotacion[Y] = it->second[3];

	if (rotacion[Z] < it->second[4])
		rotacion[Z] = it->second[4];
	else if (rotacion[Z] > it->second[5])
		rotacion[Z] = it->second[5];
	std::cout << "Rotacion " << nodoSeleccionado->getNombre() << " : " << rotacion[X] << " " << rotacion[Y] << " " << rotacion[Z] << std::endl;
	return rotacion;
}


void igvEscena3D::visualizar() {
	// crear luces
	GLfloat luz0[4] = { 5.0, 5.0, 5.0, 1 }; // luz puntual  
	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	// se pintan los ejes
	if (ejes) pintar_ejes();
	glPopMatrix();

	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena (también habría que desactivar la de arriba).



	///// Apartado B: aquí hay que añadir la visualización del árbol del modelo utilizando la pila de matrices de OpenGL
	/////             se recomienda crear una método auxiliar que encapsule todo el código para la visualización
	/////             del modelo, dejando aquí sólo la llamada a ese método, así como distintas funciones una para cada
	/////			  parte del modelo. 
	raiz->dibujar();
}

void igvEscena3D::setSeleccionado(std::string nombre)
{
	nodoSeleccionado = raiz->getHijo(nombre);
	if (nodoSeleccionado == 0)
		std::cerr << "Ha habido un error al seleccionar el nodo " << nombre << std::endl;
	else {
		rotacionSeleccionado = nodoSeleccionado->getRotacion();
		posicionSeleccionado = nodoSeleccionado->getPosicion();
	}
}


std::string igvEscena3D::getNombreNodoSel()
{
	if (nodoSeleccionado == 0)
		std::cerr << "No hay ningun nodo seleccionado." << std::endl;
	else
		return nodoSeleccionado->getNombre();
}