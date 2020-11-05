#include "igvCilindro.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265

igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV) //DivU -> Numero de espacios.  DivV -> Numero de zonas
{
	/* Apartado B: Construir la malla de triángulos para representar el cilindro */

	num_vertices = (divU) * (divV + 1);
	vertices = new float[num_vertices * 3];
	/* Apartado C: Añadir el vector de normales */
	normales = new float[num_vertices * 3];
	double radianUnitario = 2 * PI / divU;

	a /= divV;

	double posX, posZ;
	int posVertice;

	for (int i = 0; i < divU; i++)
	{
		posX = sin(radianUnitario * i) * r;
		posZ = cos(radianUnitario * i) * r;
		for (int j = 0; j <= divV; j++)
		{
			posVertice = ((j * divU) + i) * 3;

			vertices[posVertice] = posX; //Eje x
			vertices[posVertice + 1] = a * j; //Eje y
			vertices[posVertice + 2] = posZ; //Eje z


			normales[posVertice] = posX / r;
			normales[posVertice + 1] = 0.0;
			normales[posVertice + 2] = posZ / r;


			std::cout << "Vertice " << posVertice / 3 << ": " << vertices[posVertice] << ", " << vertices[posVertice + 1] << ", " << vertices[posVertice + 2] << std::endl;

		}
	}

	num_triangulos = divU * 2 * divV;
	triangulos = new unsigned int[num_triangulos * 3];

	int posActual;

	for (int i = 0; i < divV; i++)
	{
		for (int j = 0; j < divU; j++)
		{
			posActual = i * (divU * 6) + j * 6;

			triangulos[posActual] = j + (i + 1) * divU;
			triangulos[posActual + 1] = (j + 1) % divU + (i + 1) * divU;
			triangulos[posActual + 2] = j + i * divU;
			std::cout << "Triangulo " << posActual / 3 << ": " << triangulos[posActual] << ", " << triangulos[posActual + 1] << ", " << triangulos[posActual + 2] << std::endl;

			triangulos[posActual + 3] = (j + 1) % divU + (i + 1) * divU;
			triangulos[posActual + 4] = (j + 1) % divU + i * divU;
			triangulos[posActual + 5] = j + i * divU;

			std::cout << "Triangulo " << (posActual + 3) / 3 << ": " << triangulos[posActual + 3] << ", " << triangulos[posActual + 4] << ", " << triangulos[posActual + 5] << std::endl;
		}
	}


}

igvCilindro::~igvCilindro()
{
}
