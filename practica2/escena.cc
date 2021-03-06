
#include <cstdio>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "escena.h"
#include "solidoRevolucion.h"
#include "objetoPly.h"
#include <typeinfo>


Escena::Escena(string f, int n): sr(f, 15, true), ply(f)
{
	Front_plane=50;
	Back_plane=2000;
	Observer_distance = 4*Front_plane;
	Observer_angle_x = Observer_angle_y=0;
	ejes.changeAxisSize(5000);
	
	// EXAMEN
	int aumentar=10;
	vector<Vertices>exam;
	exam.push_back(Vertices(3*aumentar,5*aumentar,0*aumentar));
	exam.push_back(Vertices(3*aumentar,4*aumentar,0*aumentar));
	exam.push_back(Vertices(3*aumentar,3*aumentar,0*aumentar));
	exam.push_back(Vertices(2*aumentar,2*aumentar,0*aumentar));
	exam.push_back(Vertices(1.5*aumentar,1*aumentar,0));
	exam.push_back(Vertices(1*aumentar,0,0));
	srExamen = SolidoRevolucion(exam, 20, true);

	obj=&cubo;
}

void Escena::inicializar(int UI_window_width,int UI_window_height)
{
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

template<class T>
void Escena::draw_all_objects(T ob, char modo)
{
	switch(modo)
	{
		case 'l': ob.draw_lines();
		break;
		case 'p': ob.draw_points();
		break;
		case 'f': ob.draw_fills();
		break;
		case 'a': ob.draw_chess();
		break;
	}
}

void Escena::draw_revolution(SolidoRevolucion & ob, char tecla_tapa)
{
	int n;
	if(tecla_tapa=='t')
	{
		ob.modificar_tapas(tapa);
		tapa=!tapa;
	}
	else if(tecla_tapa=='n')
	{
		cin >> n;
		ob=SolidoRevolucion(ob.getFichero(), n, tapa);
	}
	tecla_tapa='a';
}


void Escena::draw_objects()
{

	switch(tecla)
	{
		case 'l': obj->draw_lines();
		break;
		case 'p': obj->draw_points();
		break;
		case 'f': obj->draw_fills();
		break;
		case 'a': obj->draw_chess();
		break;
	}


	// switch(figura)
	// {
	// 	case 1: draw_all_objects(tetraedro, tecla);
	// 	break;
	// 	case 2: draw_all_objects(cubo, tecla);
	// 	break;
	// 	case 3: draw_all_objects(ply, tecla);
	// 	break;
	// 	case 4: if (tecla_tapa!='a') draw_revolution(sr, tecla_tapa);
	// 			draw_all_objects(sr, tecla);  // solido revolucion
	// 	break;
	// 	case 5: if (tecla_tapa!='a') draw_revolution(srExamen, tecla_tapa);
	// 			draw_all_objects(srExamen,tecla); // examen
	// 	break;
	// }

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
		case 'q': return 1;
		break;
		case '1':figura=1; 
				obj=&tetraedro;// tetraedro
		break;
		case '2':figura=2;
				obj=&cubo; // cubo
		break;
		case '3': figura=3;
				  obj=&ply; // ply
		break;
		case 'u':Observer_distance*=1.2;
		break;
		case 'i':Observer_distance/=1.2;
		break;
		case '4': figura=4; 
				  obj=&sr; // revolucion
		break;
		case '5': figura=5;
				  obj=&srExamen; // examen
		break;
		case 'l': tecla='l';//  lineas
		break;
		case 'p': tecla='p'; // points
		break;
		case 'a': tecla='a';// chess
		break;
		case 'f': tecla='f'; //fill
		break;
		case 't': tecla_tapa='t';   // tapas
		break;
		case 'n': tecla_tapa='n';   // tapas
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




