#include "Nodo.h"

Nodo::Nodo(std::string nombre, igvPunto3D posicion, float tamCubo): nombre(nombre), posicion(posicion), posicionInicial(posicion), tamCubo(tamCubo)
{
	rotacion[X] = rotacionInicial[X] = 0;
	rotacion[Y] = rotacionInicial[Y] = 0;
	rotacion[Z] = rotacionInicial[Z] = 0;

	escalado[X] = 1;
	escalado[Y] = 1;
	escalado[Z] = 1;
}

Nodo::Nodo(std::string nombre, igvPunto3D posicion, igvPunto3D rotacion, igvPunto3D escalado, float tamCubo) : nombre(nombre), posicion(posicion), posicionInicial(posicion), rotacion(rotacion), rotacionInicial(rotacion), escalado(escalado), tamCubo(tamCubo)
{
}

Nodo::~Nodo()
{
	for (unsigned i = 0; i < hijos.size(); i++)
	{
		delete hijos[i];
	}
}

void Nodo::addHijo(Nodo* hijo)
{
	hijos.push_back(hijo);
}

Nodo* Nodo::getHijo(unsigned pos)
{
	return hijos[pos];
}

Nodo* Nodo::getHijo(std::string nombre)
{
	Nodo* aux;
	if (this->nombre == nombre)
		return this;
	else {
		for (unsigned i = 0; i < hijos.size(); i++)
		{
			aux = hijos[i]->getHijo(nombre);
			if (aux)
			{
				return aux;
			}
		}
		return 0;
	}
}

igvPunto3D Nodo::getRotacion()
{
	return rotacion;
}

igvPunto3D Nodo::getPosicion()
{
	return posicion;
}

void Nodo::dibujar()
{
	glPushMatrix();//Guardamos la matriz de modelado para evitar que afecte a otros elementos como la camara

	glTranslatef(posicion[X], posicion[Y], posicion[Z]); //Aplicamos la translacion
	glRotatef(rotacion[X], 1, 0, 0); //Aplicamos las rotaciones
	glRotatef(rotacion[Y], 0, 1, 0);
	glRotatef(rotacion[Z], 0, 0, 1);
	glPushMatrix(); //Guardamos la matriz de modelado para restaurarla mas tarde sin el escalado.
	glScalef(escalado[X], escalado[Y], escalado[Z]); //Aplicamos el escalado exclusivamente al objeto de este nodo
	glutSolidCube(tamCubo); //Creamos nuestro cubo
	glPopMatrix(); //Restauramos la matriz de modelado guardada sin el escalado

	for (unsigned i = 0; i < hijos.size(); i++)
	{
		glPushMatrix(); //Guardamos la matriz de modelado actual para que todos los hijos tengan la misma
		hijos[i]->dibujar(); //Dibujamos los hijos
		glPopMatrix(); //Restauramos la matriz de modelado anteriormente guardada
	}

	glPopMatrix();//Restauramos la matriz de modelado inicialmente almacenada
}

void Nodo::setRotacion(igvPunto3D rotacion)
{
	this->rotacion = rotacion;
}

void Nodo::setPosicion(igvPunto3D posicion)
{
	this->posicion = posicion;
}

void Nodo::reset()
{
	this->rotacion = rotacionInicial;
	this->posicion = posicionInicial;
	for (unsigned i = 0; i < hijos.size(); i++)
	{
		hijos[i]->reset(); //Dibujamos los hijos
	}
}

std::string Nodo::getNombre()
{
	return nombre;
}

