
#include <cstdio>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "escena.h"
#include "solidoRevolucion.h"
#include "objetoPly.h"
#include <typeinfo>
#include <unistd.h>


Escena::Escena(string f, int n, const char * t): sr(f, 15, true), ply(f), textura(t)
{
	Front_plane=50;
	Back_plane=2000;
	Observer_distance = 4*Front_plane;
	Observer_angle_x = Observer_angle_y=0;
	ejes.changeAxisSize(5000);

	 valorMaximoAngulo=40.0;
	 valorMinimoAngulo=1.0;

	 valorMaximoCuello=3;
	 valorMinimoCuello=1;
	
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

	obj=0;

	luz2.setAmbient(0.973,0.0,0.0,1.0);
	luz2.setDiffuse(0.973,0.0,0.0,1.0);
	luz2.setSpecular(0.973,0.0,0.0,1.0);
	luz2.setPosition(-100.0,100.0,-100.0,1.0);


	

	_f1=_f2=0.0;
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

void Escena::pintarExamen()
{
	
}
void Escena::draw_objects()
{
	if(figura==7)
	{
		glPushMatrix();
	 glTranslatef(-50*20/2,-50*5,0);
        glScalef(20,1,1);
        glTranslatef(0,0,50/2);
        glColor3f(255.0,255.0,0.0);
        cubo.setTipoPintar(0);
        cubo.setModoPintar(GL_FILL);
			cubo.draw();
		glPopMatrix();

		mj.setModoPintar(GL_FILL);
		mj.draw_mj();

	}

	if(obj) {
	 obj->setModoPintar(modo);
	 if(figura==5)
	 {
		 ((class ModeloJerarquico *)obj)->draw_mj();
	 }
	 else
	 	obj->draw();
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
		case '-':Observer_distance*=1.2;
		break;
		case '+':Observer_distance/=1.2;
		break;
		case '4': figura=4; 
				  obj=&sr; // revolucion
		break;
		case '5': figura=5;
					obj=&mj;	
		break;
		case '6': figura=6;
					obj=&tablero;	
		break;
		case '7': figura=7;			
		break;
		case 'l': obj->setTipoPintar(0);
					modo = GL_LINE;//  lineas
		break;
		case 'p':  obj->setTipoPintar(0);
				   modo = GL_POINT;  // points
		break;
		case 'a': obj->setTipoPintar(1); // chess
		break;
		case 'f':
			 obj->setTipoPintar(0);
			  modo = GL_FILL; //fill
		break;
		case 'z': mj.setLibertad1(libertad1+=0.3);
		break;
		case 'Z': mj.setLibertad1(libertad1-=0.3);
		break;
		case 'x': mj.setLibertad2(libertad2+=1.5);
		break;
		case 'X': mj.setLibertad2(libertad2-=1.5);
		break;
		case 'c': mj.setLibertad3(libertad3+=4.0);
		break;
		case 'C': mj.setLibertad3(libertad3-=4.0);
		break;
		case 'k': mj.setLibertad4(libertad4+=1);
		break;
		case 'K': mj.setLibertad4(libertad4-=1);
		break;
		case 'M': tablero.desplazarTextura(0.1);
		break;
		case 'm': tablero.desplazarTextura(-0.1);
		break;
		case '9': mj.setMovimientoGeneral(5.0);
		break;
		case '8': mj.setMovimientoGeneral(-5.0);
		break;
		case's': if(flat)
				{
					flat=false;
					glShadeModel(GL_SMOOTH);
				}
				else{
					flat=true;
					glShadeModel(GL_FLAT);
				}
		break;
		case 'i': if(plomos_activado)
					{
						glDisable(GL_LIGHTING);
						plomos_activado=false;
						luz1.apagar();
						luz2.apagar();
						luzExamen.apagar();
					}
					else 
					{
					  glEnable(GL_LIGHTING);
					  luz1.encender();
					  luz2.encender();
					//luzExamen.encender(;
					  plomos_activado=true;
				  	}
		break;
		case 't': 
					   if(textura_activada) 
					  {
						  textura.desactivarTextura();
						  textura_activada=false;
					  }
					  else 
					  {
						  textura.cargarTextura();
						  textura.activarTextura();
						  textura_activada=true;
					  } 
		break;
		
	}
	return 0;
}

void Escena::animacion()
{
	usleep(10000); 

	if (sentido==1)
	{
		libertad1++;
		if(libertad1==valorMaximoAngulo)
			sentido=0;
	}
	else
	{
		libertad1--;
		if(libertad1==valorMinimoAngulo)
			sentido=1;
	}

	if(sentido_cuello==1)
	{
			libertad2+=1;
			if(libertad2==valorMaximoCuello)
				sentido_cuello=0;
	}
	else
	{
		libertad2-=1;
		if(libertad2==valorMinimoCuello)
			sentido_cuello=1;
	}

	
	libertad3+=1.0;

	mj.setLibertad1(libertad1);
	mj.setLibertad2(libertad2);
	mj.setLibertad3(libertad3);

	glutPostRedisplay();
}

void Escena::teclaEspecial(int Tecla1,int x,int y) {
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_F1:_f1+=25.0;girarLuz(1);break;
		case GLUT_KEY_F2:_f2+=25.0;girarLuz(2);break;
		case GLUT_KEY_F5:obj->activarMaterial(1);break;
		case GLUT_KEY_F6:obj->activarMaterial(2);break;
		case GLUT_KEY_F7:obj->activarMaterial(3);break;

		//case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		//case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
	
	std::cout << Observer_distance << std::endl;
}

void Escena::girarLuz(int foco)
{ 
	if(plomos_activado)
	{
		Iluminacion * aux;
		aux=&luz1;
		int aux_grados=_f1;

		if(foco==2) 
		{
			aux=&luz2;
			aux_grados=_f2;
		}

		glPushMatrix();
			glRotatef(aux_grados,1,0,0);
			aux->posicionar();
		glPopMatrix();
		
	}

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




