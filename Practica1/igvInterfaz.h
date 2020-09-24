#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else
#include <GL/glut.h>
#endif
#include <string>

using namespace std;

class igvInterfaz {
	protected:
		// Atributos
		int ancho_ventana; // ancho inicial de la ventana de visualizacion
		int alto_ventana;  // alto inicial de la ventana de visualizacion

	public:
		static bool ejes;

		// Constructores por defecto y destructor
		igvInterfaz();
		~igvInterfaz();

		// Metodos estáticos
		// callbacks de eventos
		static void set_glutKeyboardFunc(unsigned char key, int x, int y); // metodo para control de eventos del teclado
		static void set_glutReshapeFunc(int w, int h); // método que define la camara de vision y el viewport
		                                               // se llama automáticamente cuano se camba el tamaño de la ventana
		static void set_glutDisplayFunc(); // método para visualizar la escena


		// Metodos
		// inicializa todos los parámetros para crear una ventana de visualización
		void configura_entorno(int argc, char** argv, // parametros del main
			                     int _ancho_ventana, int _alto_ventana, // ancho y alto de la ventana de visualización
			                     int _pos_X, int _pos_Y, // posicion inicial de la ventana de visualización
													 string _titulo // título de la ventan de visualización
													 ); 
		void inicializa_callbacks(); // inicializa todas los callbacks

		void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

		// métodos get_ y set_ de acceso a los atributos
		int get_ancho_ventana(){return ancho_ventana;};
		int get_alto_ventana(){return alto_ventana;};

		void set_ancho_ventana(int _ancho_ventana){ancho_ventana = _ancho_ventana;};
		void set_alto_ventana(int _alto_ventana){alto_ventana = _alto_ventana;};

		static bool get_ejes() {
			return ejes;
		}

		static void set_ejes() {
			ejes = !ejes;
		}
};

#endif
