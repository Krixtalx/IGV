#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include <iostream>

// Metodos constructores -----------------------------------

igvEscena3D::igvEscena3D() { 
	ejes = true; 
	cajasX = 3;
	cajasY = 3;
	cajasZ = 3;
}

igvEscena3D::~igvEscena3D() {}


// Metodos publicos ----------------------------------------

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

void igvEscena3D::visualizar(int escena) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	//Luces
	GLfloat light0[] = { 10,8,9,1 }; // point light source
	glLightfv(GL_LIGHT0, GL_POSITION, light0);
	glEnable(GL_LIGHT0);

	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();

	// Escena seleccionada a través del menú (click botón derecho)
	if (escena == EscenaA) renderEscenaA();
	else if (escena == EscenaB) renderEscenaB();
	else if (escena == EscenaC) renderEscenaC();

	glPopMatrix(); // restaura la matriz de modelado
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvEscena3D::addCajasX(int num)
{
	if (cajasX + num > 0)
		cajasX += num;
	else
		cajasX = 1;
}

void igvEscena3D::addCajasY(int num)
{
	if (cajasY + num > 0)
		cajasY += num;
	else
		cajasY = 1;
}

void igvEscena3D::addCajasZ(int num)
{
	if (cajasZ + num > 0)
		cajasZ += num;
	else
		cajasZ = 1;
}

void igvEscena3D::renderEscenaA() {
	GLfloat color_pieza[] = { 0,0.25,0 };

	// Practica 2a. Parte A.
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);

	glPushMatrix();
	glScalef(1, 1, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.4f, 0);
	glScalef(1.1f, 0.2f, 2.1f);
	glutSolidCube(1);
	glPopMatrix();

}

void igvEscena3D::renderEscenaB() {
	GLfloat color_pieza[] = { 0,0,0.5 };

	// Practica 2a. Parte B.
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);

	generarCajasVertical(3);
}


void igvEscena3D::renderEscenaC() {
	GLfloat color_pieza[] = { 0.5,0,0 };

	// Practica 2a. Parte C.
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);
	std::cout << "CajasX: " << cajasX << std::endl;
	std::cout <<"CajasY: " << cajasY<<std::endl;
	std::cout << "CajasZ: " << cajasZ << std::endl<< std::endl;

	for (int i = 0; i < cajasX; i++)
	{
		for (int j = 0; j < cajasY; j++)
		{
			for (int k = 0; k < cajasZ; k++)
			{
				glPushMatrix();
				glTranslatef(i*1.3f, j, k*2.5f);
				glScalef(1, 1, 2);
				glutSolidCube(1);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(i * 1.3f, j + 0.4f, k * 2.5f);
				glScalef(1.1f, 0.2f, 2.1f);
				glutSolidCube(1);
				glPopMatrix();
			}
		}
	}

	

}

void igvEscena3D::generarCajasVertical(int num) {
	for (int i = 0; i < num; i++)
	{
		glPushMatrix();
		glTranslatef(0, i, 0);
		glScalef(1, 1, 2);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, i+0.4f, 0);
		glScalef(1.1f, 0.2f, 2.1f);
		glutSolidCube(1);
		glPopMatrix();
	}

}




