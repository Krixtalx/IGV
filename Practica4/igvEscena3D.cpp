#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"

#include <iostream>

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

}

igvEscena3D::~igvEscena3D() {
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


void pintar_quad(float div_x, float div_z) {
	float ini_x = 0.0;
	float ini_z = 0.0;
	float tam_x = 5.0;
	float tam_z = 5.0;
	float inc_x = tam_x / div_x;
	float inc_z = tam_z / div_z;
	float inc_tex_x = 1 / div_x;
	float inc_tex_z = 1 / div_z;


	glNormal3f(0, 1, 0);
	for (int i = 0; i < div_x; i++)
	{
		for (int j = 0; j < div_z; j++)
		{
			glBegin(GL_QUADS);

			glTexCoord2f(i*inc_tex_x, j*inc_tex_z);
			glVertex3f(ini_x + i * inc_x, 0.0, ini_z + j * inc_z);

			glTexCoord2f(i * inc_tex_x, (j + 1) * inc_tex_z);
			glVertex3f(ini_x + i * inc_x, 0.0, ini_z + (j + 1) * inc_z);

			glTexCoord2f((i + 1) * inc_tex_x, (j + 1) * inc_tex_z);
			glVertex3f(ini_x + (i + 1) * inc_x, 0.0, ini_z + (j + 1) * inc_z);

			glTexCoord2f((i + 1) * inc_tex_x, j * inc_tex_z);
			glVertex3f(ini_x + (i + 1) * inc_x, 0.0, ini_z + j * inc_z);

			glEnd();
		}
	}


}


void igvEscena3D::visualizar(void) {
	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

		// se pintan los ejes
	if (ejes) pintar_ejes();

	// luces se aplican antes de las transformaciones a la escena para que permanezcan fijas

	// APARTADO B: Define y aplica la luz puntual especificada en el guión de prácticas
	igvFuenteLuz luz(GL_LIGHT0, { 1.0, 1.0, 1.0 }, { 0,0,0,1.0 }, { 1.0, 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 }, 1.0, 0, 0);
	luz.aplicar();

	// APARTADO F: Define y aplica la luz tipo foco especificada en el guión de prácticas
	igvFuenteLuz luz2(GL_LIGHT1, pos, { 0,0,0,1.0 }, { 1.0, 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 }, 1.0, 0, 0, { 0, -1, 0 }, 45, 3);
	luz2.aplicar();

	/* Apartado D: definir y aplicar las propiedades de material indicadas en el guión de prácticas */
	igvMaterial material(Ka, Kd, Ks, Ns);
	material.aplicar();
	/* Apartado E: sustituir los valores correspondientes a la componente R del coeficiende difuso,
				   la componente R del coeficiente especular y el exponente de Phong, por el valor
								 del atributo correspondiente de la clase igvEscena */


	/* Apartado G: Añade aquí la creación del objeto textura y su aplicación */
	std::string aux = "mapa.png";
	igvTextura tex(&aux[0]);
	

	pintar_quad(50, 50);


	glPopMatrix(); // restaura la matriz de modelado
}

void igvEscena3D::incKa(float val)
{
	Ka[0] += val;
}

void igvEscena3D::incKd(float val)
{
	Kd[0] += val;
}

void igvEscena3D::incKs(float val)
{
	Ks[0] += val;
}

void igvEscena3D::incNs(double val)
{
	Ns += val;
}

void igvEscena3D::incX(float val)
{
	pos[0] += val;
}

void igvEscena3D::incY(float val)
{
	pos[1] += val;
}
