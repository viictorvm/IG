#include <cstdio>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <vector>

#include "tetraedro.h"

Tetraedro::Tetraedro(float tam)
{ //tam 80
	vertices.push_back(Vertices(-tam,0.0,0.0)); //v0¡
	vertices.push_back(Vertices(tam,0.0,0.0));
	vertices.push_back(Vertices(0.0,0.0,-tam)); // el de atrás
	vertices.push_back(Vertices(0.0,tam*2,-tam/2));  // punta

	caras.push_back(Caras(0,1,3));    // vertices 0, 1, el de atrás 2, y la punta 3
	caras.push_back(Caras(1,2,3));
	caras.push_back(Caras(3,2,0));
	caras.push_back(Caras(0,1,2));
}
