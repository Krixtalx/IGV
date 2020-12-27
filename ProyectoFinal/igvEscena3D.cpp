#include <cstdlib>
#include <stdio.h>
#include <iostream>

#include "igvEscena3D.h"
#include "Pared.h"
#include <stack>
#include "Mmsystem.h"



//==================== Constructor y destructor =======================

igvEscena3D::igvEscena3D() {
	ejes = false;
	matrizLaberinto = new int* [fil];
	for (unsigned i = 0; i < fil; i++)
	{
		matrizLaberinto[i] = new int[col];
		for (unsigned j = 0; j < col; j++)
		{
			matrizLaberinto[i][j] = 1;
		}
	}


	matrizLaberinto[fil - 2][col - 1] = 3;
	generarLaberinto();
	crearLaberinto();

	PlaySound(TEXT("avalanche.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}

igvEscena3D::~igvEscena3D() {
	for (unsigned i = 0; i < fil; i++)
	{
		delete matrizLaberinto[i];
	}
	delete[] matrizLaberinto;
	delete texParedes;
}


//==================== Metodos Laberinto =======================
// 0->Casilla libre
// 1->Muro
// 2->Casilla visitada solucion
// 3->Salida
void igvEscena3D::generarLaberinto()
{
	srand(semilla);

	std::pair<int, int> arriba(0, 1);
	std::pair<int, int> abajo(0, -1);
	std::pair<int, int> derecha(1, 0);
	std::pair<int, int> izquierda(-1, 0);
	std::pair<int, int> aux;
	std::vector<std::pair<int, int>> movimientos;
	std::stack<std::pair<int, int>> pila;
	unsigned posCol = 1, posFil = 1;
	float probSkip = 1;
	do {
		float aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (aleatorio < probSkip) {
			if (factible(posFil, posCol + 1))
				movimientos.push_back(arriba);
			if (factible(posFil, posCol - 1))
				movimientos.push_back(abajo);
			if (factible(posFil + 1, posCol))
				movimientos.push_back(derecha);
			if (factible(posFil - 1, posCol))
				movimientos.push_back(izquierda);
			probSkip -= 0.017;
		}

		if (movimientos.size() > 0) {
			aux = movimientos[rand() % movimientos.size()];
			posFil += aux.first;
			posCol += aux.second;
			pila.push(aux);
			matrizLaberinto[posFil][posCol] = 0;
		}
		else {
			probSkip = 1;
			while (movimientos.size() <= 0 && !pila.empty()) {
				aux = pila.top();
				pila.pop();
				posFil -= aux.first;
				posCol -= aux.second;
				if (factible(posFil, posCol + 1))
					movimientos.push_back(arriba);
				if (factible(posFil, posCol - 1))
					movimientos.push_back(abajo);
				if (factible(posFil + 1, posCol))
					movimientos.push_back(derecha);
				if (factible(posFil - 1, posCol))
					movimientos.push_back(izquierda);
			}
		}
		movimientos.clear();
	} while (!pila.empty());

	posCol = col - 2;
	posFil = fil - 2;
	while (matrizLaberinto[posFil][posCol] == 1) {
		matrizLaberinto[posFil][posCol] = 0;
		posFil--;
	}
}

void igvEscena3D::crearLaberinto()
{
	for (unsigned i = 0; i < fil; i++)
	{
		for (unsigned j = 0; j < col; j++)
		{
			if (matrizLaberinto[i][j] == 1)
				paredes.push_back(Pared({ (float)j + 0.5, 0.5, (float)i + 0.5 }, { 0,0,0 }));
			else if (matrizLaberinto[i][j] == 2)
				paredes.push_back(Pared({ (float)j + 0.5, -0.5, (float)i + 0.5 }, { 0,0,0 }, { 0,1,0,1.0 }));
			else if (matrizLaberinto[i][j] == 3)
				paredes.push_back(Pared({ (float)j + 0.5, -0.5, (float)i + 0.5 }, { 0,0,0 }, { 1,0,0,1.0 }));
			else if (matrizLaberinto[i][j] == 0)
				paredes.push_back(Pared({ (float)j + 0.5, -0.5, (float)i + 0.5 }, { 0,0,0 }, { 0,0,0,1.0 }));
		}
	}
	std::cout << "NumParedes: " << paredes.size() << std::endl;
}


bool igvEscena3D::factible(unsigned posFil, unsigned posCol)
{
	if (posFil < 1 || posFil >= (fil - 1) || posCol < 1 || posCol >= (col - 1))
		return false;
	if (matrizLaberinto[posFil][posCol] == 0)
		return false;

	int count = 0;
	if (matrizLaberinto[posFil + 1][posCol] == 0)
		count++;
	if (matrizLaberinto[posFil - 1][posCol] == 0)
		count++;
	if (matrizLaberinto[posFil][posCol + 1] == 0)
		count++;
	if (matrizLaberinto[posFil][posCol - 1] == 0)
		count++;
	if (count > 1)
		return false;
	return true;

}

//Metodo publico inicial
void igvEscena3D::resolverLaberinto()
{
	bool encontrado = false;
	resolverLaberinto(1, 1, encontrado);

	if (encontrado) {
		for (unsigned i = 0; i < fil; i++)
		{
			for (unsigned j = 0; j < col; j++)
			{
				if (matrizLaberinto[i][j] == 2)
					paredes.push_back(Pared({ (float)j + 0.5, 0.5, (float)i + 0.5 }, { 0,0,0 }, { 0,1,0,1.0 }));
			}
		}
	}
	resuelto = true;
	Pared::resuelto = true;
	glDisable(GL_TEXTURE_2D);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
}

//Lazo recursivo
void igvEscena3D::resolverLaberinto(unsigned posFil, unsigned posCol, bool& encontrado)
{
	if (matrizLaberinto[posFil][posCol] == 3)
		encontrado = true;
	else if (matrizLaberinto[posFil][posCol] != 1 && matrizLaberinto[posFil][posCol] != 2) {
		matrizLaberinto[posFil][posCol] = 2;
		if (!encontrado)
			resolverLaberinto(posFil + 1, posCol, encontrado);
		if (!encontrado)
			resolverLaberinto(posFil, posCol + 1, encontrado);
		if (!encontrado)
			resolverLaberinto(posFil - 1, posCol, encontrado);
		if (!encontrado)
			resolverLaberinto(posFil, posCol - 1, encontrado);
		if (!encontrado)
			matrizLaberinto[posFil][posCol] = 0;
	}
}


void igvEscena3D::mostrarLaberinto()
{
	for (unsigned i = 0; i < fil; i++)
	{
		for (unsigned j = 0; j < col; j++)
		{
			std::cout << matrizLaberinto[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//===========================================================================================
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
	if (!texParedes)
		texParedes = new igvTextura("128.png");
	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();
	
	for (Pared pared : paredes)
	{
		pared.dibujar();
	}

	glPopMatrix(); // restaura la matriz de modelado
}

void igvEscena3D::comprobarColision(igvPunto3D current, igvPunto3D& target)
{
	int posX, posZ;
	posX = target[X] / Pared::tam;
	posZ = target[Z] / Pared::tam;
	
	//std::cout << "PosX: " << posX << " PosZ: " << posZ << std::endl;
	if (posX<0 || posZ<0 || matrizLaberinto[posZ][posX] == 1)
	{
		target = current;
	}
}


const unsigned igvEscena3D::getCol()
{
	return col;
}

const unsigned igvEscena3D::getFil()
{
	return fil;
}