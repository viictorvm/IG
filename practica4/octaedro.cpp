#include <cstdio>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "octaedro.h"

/* Victor Vallecillo Morilla */


    //Octaedro(80.0);

Octaedro::Octaedro(float tam)
{
    vertices.push_back(Vertices(-tam,0.0,0.0)); //primero delantero v0
	vertices.push_back(Vertices(tam,0.0,0.0));  //segundo delantero v1
    
    vertices.push_back(Vertices(tam,0.0,-tam));  // primero de atrás v2
    vertices.push_back(Vertices(-tam,0.0,-tam)); // segundo de atrás v3

    vertices.push_back(Vertices(0.0,tam*2,-tam/2));  // punta v4

    //segunda lado
   vertices.push_back(Vertices(0.0,-tam*2,-tam/2));  // punta de abajo v5

    //todas las unimos con el vertice de arriba
        caras.push_back(Caras(0,1,4));
        caras.push_back(Caras(1,3,4));
        caras.push_back(Caras(4,3,2));
        caras.push_back(Caras(2,0,4));
    //lo mismo pero ahora con el vertice de abajo
    caras.push_back(Caras(0,5,1));
    caras.push_back(Caras(1,5,3));
    caras.push_back(Caras(3,2,5));
    caras.push_back(Caras(2,5,0));
}


