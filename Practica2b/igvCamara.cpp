#include <math.h>

#include "igvCamara.h"
#include <iostream>

// Metodos constructores

igvCamara::igvCamara() {}

igvCamara::~igvCamara() {}

igvCamara::igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;

	tipo = _tipo;
}

// Metodos publicos 
void igvCamara::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;
}

void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
	double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	xwmin = _xwmin;
	xwmax = _xwmax;
	ywmin = _ywmin;
	ywmax = _ywmax;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
	double _angulo, double _raspecto, double _znear, double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	angulo = _angulo;
	raspecto = _raspecto;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::cambiarTipoCamara() {
	if (tipo == IGV_PARALELA)
		tipo = IGV_PERSPECTIVA;
	else
		tipo = IGV_PARALELA;

	aplicar();

}

void igvCamara::cambiarVista(int vista){
	std::cout << this->vista << std::endl;
	if (vista == -1) {
		this->vista = (this->vista + 1) % 4;
	}
	else {
		this->vista = vista % 4;
	}
	switch (this->vista)
	{
	case 0: //Planta
		P0 = igvPunto3D(0, 4, 0);
		V = igvPunto3D(1.0, 0, 0);
		break;
	case 1: //Alzado
		P0 = igvPunto3D(4, 0, 0);
		V = igvPunto3D(0, 1.0, 0);
		break;
	case 2: //Perfil
		P0 = igvPunto3D(0, 0, 4);
		V = igvPunto3D(0, 1.0, 0);
		break;
	default:
		P0 = igvPunto3D(3.0, 2.0, 4);
		V = igvPunto3D(0, 1.0, 0);
		break;
	}
	aplicar();
	
}

void igvCamara::aplicar(void) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (tipo == IGV_PARALELA) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_FRUSTUM) {
		glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_PERSPECTIVA) {
		gluPerspective(angulo, raspecto, znear, zfar);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z]);
}

void igvCamara::zoom(double factor) {

}
