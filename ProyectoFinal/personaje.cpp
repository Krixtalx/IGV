#include "personaje.h"

personaje::personaje(igvCamara* camara, igvFuenteLuz* luz, igvPunto3D posInicial): camara(camara), luz(luz)
{
	setPos(posInicial);
}

personaje::~personaje()
{
}

void personaje::setPos(igvPunto3D pos)
{
	camara->setPos(pos);
	luz->setPosicion(pos);
}

void personaje::setPosApuntado(igvPunto3D pos)
{
	camara->setPosApuntado(pos);
	luz->setDireccionFoco(pos);
}

