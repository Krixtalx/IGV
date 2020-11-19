#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

using namespace std;

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {

}

igvInterfaz::~igvInterfaz() {}

// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {

	// crear cámaras
	p0 = igvPunto3D(6.0, 4.0, 8);
	r = igvPunto3D(0, 0, 0);
	V = igvPunto3D(0, 1.0, 0);

	interfaz.camara.set(IGV_PARALELA, p0, r, V,
		-1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200);

	//parámetros de la perspectiva
	interfaz.camara.angulo = 60.0;
	interfaz.camara.raspecto = 1.0;
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
		////// Apartado C: incluir aquí la modificación de los grados de libertad del modelo pulsando las teclas correspondientes
	case '1':
		interfaz.escena.setSeleccionado("Cintura");
		std::cout << "Seleccionado el nodo " << interfaz.escena.getNombreNodoSel() << std::endl;
		break;
	case '2':
		interfaz.escena.setSeleccionado("Tronco");
		std::cout << "Seleccionado el nodo " << interfaz.escena.getNombreNodoSel() << std::endl;
		break;
	case '3':
		interfaz.escena.setSeleccionado("Cabeza");
		std::cout << "Seleccionado el nodo " << interfaz.escena.getNombreNodoSel() << std::endl;
		break;
	case '4':
		interfaz.escena.setSeleccionado("HombroDer");
		std::cout << "Seleccionado el nodo " << interfaz.escena.getNombreNodoSel() << std::endl;
		break;
	case '5':
		interfaz.escena.setSeleccionado("HombroIzq");
		std::cout << "Seleccionado el nodo " << interfaz.escena.getNombreNodoSel() << std::endl;
		break;
	case '6':
		interfaz.escena.setSeleccionado("PiernaDer");
		std::cout << "Seleccionado el nodo " << interfaz.escena.getNombreNodoSel() << std::endl;
		break;
	case '7':
		interfaz.escena.setSeleccionado("PiernaIzq");
		std::cout << "Seleccionado el nodo " << interfaz.escena.getNombreNodoSel() << std::endl;
		break;
	case '8':
		interfaz.escena.setSeleccionado("PiernaDer2");
		std::cout << "Seleccionado el nodo " << interfaz.escena.getNombreNodoSel() << std::endl;
		break;
	case '9':
		interfaz.escena.setSeleccionado("PiernaIzq2");
		std::cout << "Seleccionado el nodo " << interfaz.escena.getNombreNodoSel() << std::endl;
		break;
	case 'x':
		interfaz.escena.modificarAnguloSeleccionado({ 5,0,0 });
		break;
	case 'X':
		interfaz.escena.modificarAnguloSeleccionado({ -5,0,0 });
		break;
	case 'y':
		interfaz.escena.modificarAnguloSeleccionado({ 0,5,0 });
		break;
	case 'Y':
		interfaz.escena.modificarAnguloSeleccionado({ 0,-5,0 });
		break;
	case 'z':
		interfaz.escena.modificarAnguloSeleccionado({ 0,0,5 });
		break;
	case 'Z':
		interfaz.escena.modificarAnguloSeleccionado({ 0,0,-5 });
		break;
	case 'a':
		interfaz.idle = !interfaz.idle;
		break;

		////// Apartado C: incluir aquí el cambio de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva 
	case 'p': // cambia el tipo de proyección de paralela a perspectiva y viceversa
		interfaz.camara.cambiarTipoCamara();
		break;
	case 'P': // cambia el tipo de proyección de paralela a perspectiva y viceversa
		interfaz.camara.cambiarTipoCamara();
		break;
	case 'v': // cambia la posición de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva
		interfaz.camara.cambiarVista();
		break;
	case 'V': // dividir la ventana  en cuatro vistas
		interfaz.vistas = !interfaz.vistas;
		break;
	case '+': // zoom in
		interfaz.camara.zoom(0.05);
		break;
	case '-': // zoom out
		interfaz.camara.zoom(-0.05);
		break;
	case 'n': // incrementar la distancia del plano cercano
		interfaz.camara.znear += 0.2;
		interfaz.camara.aplicar();
		break;
	case 'N': // decrementar la distancia del plano cercano
		interfaz.camara.znear -= 0.2;
		interfaz.camara.aplicar();
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

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
	// se establece el viewport
	if (interfaz.vistas) {

		glViewport(0, 0, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2);
		interfaz.camara.cambiarVista(0);
		interfaz.escena.visualizar();
		glViewport(interfaz.get_ancho_ventana() / 2, 0, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2);
		interfaz.camara.cambiarVista(1);
		interfaz.escena.visualizar();
		glViewport(interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2);
		interfaz.camara.cambiarVista(2);
		interfaz.escena.visualizar();
		glViewport(0, interfaz.get_alto_ventana() / 2, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2);
		interfaz.camara.cambiarVista(3);
		interfaz.escena.visualizar();
	}
	else {
		glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());
		//visualiza la escena
		interfaz.escena.visualizar();
	}
	// refresca la ventana
	glutSwapBuffers();
}

