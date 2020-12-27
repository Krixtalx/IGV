#pragma once
#include <vector>
#include <string>
#include "igvPunto3D.h"

class Nodo
{
private:
	std::vector<Nodo*> hijos;
	igvPunto3D posicion;
	igvPunto3D posicionInicial;
	igvPunto3D rotacion;
	igvPunto3D rotacionInicial;
	igvPunto3D escalado;
	float tamCubo;
	std::string nombre; //Debe de ser unico para cada nodo	

public:
	Nodo()=default;
	Nodo(std::string nombre, igvPunto3D posicion, float tamCubo);
	Nodo(std::string nombre, igvPunto3D posicion, igvPunto3D rotacion, igvPunto3D escalado, float tamCubo);
	~Nodo();
	void addHijo(Nodo* hijo);
	Nodo* getHijo(unsigned pos);
	Nodo* getHijo(std::string nombre);
	igvPunto3D getRotacion();
	igvPunto3D getPosicion();
	void dibujar();
	void setRotacion(igvPunto3D rotacion);
	void setPosicion(igvPunto3D posicion);
	void reset();
	std::string getNombre();
};

