#include <cstdlib>
#include <stdio.h>
#include "igvInterfaz.h"
#include <iostream>

#include "Mmsystem.h"

#define PI 3.14159265

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

//==================== Constructor y destructor =======================

igvInterfaz::igvInterfaz() {
	modo = IGV_VISUALIZAR;
	boton_retenido = false;
}

igvInterfaz::~igvInterfaz() {}


//==================== Metodos auxiliares de inicializacion =======================

void igvInterfaz::crear_mundo(void) {
	// crear cámaras
	igvPunto3D p0 = igvPunto3D(15, 3, 15);
	igvPunto3D r = igvPunto3D(1, 0, 0);
	igvPunto3D V = igvPunto3D(0, 1.0, 0);

	interfaz.camara.set(IGV_PERSPECTIVA, p0, r, V,
		-1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200);


	//parámetros de la perspectiva
	interfaz.camara.angulo = 120.0;
	interfaz.camara.raspecto = (double)interfaz.ancho_ventana/interfaz.alto_ventana;
	interfaz.luz = igvFuenteLuz(GL_LIGHT0, p0, { 0.1,0.1,0.1,1.0 }, { 1.0, 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 }, 1.0, 0, 0, r, 65, 2);
	interfaz.luz.aplicar();
}

//===========================================================================================

void igvInterfaz::configura_entorno(int argc, char** argv,
	int _ancho_ventana, int _alto_ventana,
	int _pos_X, int _pos_Y,
	string _titulo) {
	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana, _alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(0, 0, 0, 0.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	glShadeModel(GL_SMOOTH);

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

//===========================================================================================

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutTimerFunc(1000/60, set_glutTimerFunc, 0);
	glutMouseFunc(set_glutMouseFunc);
	glutPassiveMotionFunc(set_glutMotionFunc);
	glutSetCursor(GLUT_CURSOR_NONE);
}


void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

//==================== Implementacion de los metodos callback =======================

//Metodo encargado del manejo de teclado
void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {

	float speed = 0.015f * interfaz.deltaTime;
	igvPunto3D target; 
	switch (key) {
	case 'w':
		target = interfaz.camara.getPos() + interfaz.camara.getRef() * speed;
		interfaz.escena.comprobarColision(interfaz.camara.getPos(), target);
		interfaz.camara.setPos(target);
		interfaz.luz.setPosicion(target);
		break;
	case 'a':
		target = interfaz.camara.getPos() - (interfaz.camara.getRef().cross(interfaz.camara.getV()).normalize()) * speed;
		interfaz.escena.comprobarColision(interfaz.camara.getPos(), target);
		interfaz.camara.setPos(target);
		interfaz.luz.setPosicion(target);
		break;
	case 's':
		target = interfaz.camara.getPos() - interfaz.camara.getRef() * speed;
		interfaz.escena.comprobarColision(interfaz.camara.getPos(), target);
		interfaz.camara.setPos(target);
		interfaz.luz.setPosicion(target);
		break;
	case 'd':
		target = interfaz.camara.getPos() + (interfaz.camara.getRef().cross(interfaz.camara.getV()).normalize()) * speed;
		interfaz.escena.comprobarColision(interfaz.camara.getPos(), target);
		interfaz.camara.setPos(target);
		interfaz.luz.setPosicion(target);
		break;
	case 'r':
		target = interfaz.camara.getPos();
		interfaz.escena.resolverLaberinto(target[Z]/Pared::tam, target[X] / Pared::tam);
		interfaz.camara.setPosPlanta({ (float)interfaz.escena.getFil() * 10 / 2, 20, (float)interfaz.escena.getCol() * 10 / 2 });
		interfaz.camara.cambiarVista(0);
		interfaz.luz.apagar();
		interfaz.luz.aplicar();
		break;
	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision y redibuja la escena
}

//===========================================================================================

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}

//===========================================================================================

void igvInterfaz::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());
	if (interfaz.modo == IGV_SELECCIONAR) {
		glDisable(GL_LIGHTING); // desactiva la iluminacion de la escena
		glDisable(GL_DITHER);
		glDisable(GL_TEXTURE_2D);

		interfaz.escena.visualizar();

		GLubyte pixel[3];
		glReadPixels(interfaz.ancho_ventana/2, interfaz.alto_ventana/2, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
		
		
		GLubyte pixelEsfera[3];
		pixelEsfera[0] = (GLubyte)(0.9 * 255);
		pixelEsfera[1] = (GLubyte)(0.9 * 255);
		pixelEsfera[2] = (GLubyte)(0.9 * 255);
		if (pixelEsfera[0] == pixel[0] && pixelEsfera[1] == pixel[1] && pixelEsfera[2] == pixel[2]) {
			interfaz.escena.abrirPuerta();
			cout << "Se ha abierto la salida" << std::endl;
		}

		interfaz.modo = IGV_VISUALIZAR;
		
		glEnable(GL_LIGHTING);
		glEnable(GL_DITHER);
		glEnable(GL_TEXTURE_2D);

	}
	else {
		//visualiza la escena
		interfaz.escena.visualizar();
		// refresca la ventana
		glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
	}
	
}

