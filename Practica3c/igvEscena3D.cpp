#include <cstdlib>
#include <stdio.h>
#include<iostream>
#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

	for (int pilasY = 0; pilasY < 10; pilasY++) {
		for (int pilasX = 0; pilasX < 10; pilasX++) {
			for (int pilasZ = 0; pilasZ < 10; pilasZ++) {
				cajas.push_back(new igvCaja(0.1 * pilasX, 0.1 * pilasY, 0.1 * pilasZ)); //Se crea una nueva caja con el color indicado
			}
		}
	}
}

igvEscena3D::~igvEscena3D() {
	for (int i = 0; i < cajas.size(); i++)
	{
		delete cajas[i];
	}
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

//Método para la visualización del modelo
void igvEscena3D::visualizar() {
	// crear luces
	GLfloat luz0[4] = { 5.0,5.0,5.0,1 }; // luz puntual  
	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado
	if (ejes) pintar_ejes(); // se pintan los ejes
	glPopMatrix();

	glPushMatrix();
	visualizarVB();
	glPopMatrix();

}

//Método para la visualización del modelo sin luces (se utiliza durante la selección)
void igvEscena3D::visualizarVB() {
	GLfloat separacionX = 2.5;
	GLfloat separacionZ = 2.5;

	int cont = 0;
	// Practica 2a. Parte B y C.
	for (int pilasY = 0; pilasY < cajasY; pilasY++) {
		for (int pilasX = 0; pilasX < cajasX; pilasX++) {
			for (int pilasZ = 0; pilasZ < cajasZ; pilasZ++) {
				glPushMatrix();
				glTranslatef(pilasX * separacionX, pilasY, pilasZ * separacionZ);
				cajas[pilasY * 100 + pilasX * 10  + pilasZ]->visualizar(); //Se visualiza la caja
				glPopMatrix();
			}
		}
	}
}

int igvEscena3D::encontrar(GLubyte pixel[3])
{
	for (int i = 0; i < cajas.size(); i++)
	{
		GLubyte* pixelCaja = cajas[i]->getColorByte();
		if (pixelCaja[0] == pixel[0] && pixelCaja[1] == pixel[1] && pixelCaja[2] == pixel[2])
			return i;
	}
	return -1;
}

void igvEscena3D::addCajaX(int num)
{
	cajasX += num;
	if (cajasX < 0)
		cajasX = 0;
	else if (cajasX > 10)
		cajasX = 10;
}

void igvEscena3D::addCajaY(int num)
{
	cajasY += num;
	if (cajasY < 0)
		cajasY = 0;
	else if (cajasY > 10)
		cajasY = 10;
}

void igvEscena3D::addCajaZ(int num)
{
	cajasZ += num;
	if (cajasZ < 0)
		cajasZ = 0;
	else if (cajasZ > 10)
		cajasZ = 10;
}

