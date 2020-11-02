#include <cstdlib>
#include <stdio.h>
#include <cmath>

#include "igvEscena3D.h"
#include "igvMallaTriangulos.h"
#include "igvCilindro.h"


// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

	// Apartado B: Inserta el código para crear un cilindro
	malla = new igvCilindro(1, 1, 40, 2);
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

void igvEscena3D::visualizar(void) {
	GLfloat color_malla[] = { 0,0.25,0 };
	// crear luces
	GLfloat luz0[4] = { 2.0,2.5,3.0,1 }; // luz puntual para visualizar el cubo

	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();


	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena
	glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);


	// Apartado B: la siguiente llamada hay que sustituirla por la llamada al método visualizar de la malla
	glRotatef(x, 1, 0, 0);
	glRotatef(y, 0, 1, 0);
	glRotatef(z, 0, 0, 1);

	malla->visualizar();

	/*GLUquadric* cyl = gluNewQuadric();
	gluCylinder(cyl, 1, 1, 1, 20, 5);
	gluDeleteQuadric(cyl);
	cyl=nullptr;*/




	glPopMatrix(); // restaura la matriz de modelado
}

void igvEscena3D::addX(int valor)
{
	x += valor;
	x = x % 360;
}

void igvEscena3D::addY(int valor)
{
	y += valor;
	y = y % 360;
}

void igvEscena3D::addZ(int valor)
{
	z += valor;
	z = z % 360;
}

int igvEscena3D::getX()
{
	return x;
}

int igvEscena3D::getY()
{
	return y;
}

int igvEscena3D::getZ()
{
	return z;
}


