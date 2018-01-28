#include <cstdio>
#include <iostream>
#include "cubo.h"

/* Practica realizada por Victor Vallecillo Morilla*/

void Objeto3D::draw_lines()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	draw();
	
}
void Objeto3D::draw_points()
{
	glPointSize(5.0);
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
	glDrawArrays(GL_POINTS, 0, vertices.size());
	/*Al utilizar drawElements tengo que pasarle
	una tabla de caras, pero si quieremos pintar un perfil donde todavia no existan
	caras tendremos que usar drawArrays*/
}

void Objeto3D::draw_fills()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	draw();
}

void Objeto3D::draw()
{
	glPointSize(5.0);
	glEnable(GL_CULL_FACE);
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
	glDrawElements(GL_TRIANGLES, 3*caras.size(), GL_UNSIGNED_INT, &caras[0]);
}

void Objeto3D::draw_everything()
{
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
	vector<Color>v1, v2, v3;  

	for(int i = 0; i < vertices.size(); i++){
		
			v1.push_back(Color(255, 215, 0)); 

			v2.push_back(Color(255, 0, 0));
			
			v3.push_back(Color(0,255,0));
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColorPointer(3, GL_FLOAT,0,&v1[0]);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawElements(GL_TRIANGLES, 3*caras.size(), GL_UNSIGNED_INT, &caras[0]);


	glColorPointer(3, GL_FLOAT,0,&v2[0]);
	glEnableClientState(GL_COLOR_ARRAY);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glDrawElements(GL_TRIANGLES, 3*caras.size(), GL_UNSIGNED_INT, &caras[0]);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColorPointer(3, GL_FLOAT,0,&v3[0]);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawElements(GL_TRIANGLES, 3*caras.size(), GL_UNSIGNED_INT, &caras[0]);
}
void Objeto3D::draw_chess()
{

	vector<Caras> c_pares, c_impares;

	for(int j=0;j<caras.size();j++)
	{
		if(j % 2 != 0) c_impares.push_back(caras[j]);
		else c_pares.push_back(caras[j]);
	}

	vector<Color>cp;  // tmp colores pares 
	vector<Color>ci;	// tmp colores impares 

	// rellenar los vectores de colores
	// cada vector tendrá el tamaño de la mitad del vector de vértices 
	for(int i = 0; i < vertices.size(); i++)
	{
			cp.push_back(Color(255, 215, 0)); 

			ci.push_back(Color(255, 0, 0)); 
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer(3,GL_FLOAT,0,&vertices[0]);


	// dibujar caras impares
	glEnableClientState( GL_COLOR_ARRAY );
	glColorPointer(3, GL_FLOAT,0,&ci[0]);
	glDrawElements(GL_TRIANGLES, 3*c_impares.size(), GL_UNSIGNED_INT, &c_impares[0]);
	
	// // dibujar caras paras
	glEnableClientState( GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT,0,&cp[0]);
	glDrawElements(GL_TRIANGLES, 3*c_pares.size(), GL_UNSIGNED_INT, &c_pares[0]);
}


