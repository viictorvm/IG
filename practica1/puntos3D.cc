if defined(__APPLE__)

#endif
#include <cstdio>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>


Puntos3D::Puntos3D(float x, float y, float z)
{
	this.x=x;
	this.y=y;
	this.z=z;
}

float Puntos3D::operator[](int e)
{
	if (e==0) return x;
	else if (e==1) return y;
	return z;
}