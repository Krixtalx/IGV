#include <cstdlib>
#include <stdio.h>
#include "igvInterfaz.h"
#include <iostream>

#define PI 3.14159265

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	// crear cámaras
	igvPunto3D p0 = igvPunto3D(15, 3, 15);
	igvPunto3D r = igvPunto3D(1, 0, 0);
	igvPunto3D V = igvPunto3D(0, 1.0, 0);

	interfaz.camara.set(IGV_PERSPECTIVA, p0, r, V,
		-1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200);


	//parámetros de la perspectiva
	interfaz.camara.angulo = 120.0;
	interfaz.camara.raspecto = 1.0;
	interfaz.luz = igvFuenteLuz(GL_LIGHT1, p0, { 0.1,0.1,0.1,1.0 }, { 1.0, 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 }, 1.0, 0, 0, r, 180, 2);
	interfaz.luz.aplicar();
}

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

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {

	float speed = 0.002f * interfaz.deltaTime;

	//std::cout << "PosCam: " << interfaz.camara.getPos()[0] << ", " << interfaz.camara.getPos()[1] << ", " << interfaz.camara.getPos()[2] << std::endl;
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
	case 'p': // cambia el tipo de proyección de paralela a perspectiva y viceversa
		interfaz.camara.cambiarTipoCamara();
		break;
	case 'P': // cambia el tipo de proyección de paralela a perspectiva y viceversa
		interfaz.camara.cambiarTipoCamara();
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

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());
	//visualiza la escena
	interfaz.escena.visualizar();

	// refresca la ventana
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

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

void igvInterfaz::set_glutTimerFunc(int value)
{
	float currentFrame = glutGet(GLUT_ELAPSED_TIME);
	interfaz.deltaTime = currentFrame - interfaz.lastFrame;
	interfaz.lastFrame = currentFrame;
	
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutTimerFunc(1000 / 60, set_glutTimerFunc, 0);
	glutPassiveMotionFunc(set_glutMotionFunc);
	glutSetCursor(GLUT_CURSOR_NONE);
}
