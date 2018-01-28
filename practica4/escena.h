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
#include "modeloJerarquico.h"
#include "iluminacion.h"
#include "tablero.h"
#include "textura.h"


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
	void draw_revolution(SolidoRevolucion & ob, char tecla_tapa);

	Objeto3D *obj;
	Esfera esfera;
	SolidoRevolucion sr;
	SolidoRevolucion srExamen;
	ObjetoPly ply;
	Cubo cubo;
	Tetraedro tetraedro;
	Octaedro octaedro;
	Casa3D casa;
	ModeloJerarquico mj;
	char tecla='l';
	char tecla_tapa='a';
	int figura=5;
	bool tapa=true;
	float  libertad1=1.0;
	float libertad3=0.0;
	int libertad2=1;
	int libertad4=2;
	GLenum modo=GL_LINE;


	/////// Iluminacion
	float _f1, _f2;
	 Iluminacion luz1=Iluminacion(0);
	 Iluminacion luz2=Iluminacion(1);
	 Iluminacion luzExamen=Iluminacion(2);

	bool plomos_activado=false;
	bool flat=true;


	///////////// animación
	int sentido=1;
	float valorMaximoAngulo;
	float valorMinimoAngulo;
	float ang;
	
	
	int sentido_cuello=1;
	float valorMaximoCuello;
	float valorMinimoCuello;



	/////////////// Tablero texturas
	Tablero tablero;
	Textura textura;
	bool textura_activada=false;
	

public:
	
    Escena(string s, int b, const char * t);
	void inicializar(int UI_window_width,int UI_window_height);
	void redimensionar(int newWidth,int newHeight) ;

	// Dibujar
	void dibujar();
	void animacion();
	

	// Interacci�n con la escena
	int teclaPulsada(unsigned char Tecla1,int x,int y) ;
	void teclaEspecial(int Tecla1,int x,int y);

	void pintarExamen();


	void girarLuz(int n);
};
#endif
