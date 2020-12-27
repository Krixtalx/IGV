#pragma once
#include "igvPunto3D.h"
#include "igvColor.h"
#include "igvTextura.h"
class Pared
{
private:
	igvPunto3D posicion;
	igvPunto3D rotacion;
	igvPunto3D escalado;
	igvColor color;

	igvColor Ka = { 0,0,0 }; // coeficiente reflexión luz ambiental
	igvColor Kd = { 1,1,1 }; // coeficiente reflexión difuso
	igvColor Ks = { 0,0,0 }; // coeficiente reflexión especular
	double   Ns = 120; // exponente de Phong

public:
	Pared(igvPunto3D posicion, igvPunto3D rotacion, igvColor color = { 0,0,1,1.0 });
	void dibujar();
	void crearQuad();
	static int tam;
	static bool resuelto;
};