//===========================================================================================

//Funcion encargada de la gestión del movimiento del raton
void igvInterfaz::set_glutMotionFunc(GLint x, GLint y) {

	if (interfaz.primero)
	{
		interfaz.cursorX = x;
		interfaz.cursorY = y;
		interfaz.primero = false;
	}

	if (!Pared::resuelto) {
		interfaz.movX = x - interfaz.cursorX;
		interfaz.cursorX = x;

		interfaz.movY = interfaz.cursorY - y;
		interfaz.cursorY = y;

		interfaz.yaw += interfaz.movX;
		interfaz.pitch += interfaz.movY;

		if (interfaz.pitch > 89.0f)
			interfaz.pitch = 89.0f;
		if (interfaz.pitch < -89.0f)
			interfaz.pitch = -89.0f;

		glutPostRedisplay();

		igvPunto3D direccion;
		direccion[X] = cos(interfaz.yaw * PI / 180) * cos(interfaz.pitch * PI / 180);
		direccion[Y] = sin(interfaz.pitch * PI / 180);
		direccion[Z] = sin(interfaz.yaw * PI / 180) * cos(interfaz.pitch * PI / 180);
		direccion.normalize();

		//std::cout << "Direccion: " << direccion[0] << ", " << direccion[1] << ", " << direccion[2] << std::endl;

		interfaz.camara.setPosApuntado(direccion);
		interfaz.luz.setDireccionFoco(direccion);
		interfaz.luz.aplicar();
		interfaz.camara.aplicar();

		if (x < 100 || x > interfaz.ancho_ventana - 100) {  
			interfaz.cursorX = interfaz.ancho_ventana / 2;  
			interfaz.cursorY = interfaz.alto_ventana / 2;
			glutWarpPointer(interfaz.alto_ventana / 2, interfaz.alto_ventana / 2);
		}
		else if (y < 100 || y > interfaz.alto_ventana - 100) {
			interfaz.cursorX = interfaz.ancho_ventana / 2;
			interfaz.cursorY = interfaz.alto_ventana / 2;
			glutWarpPointer(interfaz.alto_ventana / 2, interfaz.alto_ventana / 2);
		}
	}
}

//===========================================================================================

//Funcion encargada de gestionar el click del raton
void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y) {

	// Apartado A: comprobar que se ha pulsado el botón izquierdo
	if (boton == GLUT_LEFT_BUTTON && !interfaz.boton_retenido) {
		interfaz.boton_retenido = !interfaz.boton_retenido;
		// Apartado A: guardar que el boton se ha presionado o se ha soltado, si se ha pulsado hay que
		// pasar a modo IGV_SELECCIONAR
		interfaz.modo = IGV_SELECCIONAR;

		// Apartado A: renovar el contenido de la ventana de vision
		glutPostRedisplay();
	}
	else if (interfaz.boton_retenido) {
		interfaz.boton_retenido = !interfaz.boton_retenido;
	}
}

//===========================================================================================

//Funcion que se llama cada 16,666 ms para actualizar el deltaTime.
void igvInterfaz::set_glutTimerFunc(int value)
{
	float currentFrame = glutGet(GLUT_ELAPSED_TIME);
	interfaz.deltaTime = currentFrame - interfaz.lastFrame;
	interfaz.lastFrame = currentFrame;
	glutTimerFunc(1000 / 60, set_glutTimerFunc, 0);
}




