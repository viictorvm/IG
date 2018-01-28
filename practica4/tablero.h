#ifndef _TABLERO_H
#define _TABLERO_H
#include "objeto3D.h"

class Tablero : public Objeto3D
{
	public:
		Tablero(int dimensiones=20);
		void desplazarTextura(float);
		void girarTextura(float);
	
};

#endif