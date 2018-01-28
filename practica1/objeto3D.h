#ifndef _OBJETO3D_H
#define _OBJETO3D_H

#include <vector>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

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
	float vector1,vector2,vector3;

	Vertices(float v1, float v2, float v3)
	{		
		vector1 = v1; 
		vector2 = v2; 
		vector3 = v3; 
	}
};
struct Color
{
	float r,g,b; 
	Color(float r, float g, float b)
	{
		r=r;
		g=g;
		b=b;
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
		//void draw(int figura, int modo);
		
	
};

#endif