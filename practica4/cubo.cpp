#include <cstdio>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "cubo.h"


	//    v6----- v5
	//   /|      /|
	//  v3------v2|
	//  | |     | |
	//  | |v7---|-|v4
	//  |/      |/
	//  v0------v1
	//float tam=50.0;

	//Cubo(50.0f);

Cubo::Cubo(float tam)
{
	vertices.push_back(Vertices(0.0,0.0,0.0));
	vertices.push_back(	Vertices(tam,0.0,0.0));
	vertices.push_back(Vertices(tam,tam,0.0));
	vertices.push_back(Vertices(0.0,tam,0.0));
	vertices.push_back(Vertices(tam,0.0,-tam));
	vertices.push_back(Vertices(tam,tam,-tam));
	vertices.push_back(Vertices(0.0,tam,-tam));
	vertices.push_back(Vertices(0.0,0.0,-tam)); // v7

	caras.push_back(Caras(0,1,2)); 
	caras.push_back(Caras(2,3,0));//Cara delantera

	caras.push_back(Caras(1,4,5));
	caras.push_back(Caras(5,2,1)); // lateral decha
	
	caras.push_back(Caras(2,5,3));
	caras.push_back(Caras(5,6,3));  // cara de arriba

	caras.push_back(Caras(7,3,6));
	caras.push_back(Caras(7,0,3)); // lateral izquierdo

	caras.push_back(Caras(1,0,4));
	caras.push_back(Caras(7,4,0)); // cara de abajo
	
	caras.push_back(Caras(5,4,7)); // cara trasera
	caras.push_back(Caras(7,6,5)); 

	crearNormalesCaras();


}