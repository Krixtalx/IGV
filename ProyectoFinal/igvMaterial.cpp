#include "igvMaterial.h"

// Metodos constructores 

igvMaterial::igvMaterial () {
	
}

igvMaterial::~igvMaterial () {

}

igvMaterial::igvMaterial (const igvMaterial& p) {	//de copia
	Ka = p.Ka;
	Kd = p.Kd;
	Ks = p.Ks;
	Ns = p.Ns;
}

igvMaterial::igvMaterial(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Metodos publicos 

void igvMaterial::aplicar(void) {

// APARTADO C
// Aplicar los valores de los atributos del objeto igvMaterial:
// - coeficiente de reflexión de la luz ambiental
	glMaterialfv(GL_FRONT, GL_AMBIENT, this->Ka.cloneToFloatArray());
// - coeficiente de reflexión difuso
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->Kd.cloneToFloatArray());
// - coeficiente de reflesión especular
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->Ks.cloneToFloatArray());
// - exponente de Phong
	glMaterialf(GL_FRONT, GL_SHININESS, this->Ns);

// establecer como color de emisión (0.0, 0.0, 0.0) (el objeto no es una fuente de luz)
	float* aux = new float[3];
	aux[0] = 0.0;
	aux[1] = 0.0;
	aux[2] = 0.0;
	glMaterialfv(GL_FRONT, GL_EMISSION, aux);


}

void igvMaterial::set(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}



