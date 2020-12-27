#pragma once
#include "igvCamara.h"
#include "igvFuenteLuz.h"
class personaje
{
private:
	igvCamara* camara;
	igvFuenteLuz* luz;
	

public:
	personaje(igvCamara* camara, igvFuenteLuz* luz, igvPunto3D posInicial);
	~personaje();
	void setPos(igvPunto3D pos);
	void setPosApuntado(igvPunto3D pos);
};

