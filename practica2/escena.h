#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "objeto3D.h"
#include "cubo.h"
#include "tetraedro.h"
#include "octaedro.h"
#include "casa3d.h"
#include "solidoRevolucion.h"
#include "objetoPly.h"
#include "esfera.h"
#include <vector>
#include <string>

/* Practica realizada por Victor Vallecillo Morilla*/

class Escena {
private:
// tamanio de los ejes
#define AXIS_SIZE 5000
Ejes ejes;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Width,Height,Front_plane,Back_plane;

private:
	void clear_window();
	void draw_axis();
	void draw_objects();

//Transformacion de camara
	void change_projection();
	void change_observer();
	template<class T>
	void draw_all_objects(T  ob, char modo);
	void draw_revolution(SolidoRevolucion & ob, char tecla_tapa);

	Objeto3D *obj;
	Esfera e;
	SolidoRevolucion sr;
	SolidoRevolucion srExamen;
	ObjetoPly ply;
	Cubo cubo;
	Tetraedro tetraedro;
	Octaedro octaedro;
	Casa3D casa;
	char tecla='l';
	char tecla_tapa='a';
	int figura=4;
	bool tapa=true;
public:
	
    Escena(string s, int b);
	void inicializar(int UI_window_width,int UI_window_height);
	void redimensionar(int newWidth,int newHeight) ;

	// Dibujar
	void dibujar() ;
	

	// Interacci�n con la escena
	int teclaPulsada(unsigned char Tecla1,int x,int y) ;
	void teclaEspecial(int Tecla1,int x,int y);

	void crearSolido(string, int n);
	void crearExamen();
};
#endif
