#include <cstdio>
#include <iostream>
#include "cubo.h"
#include <cmath>
#include <cassert>

/* Practica realizada por Victor Vallecillo Morilla*/

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

void Objeto3D::draw()
{
	if(tipo_pintar == 0)
	 {
		if(modo_pintar == GL_POINT)
		{
			draw_points();
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, modo_pintar);
			glEnable(GL_CULL_FACE);
			if(vertices_texturas.size()>0)
			{
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					glTexCoordPointer(2, GL_FLOAT,0,&vertices_texturas[0]);
			}
			glEnableClientState( GL_VERTEX_ARRAY );
			glEnableClientState( GL_NORMAL_ARRAY );
			glNormalPointer(GL_FLOAT, 0 , &normales_caras[0]);
			glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
			glDrawElements(GL_TRIANGLES, 3*caras.size(), GL_UNSIGNED_INT, &caras[0]);
		
		}
	}
	else if(tipo_pintar == 1) 
	{
		draw_chess();
	}
	else {
		draw_everything();
	}
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

Vertices Objeto3D::productoVectorial(Vertices p, Vertices q)
{
	return Vertices(p.v2*q.v3 - p.v3*q.v2, p.v3*q.v1 - p.v1*q.v3, p.v1*q.v2 - p.v2*q.v1);
}

void  Objeto3D::crearNormalesCaras()  //creamos las normales de las caras
{
	normales_caras.clear();
	normales_vertices.clear();

	normales_vertices.resize(vertices.size(), 0);

	for(int i=0; i<caras.size();i++)
	{
		Vertices producto=productoVectorial(vertices[caras[i].c0],vertices[caras[i].c1],vertices[caras[i].c2]);
		
		normales_caras.push_back(normalizar(producto));

		normales_vertices[caras[i].c0].v1+=normales_caras[i].v1;
		normales_vertices[caras[i].c0].v2+=normales_caras[i].v2;
		normales_vertices[caras[i].c0].v3+=normales_caras[i].v3;

		normales_vertices[caras[i].c1].v1+=normales_caras[i].v1;
		normales_vertices[caras[i].c1].v2+=normales_caras[i].v2;
		normales_vertices[caras[i].c1].v3+=normales_caras[i].v3;

		normales_vertices[caras[i].c2].v1+=normales_caras[i].v1;
		normales_vertices[caras[i].c2].v2+=normales_caras[i].v2;
		normales_vertices[caras[i].c2].v3+=normales_caras[i].v3;
	}
}
Vertices Objeto3D::normalizar(Vertices v)
{
	Vertices nuevo;
	float modulo= sqrt( (v.v1*v.v1) + (v.v2*v.v2) + (v.v3*v.v3));
	
	nuevo.v1= (v.v1 / modulo) * 10;
	nuevo.v2= (v.v2 / modulo)*10;
	nuevo.v3= (v.v3 / modulo)*10;

	return nuevo;
}

 void Objeto3D::pintarNormales()
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_LINES);

	for(int i = 0; i < caras.size(); i++)
	{
		Vertices aux= (vertices[caras[i].c0] + vertices[caras[i].c1] + vertices[caras[i].c2]);

		Vertices baricentro;
		baricentro.v1=aux.v1/3.0;
		baricentro.v2=aux.v2/3.0;
		baricentro.v3=aux.v3/3.0;

		Vertices p = baricentro + normales_caras[i];
		Vertices q= vertices[i] + normales_vertices[i];

		glColor3f(1,0,0);
		glVertex3f(baricentro.v1, baricentro.v2, baricentro.v3);
		glVertex3f(p.v1, p.v2, p.v3);

		glVertex3f(vertices[i].v1, vertices[i].v2, vertices[i].v3);
		glColor3f(0,1,0);
		glVertex3f(q.v1, q.v2, q.v3);
	}
	glEnd();
} 

Vertices Objeto3D::productoVectorial(Vertices _v1, Vertices _v2, Vertices _v3)
{
  // En base a los tres puntos, calculamos los vectores
  Vertices p, q;

  p.v1 = _v2.v1 - _v1.v1;
  p.v2 = _v2.v2 - _v1.v2;
  p.v3 = _v2.v3 - _v1.v3;
  q.v1 = _v3.v1 - _v1.v1;
  q.v2 = _v3.v2 - _v1.v2;
  q.v3 = _v3.v3 - _v1.v3;

  return productoVectorial(p, q);
}

void Objeto3D::activarMaterial(int n)
{
	cout << "Entramos en el material numero: " << n << endl;
	Material aux=material1;
 	if(n==2)
	{
		aux=material2;
	}
	else if(n==3)
	{
		aux=material3;
	}

	glMaterialfv(GL_FRONT,GL_AMBIENT,((GLfloat *) &aux.ambient));
	glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &aux.diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &aux.specular);
	glMaterialf(GL_FRONT,GL_SHININESS, aux.shininess * 128.0);
	
}