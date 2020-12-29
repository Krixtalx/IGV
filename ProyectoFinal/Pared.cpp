#include "Pared.h"
#include "igvMaterial.h"
#include "igvTextura.h"
#include <string>
#include <iostream>

#define PI 3.14159265

int Pared::tam = 10;
bool Pared::resuelto = false;

Pared::Pared(igvPunto3D posicion, igvPunto3D rotacion, igvColor color) : posicion(posicion), rotacion(rotacion), escalado({ 1,1,1 }), color(color)
{
}

//Funcion encargada de dibujar la pared
void Pared::dibujar()
{
	glPushMatrix();
	if (!resuelto) {
		igvMaterial material(Ka, Kd, Ks, Ns);
		material.aplicar();
	}
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, color.cloneToFloatArray());

	glTranslatef(posicion[X] * tam, posicion[Y] * tam, posicion[Z] * tam); //Aplicamos la translacion
	glRotatef(rotacion[X], 1, 0, 0); //Aplicamos las rotaciones
	glRotatef(rotacion[Y], 0, 1, 0);
	glRotatef(rotacion[Z], 0, 0, 1);
	glScalef(escalado[X], escalado[Y], escalado[Z]); //Aplicamos el escalado exclusivamente al objeto de este nodo
	crearQuad(); //Creamos nuestro cubo
	glPopMatrix(); //Restauramos la matriz de modelado guardada sin el escalado
}

//====================================================================================================================

//Funcion encargada de crear el quad con la textura. Es usada por la funcion dibujar
void Pared::crearQuad()
{
	float ini = -Pared::tam / 2;
	int div = 10;
	float inc = (float)Pared::tam / div;
	float inc_tex = (float)1 / div;

	glNormal3f(1, 0, 0);//Cara derecha
	for (int i = 0; i < div; i++)
	{
		for (int j = 0; j < div; j++)
		{
			glBegin(GL_QUADS);
			glTexCoord2f(i * inc_tex, j * inc_tex);
			glVertex3f(Pared::tam / 2, ini + i * inc, ini + j * inc);

			glTexCoord2f(i * inc_tex, (j + 1) * inc_tex);
			glVertex3f(Pared::tam / 2, ini + i * inc, ini + (j + 1) * inc);

			glTexCoord2f((i + 1) * inc_tex, (j + 1) * inc_tex);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + (j + 1) * inc);

			glTexCoord2f((i + 1) * inc_tex, j * inc_tex);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + j * inc);

			glEnd();
		}
	}

	glPushMatrix();
	glNormal3f(1, 0, 0);
	glRotated(90, 0, 0, 1); //CaraSuperior
	for (int i = 0; i < div; i++)
	{
		for (int j = 0; j < div; j++)
		{
			glBegin(GL_QUADS);

			glVertex3f(Pared::tam / 2, ini + i * inc, ini + j * inc);
			glVertex3f(Pared::tam / 2, ini + i * inc, ini + (j + 1) * inc);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + (j + 1) * inc);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + j * inc);

			glEnd();
		}
	}
	glPopMatrix();
	
	glPushMatrix();
	glNormal3f(1, 0, 0);
	glRotated(90, 0, 1, 0); //Cara frontal
	for (int i = 0; i < div; i++)
	{
		for (int j = 0; j < div; j++)
		{
			glBegin(GL_QUADS);

			glTexCoord2f(i * inc_tex, j * inc_tex);
			glVertex3f(Pared::tam / 2, ini + i * inc, ini + j * inc);

			glTexCoord2f(i * inc_tex, (j + 1) * inc_tex);
			glVertex3f(Pared::tam / 2, ini + i * inc, ini + (j + 1) * inc);

			glTexCoord2f((i + 1) * inc_tex, (j + 1) * inc_tex);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + (j + 1) * inc);

			glTexCoord2f((i + 1) * inc_tex, j * inc_tex);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + j * inc);

			glEnd();
		}
	}
	glPopMatrix();


	glPushMatrix();
	glNormal3f(1, 0, 0);
	glRotated(-90, 0, 1, 0); //Cara trasera
	for (int i = 0; i < div; i++)
	{
		for (int j = 0; j < div; j++)
		{
			glBegin(GL_QUADS);

			glTexCoord2f(i * inc_tex, j * inc_tex);
			glVertex3f(Pared::tam / 2, ini + i * inc, ini + j * inc);

			glTexCoord2f(i * inc_tex, (j + 1) * inc_tex);
			glVertex3f(Pared::tam / 2, ini + i * inc, ini + (j + 1) * inc);

			glTexCoord2f((i + 1) * inc_tex, (j + 1) * inc_tex);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + (j + 1) * inc);

			glTexCoord2f((i + 1) * inc_tex, j * inc_tex);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + j * inc);

			glEnd();
		}
	}
	glPopMatrix();


	glPushMatrix();
	glNormal3f(-1, 0, 0);
	glTranslatef(-Pared::tam, 0, 0); //Cara izquierda
	for (int i = 0; i < div; i++)
	{
		for (int j = 0; j < div; j++)
		{
			glBegin(GL_QUADS);

			glTexCoord2f(i * inc_tex, j * inc_tex);
			glVertex3f(Pared::tam / 2, ini + i * inc, ini + j * inc);

			glTexCoord2f(i * inc_tex, (j + 1) * inc_tex);
			glVertex3f(Pared::tam / 2, ini + i * inc, ini + (j + 1) * inc);

			glTexCoord2f((i + 1) * inc_tex, (j + 1) * inc_tex);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + (j + 1) * inc);

			glTexCoord2f((i + 1) * inc_tex, j * inc_tex);
			glVertex3f(Pared::tam / 2, ini + (i + 1) * inc, ini + j * inc);

			glEnd();
		}
	}
	glPopMatrix();
}
