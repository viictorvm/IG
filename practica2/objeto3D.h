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
struct Vertices
{
	float v1,v2,v3;

	Vertices(float x=0.0, float y=0.0, float z=0.0)
	{		
		v1 = x; 
		v2 = y; 
		v3 = z; 
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

class Objeto3D
{
	protected:
		vector<Vertices> vertices;
		vector<Caras> caras;

	public:
		void draw_lines();
		void draw_points();
		void draw_fills();
		void draw();
		void draw_chess();
		void draw_everything();	
	
};

#endif