void igvInterfaz::set_glutIdleFunc() {
	///// Apartado D: incluir el código para animar el modelo de la manera más realista posible
	if (interfaz.idle) {
		int pasosFase1 = (15 / interfaz.velocidadAnim); //15 grados por fase con velocidadAnim.
		int pasosFase1_2 = pasosFase1 + (15 / interfaz.velocidadAnim);
		int pasosFase1_3 = pasosFase1_2 + (15 / interfaz.velocidadAnim);
		int pasosFase1_4 = pasosFase1_3 + (30 / interfaz.velocidadAnim);
		int pasosFase2 = pasosFase1_4 + (30 / interfaz.velocidadAnim);
		int pasosFase3 = pasosFase2 + (10 / interfaz.velocidadAnim);
		int pasosFase4 = pasosFase3 + (10 / interfaz.velocidadAnim);
		int pasosFase5 = pasosFase4 + (10 / interfaz.velocidadAnim);
		int pasosFase6 = pasosFase5 + (10 / interfaz.velocidadAnim);
		int pasosFase7 = pasosFase6 + (30 / interfaz.velocidadAnim);

		if (interfaz.paso == -1) { //Inicializamos la animación
			interfaz.bucleCaminarBackUp = interfaz.bucleCaminar;
			interfaz.escena.resetearModelo();
			interfaz.escena.setSeleccionado("Cintura");
			interfaz.escena.modificarPosicionSeleccionado({ 0,0,(-4.0 * interfaz.bucleCaminar) });
		}
		//Loop Caminar
		else if (interfaz.paso < pasosFase1) {
			interfaz.escena.setSeleccionado("PiernaDer");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim * 2, 0, 0 });
			interfaz.escena.setSeleccionado("PiernaDer2");
			interfaz.escena.modificarAnguloSeleccionado({ interfaz.velocidadAnim * 2, 0, 0 });
			interfaz.escena.setSeleccionado("PieDer");
			interfaz.escena.modificarAnguloSeleccionado({ interfaz.velocidadAnim, 0, 0 });

			interfaz.escena.setSeleccionado("Cintura");
			interfaz.escena.modificarPosicionSeleccionado({ 0,0,interfaz.velocidadAnim / 12 });

			interfaz.escena.setSeleccionado("PiernaIzq");
			interfaz.escena.modificarAnguloSeleccionado({ interfaz.velocidadAnim * 2, 0, 0 });
			interfaz.escena.setSeleccionado("PiernaIzq2");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim / 2, 0, 0 });
			interfaz.escena.setSeleccionado("PieIzq");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim / 2, 0, 0 });
		}
		else if (interfaz.paso < pasosFase1_2) {
			interfaz.escena.setSeleccionado("Cintura");
			interfaz.escena.modificarPosicionSeleccionado({ 0,0,interfaz.velocidadAnim / 12 });

			interfaz.escena.setSeleccionado("PiernaDer");
			interfaz.escena.modificarAnguloSeleccionado({ interfaz.velocidadAnim * 4, 0, 0 });
			interfaz.escena.setSeleccionado("PiernaDer2");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim * 4, 0, 0 });
			interfaz.escena.setSeleccionado("PieDer");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim * 2, 0, 0 });

			interfaz.escena.setSeleccionado("PiernaIzq");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim * 4, 0, 0 });
			interfaz.escena.setSeleccionado("PiernaIzq2");
			interfaz.escena.modificarAnguloSeleccionado({ interfaz.velocidadAnim * 2, 0, 0 });
			interfaz.escena.setSeleccionado("PieIzq");
			interfaz.escena.modificarAnguloSeleccionado({ interfaz.velocidadAnim * 2, 0, 0 });
		}
		else if (interfaz.paso < pasosFase1_3) {
			interfaz.escena.setSeleccionado("Cintura");
			interfaz.escena.modificarPosicionSeleccionado({ 0,0,interfaz.velocidadAnim / 12 });

			interfaz.escena.setSeleccionado("PiernaDer");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim * 2, 0, 0 });
			interfaz.escena.setSeleccionado("PiernaDer2");
			interfaz.escena.modificarAnguloSeleccionado({ interfaz.velocidadAnim, 0, 0 });
			interfaz.escena.setSeleccionado("PieDer");
			interfaz.escena.modificarAnguloSeleccionado({ interfaz.velocidadAnim, 0, 0 });

			interfaz.escena.setSeleccionado("PiernaIzq");
			interfaz.escena.modificarAnguloSeleccionado({ interfaz.velocidadAnim * 2, 0, 0 });
			interfaz.escena.setSeleccionado("PiernaIzq2");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim * 1.5f, 0, 0 });
			interfaz.escena.setSeleccionado("PieIzq");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim * 1.5f, 0, 0 });
		}
		else if (interfaz.bucleCaminar > 1) {
			interfaz.bucleCaminar--;
			interfaz.paso = -1;
		}


		//Loop Saludo
		else if (interfaz.paso < pasosFase1_4) {
			interfaz.escena.setSeleccionado("Tronco");
			interfaz.escena.modificarAnguloSeleccionado({ 0, interfaz.velocidadAnim, 0 });
			interfaz.escena.setSeleccionado("Cabeza");
			interfaz.escena.modificarAnguloSeleccionado({ -interfaz.velocidadAnim * 2 / 3, interfaz.velocidadAnim / 6, 0 });
		}
		else if (interfaz.paso < pasosFase2) {
			interfaz.escena.setSeleccionado("HombroDer");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim * 5.5f });
			interfaz.escena.setSeleccionado("HombroIzq");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, interfaz.velocidadAnim * 5.5f });
		}
		else if (interfaz.paso < pasosFase3) {
			interfaz.escena.setSeleccionado("HombroDer");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, interfaz.velocidadAnim * 4 });
			interfaz.escena.setSeleccionado("HombroIzq");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim * 4 });
			interfaz.escena.setSeleccionado("Tronco");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim / 2 });
			interfaz.escena.setSeleccionado("Cabeza");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, interfaz.velocidadAnim });
		}
		else if (interfaz.paso < pasosFase4) {
			interfaz.escena.setSeleccionado("HombroDer");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim * 4 });
			interfaz.escena.setSeleccionado("HombroIzq");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, +interfaz.velocidadAnim * 4 });
			interfaz.escena.setSeleccionado("Tronco");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, interfaz.velocidadAnim });
			interfaz.escena.setSeleccionado("Cabeza");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim * 2 });
		}
		else if (interfaz.paso < pasosFase5) {
			interfaz.escena.setSeleccionado("HombroDer");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, interfaz.velocidadAnim * 4 });
			interfaz.escena.setSeleccionado("HombroIzq");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim * 4 });
			interfaz.escena.setSeleccionado("Tronco");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim });
			interfaz.escena.setSeleccionado("Cabeza");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, interfaz.velocidadAnim * 2 });
		}
		else if (interfaz.paso < pasosFase6) {
			interfaz.escena.setSeleccionado("HombroDer");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim * 4 });
			interfaz.escena.setSeleccionado("HombroIzq");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, +interfaz.velocidadAnim * 4 });
			interfaz.escena.setSeleccionado("Tronco");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, interfaz.velocidadAnim });
			interfaz.escena.setSeleccionado("Cabeza");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim * 2 });
		}
		else if (interfaz.paso < pasosFase7) {
			interfaz.escena.setSeleccionado("HombroDer");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, +interfaz.velocidadAnim * 5.5f });
			interfaz.escena.setSeleccionado("HombroIzq");
			interfaz.escena.modificarAnguloSeleccionado({ 0, 0, -interfaz.velocidadAnim * 5.5f });
			interfaz.escena.setSeleccionado("Tronco");
			interfaz.escena.modificarAnguloSeleccionado({ 0, -interfaz.velocidadAnim, -interfaz.velocidadAnim / 6 });
			interfaz.escena.setSeleccionado("Cabeza");
			interfaz.escena.modificarAnguloSeleccionado({ +interfaz.velocidadAnim * 2 / 3, -interfaz.velocidadAnim / 6, interfaz.velocidadAnim / 3 });
		}
		else
			interfaz.paso = pasosFase1_3 - 1;
		interfaz.paso++;
	}
	else if (interfaz.paso > 0) {
		interfaz.paso = -1;
		interfaz.bucleCaminar = interfaz.bucleCaminarBackUp;
		interfaz.escena.resetearModelo();
		interfaz.escena.setSeleccionado("Cintura");
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutIdleFunc(set_glutIdleFunc);
}

