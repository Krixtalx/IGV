#ifndef __IGVCAMARA
#define __IGVCAMARA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvPunto3D.h"
#include <string>

typedef enum {
	IGV_PARALELA,
	IGV_FRUSTUM,
	IGV_PERSPECTIVA
} tipoCamara;

class igvCamara {

public:
	// atributos

	tipoCamara tipo;	// paralela o perspectiva

	// ventana de visi�n: parametros proyecci�n paralela y frustum
	GLdouble xwmin, xwmax, ywmin, ywmax;

	// ventana de visi�n: parametros proyecci�n perspectiva
	GLdouble 	angulo, raspecto;

	// distancias de planos cercano y lejano
	GLdouble znear, zfar;

	// punto de visi�n
	igvPunto3D P0;
	igvPunto3D P0Planta;

	// punto de referencia de visi�n
	igvPunto3D r;

	// vector arriba
	igvPunto3D V;

	int vista = 3;

	double VarZoom = 1;

	// Metodos

public:
	// Constructores por defecto y destructor
	igvCamara();
	~igvCamara();

	// Otros constructores
	igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V);

	// Metodos
	void setPos(igvPunto3D _P0);
	// define el punto de referencia
	void setPosApuntado(igvPunto3D r);
	// define la posici�n de la c�mara
	void set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V);

	// define una c�mara de tipo paralela o frustum
	void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
		double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar);

	// define una c�mara de tipo perspectiva
	void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
		double _angulo, double _raspecto, double _znear, double _zfar);

	void cambiarTipoCamara();

	

	void cambiarVista(int vista = -1);

	void aplicar(void); // aplica a los objetos de la escena la transformaci�n de visi�n y la transformaci�n de proyecci�n
						// asociadas a los par�metros de la c�mara

	void zoom(double factor); // realiza un zoom sobre la c�mara
	void setPosPlanta(igvPunto3D punto);
	igvPunto3D getPos();
	igvPunto3D getRef();
	igvPunto3D getV();
};

#endif

