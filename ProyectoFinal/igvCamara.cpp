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

void igvCamara::setPos(igvPunto3D _P0) {
	P0 = _P0;
	P0[1] = 3;
	aplicar();
}

void igvCamara::setPosApuntado(igvPunto3D r)
{
	this->r = r;
	aplicar();
}

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

void igvCamara::cambiarVista(int vista) {
	if (vista == -1) {
		this->vista = (this->vista + 1) % 2;
	}
	else {
		this->vista = vista % 2;
	}
	switch (this->vista)
	{
	case 0: //Planta
		P0 = P0Planta;
		r[0] = 0;
		r[1] = -1;
		r[2] = 0;
		V = igvPunto3D(0, 0, -1);
		VarZoom = 7.1 * P0[0] * 2 / 40;
		tipo = IGV_PARALELA;
		break;
	default:
		P0 = igvPunto3D(12, 8, 16);
		r = igvPunto3D(0, 0, 0);
		V = igvPunto3D(0, 1.0, 0);
		break;
	}
	aplicar();

}

void igvCamara::aplicar(void) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (VarZoom < 0.05)
		VarZoom = 0.05;

	if (tipo == IGV_PARALELA) {
		glOrtho(xwmin * VarZoom, xwmax * VarZoom, ywmin * VarZoom, ywmax * VarZoom, znear, zfar);
	}
	if (tipo == IGV_FRUSTUM) {
		glFrustum(xwmin * VarZoom, xwmax * VarZoom, ywmin * VarZoom, ywmax * VarZoom, znear, zfar);
	}
	if (tipo == IGV_PERSPECTIVA) {
		if (VarZoom > 2.95)
			VarZoom = 2.95;
		gluPerspective(angulo * VarZoom, raspecto, znear, zfar);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(P0[X], P0[Y], P0[Z], P0[X] + r[X], P0[Y] + r[Y], P0[Z] + r[Z], V[X], V[Y], V[Z]);
}

void igvCamara::zoom(double factor) {
	VarZoom -= factor;
	std::cout << "Zoom: " << VarZoom << std::endl;
	aplicar();
}

void igvCamara::setPosPlanta(igvPunto3D punto)
{
	P0Planta = punto;
}

igvPunto3D igvCamara::getPos()
{
	return P0;
}

igvPunto3D igvCamara::getRef()
{
	return r;
}

igvPunto3D igvCamara::getV()
{
	return V;
}
