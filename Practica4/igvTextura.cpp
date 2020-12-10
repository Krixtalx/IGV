#include "igvTextura.h"

// Metodos constructores y destructor

igvTextura::igvTextura(char *fichero) {
	ancho = 0;
	alto = 0;

	SDL_Surface* imagen = NULL;

	glEnable(GL_TEXTURE_2D);
	if (!glIsTexture(idTextura)) {

		imagen = IMG_Load(fichero);
		if (!imagen)
		{
			/* Fallo de carga de la imagen */
			printf("Error al cargar la imagen: %s\n", IMG_GetError());
			return;

		}
		/* Muestra alguna información sobre la imagen */
		printf("Cargando %s: %dx%d %dbpp\n", fichero,
			imagen->w, imagen->h, imagen->format->BitsPerPixel);

	  
		// Apartado G: Añadir aquí el código para cargar como textura OpenGL la imagen */
	    //	- Generar el identificador de textura y asignarlo al atributo idTextura (glGenTextures)
		//	- Enlazar el identificador creado a GL_TEXTURE_2D (glBindTexture)
		//  - Especificar la textura, asignádole como textura el array imagen (glTexImage2D)
		//  - Modo de aplicación de la textura (glTexEnvf)
		//	- Parámetros de la textura: repetición y filtros (glTexParameteri)
		


		SDL_FreeSurface(imagen);

	}
}

void igvTextura::aplicar(void) {
  glBindTexture(GL_TEXTURE_2D, idTextura);
}

igvTextura::~igvTextura() {
  glDeleteTextures(1, &idTextura); 
}
