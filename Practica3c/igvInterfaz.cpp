#include <cstdlib>
#include <stdio.h>
#include <vector>
#include "igvInterfaz.h"

using namespace std;

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {
	modo = IGV_VISUALIZAR;
	objeto_seleccionado = -1;
	boton_retenido = false;
}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {

	p0 = igvPunto3D(10.0, 4.0, 10.0);
	r = igvPunto3D(0, 0, 0);
	V = igvPunto3D(0, 1.0, 0);

	interfaz.camara.set(IGV_PERSPECTIVA, p0, r, V, 60, 4.0 / 3.0, 1, 100);
}

void igvInterfaz::configura_entorno(int argc, char** argv,
	int _ancho_ventana, int _alto_ventana,
	int _pos_X, int _pos_Y,
	string _titulo) {
	// inicializaci�n de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicializaci�n de la ventana de visualizaci�n
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana, _alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
		interfaz.escena.addCajaX(1);
		break;
	case 'X':
		interfaz.escena.addCajaX(-1);
		break;
	case 'z':
		interfaz.escena.addCajaZ(1);
		break;
	case 'Z':
		interfaz.escena.addCajaZ(-1);
		break;
	case 'y':
		interfaz.escena.addCajaY(1);
		break;
	case 'Y':
		interfaz.escena.addCajaY(-1);
		break;

	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los par�metros de la c�mara y de la proyecci�n
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

	// Apartado A: antes de aplicar las transformaciones de c�mara y proyecci�n hay que comprobar el modo para s�lo visualizar o seleccionar:
	if (interfaz.modo == IGV_SELECCIONAR) {
		// Apartado A: Para que funcione habr� que dibujar la escena sin efectos, sin iluminaci�n, sin texturas ...
		glDisable(GL_LIGHTING); // desactiva la iluminacion de la escena
		glDisable(GL_DITHER);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);

		igvCaja::visualizando = false;
		std::cout << "Seleccionando" << std::endl;
		// Apartado A: Reestablece los colores como no seleccionado
		if (interfaz.objeto_seleccionado >= 0)
			interfaz.escena.getCajas()[interfaz.objeto_seleccionado]->setSeleccionado();

		// Apartado A: aplica la c�mara
		interfaz.camara.aplicar();

		// Apartado A: visualiza los BV cada uno de un color
		interfaz.escena.visualizarVB();

		// Apartado A: Obtener el color del pixel seleccionado
		GLubyte pixel[3];
		glReadPixels(interfaz.cursorX, interfaz.alto_ventana - interfaz.cursorY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

		// Apartado A: Comprobar el color del objeto que hay en el cursor mirando en la tabla de colores y asigna otro color al objeto seleccionado
		interfaz.objeto_seleccionado = interfaz.escena.encontrar(pixel);

		if (interfaz.objeto_seleccionado >= 0) {
			interfaz.escena.getCajas()[interfaz.objeto_seleccionado]->setSeleccionado();
		}
		else
			std::cerr << "No se ha podido seleccionar el objeto" << std::endl;
		// Apartado A: Cambiar a modo de visualizaci�n de la escena
		interfaz.modo = IGV_VISUALIZAR;
		igvCaja::visualizando = true;

		// Apartado A: Habilitar de nuevo la iluminaci�n
		glEnable(GL_LIGHTING);
	}
	else {
		std::cout << "Visualizando" << std::endl;
		if (interfaz.objeto_seleccionado >= 0) {
			interfaz.escena.getCajas()[interfaz.objeto_seleccionado]->addRotacion(interfaz.movX);
		}
		// aplica las transformaciones en funci�n de los par�metros de la c�mara
		interfaz.camara.aplicar();
		// visualiza la escena
		interfaz.escena.visualizar();

		// refresca la ventana
		glutSwapBuffers();
	}
}

void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y) {

	// Apartado A: comprobar que se ha pulsado el bot�n izquierdo
	if (boton == GLUT_LEFT_BUTTON && !interfaz.boton_retenido) {
		interfaz.boton_retenido = !interfaz.boton_retenido;
		// Apartado A: guardar que el boton se ha presionado o se ha soltado, si se ha pulsado hay que
		// pasar a modo IGV_SELECCIONAR
		interfaz.modo = IGV_SELECCIONAR;
		// Apartado A: guardar el pixel pulsado
		interfaz.cursorX = x;
		interfaz.cursorY = y;

		// Apartado A: renovar el contenido de la ventana de vision
		glutPostRedisplay();
	}
	else if (interfaz.boton_retenido) {
		interfaz.boton_retenido = !interfaz.boton_retenido;
	}

	std::cout << "Boton izq: " << interfaz.boton_retenido << std::endl;
}

void igvInterfaz::set_glutMotionFunc(GLint x, GLint y) {

	// Apartado B: si el bot�n est� retenido y hay alg�n objeto seleccionado,
	// comprobar el objeto seleccionado y la posici�n del rat�n y rotar
	// el objeto seleccionado utilizando el desplazamiento entre la posici�n 
	//inicial y final del rat�n

	// Apartado B: guardar la nueva posici�n del rat�n 
	interfaz.movX = x - interfaz.cursorX;
	interfaz.cursorX = x;

	// Apartado B: renovar el contenido de la ventana de vision 
	glutPostRedisplay();

}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);

	glutMouseFunc(set_glutMouseFunc);
	glutMotionFunc(set_glutMotionFunc);
}

