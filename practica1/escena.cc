
#include <cstdio>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "escena.h"


Escena::Escena(){
	Front_plane=50;
	Back_plane=2000;
	Observer_distance = 4*Front_plane;
	Observer_angle_x = Observer_angle_y=0;
	ejes.changeAxisSize(5000);
}

void Escena::inicializar(int UI_window_width,int UI_window_height) {
	
	glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	
	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer
	
	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);
	
}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects()
{	glEnable(GL_CULL_FACE);
	if(figura==2)  // cubo 
	{
		switch(tecla)
		{
			case 'l': cubo.draw_lines();
			break;
			case 'p': cubo.draw_points();
			break;
			case 'f': cubo.draw_fills();
			break;
			case 'a': cubo.draw_chess();
			break;
			case 't': cubo.draw_everything();
			break;
		}
	}
	else if (figura ==1) // tetraedro
	{
		switch(tecla)
		{
			case 'l': tetraedro.draw_lines();
			break;
			case 'p': tetraedro.draw_points();
			break;
			case 'a': tetraedro.draw_chess();
			break;
			case 'f': tetraedro.draw_fills();
			break;
			case 't': tetraedro.draw_everything();
			break;
		}
	}
	else if(figura==3)  // octaedro
	{
		switch(tecla)
		{
			case 'l': octaedro.draw_lines();
			break;
			case 'p': octaedro.draw_points();
			break;
			case 'a': octaedro.draw_chess();
			break;
			case 'f': octaedro.draw_fills();
			break;
			case 't': octaedro.draw_everything();
			break;
		}
	}
	else if(figura==4)  // casa
	{
		switch(tecla)
		{
			case 'l': casa.draw_lines();
			break;
			case 'p': casa.draw_points();
			break;
			case 'a': casa.draw_chess();
			break;
			case 'f': casa.draw_fills();
			break;
			case 't': casa.draw_everything();
			break;
		}
	}
}
void Escena::dibujar() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	draw_axis();
	draw_objects();
}

int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) 
{ 
	switch(Tecla1)
	{
		case 'Q': return 1;
		break;
		case '1':figura=1; // tetraedro
		break;
		case '2':figura=2; // cubo
		break;
		case '3': figura=3; // octaedro
		break;
		case 'u':Observer_distance*=1.2;
		break;
		case 'i':Observer_distance/=1.2;
		break;
		case '4': figura=4;  // casa
		break;
		case 'l': tecla='l';  //  lineas
		break;
		case 'p': tecla='p'; // points
		break;
		case 'a': tecla='a';  // chess
		break;
		case 'f': tecla='f';   //fill
		break;
		case 't': tecla='t';   // lines, points and fill in the same time
		break;
		
	}
	
	return 0;
}

void Escena::teclaEspecial(int Tecla1,int x,int y) {
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		//case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		//case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
	
	std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformaci�n de proyeccion
//***************************************************************************

void Escena::change_projection()  {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-Width,Width,-Height,Height,Front_plane,Back_plane);
}


void Escena::redimensionar(int newWidth,int newHeight) {
	change_projection();
	Width=newWidth/10;
	Height=newHeight/10;
	glViewport(0,0,newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************



void Escena::change_observer() {
	
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis()
{
	ejes.draw();
}




