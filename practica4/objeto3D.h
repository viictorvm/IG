#ifndef _OBJETO3D_H
#define _OBJETO3D_H

#include <vector>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <string>

using namespace std;

struct Caras
{
	int c0,c1,c2;

	Caras(int cara1, int cara2, int cara3)
	{
		c0=cara1;
		c1=cara2;
		c2=cara3;
	}
};
struct Vertices2D
{
	float v1, v2;

	Vertices2D(float x=0.0, float y=0.0)
	{		
		v1 = x; 
		v2 = y; 
	}
	Vertices2D operator+( float & p) const
	{
		Vertices2D nuevo;
		nuevo.v1=p+this->v1;
		nuevo.v2=p+this->v2;
		
		return nuevo;
	}
};
struct Vertices
{
	float v1,v2,v3;

	Vertices(float x=0.0, float y=0.0, float z=0.0)
	{		
		v1 = x; 
		v2 = y; 
		v3 = z; 
	}
	Vertices operator+( Vertices & p) const
	{
		Vertices nuevo;
		nuevo.v1=p.v1+this->v1;
		nuevo.v2=p.v2+this->v2;
		nuevo.v3=p.v3+this->v3;

		return nuevo;
	}
	
};
struct Color
{
	float r,g,b; 
	Color(float _r, float _g, float _b)
	{
		r=_r;
		g=_g;
		b=_b;
	}
};

/* 	pname puede ser GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR, 
	GL_EMISSION, GL_SHININESS, GL_AMBIENT_AND_DIFFUSE,
	o GL_COLOR_INDEXES
 						*/
struct Material
{
	GLfloat ambient[4]={1.0,0.0,0.0,1.0};
    GLfloat diffuse[4];
    GLfloat specular[4];
	GLfloat shininess;

	Material(float a, float b, float c, float d, float e, float f, float g, float h , float l , float m) 
	{
		ambient[0]= a;
		ambient[1]= b;
		ambient[2]= c;
		ambient[3]= 1.0;

		diffuse[0]= d;
		diffuse[1]= e;
		diffuse[2]= f;
		diffuse[3]= 1.0;

		specular[0]=g;
		specular[1]=h;
		specular[2]=l;
		specular[3]=1.0;

		shininess=m;
	}
};

class Objeto3D
{
	protected:
		vector<Vertices> vertices;
		vector<Caras> caras;
		vector<Vertices> normales_caras;
		vector<Vertices> normales_vertices;
		vector<Vertices2D> vertices_texturas;
		GLenum modo_pintar=GL_LINE;
		int tipo_pintar=0;
		Material material1=Material(0.24725,0.1995,0.0745,0.75164,0.60648,0.22648,0.628281,0.555802,0.366065,0.4);  // oro
		Material material2=Material(0.05,0.05,0.05,0.05,0.05,0.05,0.7,0.7,0.7,0.078125); 							// goma blanca
		Material material3=Material(0.19225,0.19225,0.19225,0.50754,0.50754,0.50754,0.508273,0.508273,0.508273,0.4); // plata
	
	public:
		void draw_points();
		void draw();
		void draw_chess();
		void draw_everything();
		void setModoPintar(GLenum modo) { modo_pintar = modo; }
		void setTipoPintar(int tipo) { tipo_pintar = tipo; }
		void crearNormalesCaras();
		Vertices productoVectorial(Vertices _v1, Vertices _v2, Vertices _v3);
		Vertices productoVectorial(Vertices p, Vertices q);
		void pintarNormales();
		Vertices normalizar(Vertices v);
		void activarMaterial(int n=1);
		// void setMaterial1(GLenum face, GLenum pname, float x, float y, float z, float w){ material1.setMaterial(face, pname,x,y,z,w); }
		// void setMaterial2();
		// void setMaterial3();
	
};

#endif