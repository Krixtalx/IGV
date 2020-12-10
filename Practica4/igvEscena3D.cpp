#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"

// Metodos constructores 

igvEscena3D::igvEscena3D () {
	ejes = true;

}

igvEscena3D::~igvEscena3D() {
}


// Metodos publicos 

void pintar_ejes(void) {
  GLfloat rojo[]={1,0,0,1.0};
  GLfloat verde[]={0,1,0,1.0};
  GLfloat azul[]={0,0,1,1.0};

  glMaterialfv(GL_FRONT,GL_EMISSION,rojo);
	glBegin(GL_LINES);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);
	glEnd();

  glMaterialfv(GL_FRONT,GL_EMISSION,verde);
	glBegin(GL_LINES);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);
	glEnd();

  glMaterialfv(GL_FRONT,GL_EMISSION,azul);
	glBegin(GL_LINES);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();
}


void pintar_quad(float div_x, float div_z) {
	float ini_x = 0.0;
	float ini_z = 0.0;
	float tam_x = 5.0;
	float tam_z = 5.0;

	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
		glVertex3f(ini_x , 0.0, ini_z);
		glVertex3f(ini_x , 0.0, ini_z + tam_z);
		glVertex3f(ini_x + tam_x, 0.0, ini_z + tam_z);
		glVertex3f(ini_x + tam_x, 0.0, ini_z);
	glEnd();
}


void igvEscena3D::visualizar(void) {
	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

		// se pintan los ejes
	  if (ejes) pintar_ejes();

		// luces se aplican antes de las transformaciones a la escena para que permanezcan fijas

		// APARTADO B: Define y aplica la luz puntual especificada en el guión de prácticas


		// APARTADO F: Define y aplica la luz tipo foco especificada en el guión de prácticas
	

		/* Apartado D: definir y aplicar las propiedades de material indicadas en el guión de prácticas */
		/* Apartado E: sustituir los valores correspondientes a la componente R del coeficiende difuso, 
		               la componente R del coeficiente especular y el exponente de Phong, por el valor
									 del atributo correspondiente de la clase igvEscena */


		/* Apartado G: Añade aquí la creación del objeto textura y su aplicación */


		pintar_quad(1, 1);



	glPopMatrix (); // restaura la matriz de modelado
}
