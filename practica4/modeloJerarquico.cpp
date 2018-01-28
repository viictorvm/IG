#include <cstdio>
#include <iostream>
#include "modeloJerarquico.h"

ModeloJerarquico::ModeloJerarquico()
{
    cubo=Cubo(tam_c);
    esfera=Esfera(tam_e);
    tam_c=50.0;
    tam_e=5.0;
    w=10.0;
    body_size_y=100.0;
    libertad1=libertad4=1.0;
    libertad2=1;
    libertad3=0.0;
    
    _x=0.5;
    ancho_cuerpo=tam_c*_x;
    altura_cuerpo=tam_c*2;
    ancho_muslo=alto_muslo=tam_c;
    grados_brazos=60;
    libertad4=2;
    factor_cuello=0.3;
    
    largo_cuello=tam_c*factor_cuello;

    ancho_cabeza=alto_cabeza=tam_c;


    luzExamen.setAmbient(0.973,0.0,0.0,1.0);
	luzExamen.setDiffuse(0.973,0.0,0.0,1.0);
	luzExamen.setSpecular(0.973,0.0,0.0,1.0);
	luzExamen.setPosition(0.0,200.0,0.0,1.0);
    movimiento_general=0.0;


}
void ModeloJerarquico::setLibertad1(float & libertad) // angulo de la pierna
{
    if(libertad<1.0) 
    libertad1=libertad=1.0;
    else if(libertad>60.0)
    {
        libertad1=libertad=60.0;
    }
    else 
    libertad1=libertad;
    
}
void ModeloJerarquico::setLibertad2(int & libertad)    // estiramos el cuello
{
    if(libertad<1)
    libertad2=libertad=1;
    else if(libertad>3)
    {
        libertad2=libertad=3;
    }
    else 
        libertad2=libertad;

    
}
void ModeloJerarquico::setLibertad3(float & libertad)   // rotacion de la cabeza
{
    libertad3=libertad;
    
}

void ModeloJerarquico::setLibertad4(int & libertad)   // rotacion de la cabeza
{
    if(libertad<2)
    {
        libertad4=libertad=1;
    }
    else if (libertad>4)
    {
        libertad4=libertad=4;
    }
    else
        libertad4=libertad;
       
}

void ModeloJerarquico::setMovimientoGeneral(float _mov)
{
    movimiento_general+=_mov;

}
void ModeloJerarquico::draw_mj()
{
    
    float antiguo_torso=tam_c*2- (tam_c*2)/(1.5); //34
    float nuevo_cuello= tam_c*2*libertad2 - antiguo_torso;  //calculamos la longitud del cuello
    
    float nuevo=largo_cuello*libertad4;


     
    glTranslatef(movimiento_general,0,0);
   
   glEnable(GL_LIGHTING);
    luzExamen.encender();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(0,tam_c*2+largo_cuello ,0);
    cabeza(libertad3);
    glTranslatef(0,-nuevo,0);
    minicuello();
    
    glTranslatef(ancho_cuerpo/2,-(nuevo_cuello-antiguo_torso),0); // situar el cuerpo en el origen para posicionar la cabeza
    brazo_izq(grados_brazos);
    glTranslatef(-ancho_cuerpo,0,0); // lo ponemos en el otro lado del eje para ponerle el otro brazo
    brazo_dcha();  
    glPushMatrix();                        //los brazos siempre van a estar en la misma posicion sea como sea el cuello
        glTranslatef(0,-(tam_c*2)/(1.5),0); //situar el cuerpo en el origen para posicionar el cuerpo 
        pierna_dcha(libertad1);
        glTranslatef(ancho_cuerpo,0,0);
        cuerpo(libertad2);
        pierna_izq(libertad1);
    glPopMatrix();
    
}

void ModeloJerarquico::ojo()
{
    glPushMatrix();
    esfera.setTipoPintar(tipo_pintar);
    esfera.setModoPintar(modo_pintar);
    esfera.draw();
    glPopMatrix();
}

void ModeloJerarquico::muslo()
{
    float _ancho=0.2;
    float _altura=1;
    ancho_muslo =tam_c*_ancho;
    alto_muslo=tam_c*_altura;
    
    glPushMatrix();
    glTranslatef(-ancho_muslo/2,0,ancho_muslo/2); 
    glScalef(_ancho,_altura,_ancho);
    cubo.setTipoPintar(tipo_pintar);
    cubo.setModoPintar(modo_pintar);
    cubo.draw();
    glPopMatrix();
    
}
void ModeloJerarquico::pierna_izq(float libertad1, float posicion)
{
    glPushMatrix();
    glRotatef(posicion, 0 ,0,1);
    glTranslatef(0,-alto_muslo,0);
    muslo();
    esfera.setTipoPintar(tipo_pintar);
    esfera.setModoPintar(modo_pintar);
    esfera.draw();
    glRotatef(-libertad1, 0,0,1);  //primer grado de libertad
    glTranslatef(0,-alto_muslo,0);
    muslo();
    glPopMatrix();
}

void ModeloJerarquico::pierna_dcha(float libertad1)
{
    glPushMatrix();
    pierna_izq(-libertad1, -60);
    glPopMatrix();
}
void ModeloJerarquico::cuerpo(int libertad2)
{ 
    _x=0.5;
    ancho_cuerpo=tam_c*_x;
    altura_cuerpo=2*libertad2; 
    glPushMatrix();                                     // tenemos que modificar tambien la Z para que esté centrado
    glTranslatef((-ancho_cuerpo),0,ancho_cuerpo/2); // ponemos el cuerpo a un lado del eje para posteriormente ponerle el brazo derecho
    glScalef(_x, 2*libertad2, _x);
    cubo.setTipoPintar(tipo_pintar);
    cubo.setModoPintar(modo_pintar);
    cubo.draw();
    glPopMatrix();
    
}

void ModeloJerarquico::cabeza(float libertad3)
{
    float pos_ojo=8;
    glPushMatrix();
    glRotatef(libertad3,0,1,0);
   
    glTranslatef(-(ancho_cabeza-(pos_ojo*2))/2,alto_cabeza/1.7,ancho_cabeza/2);  // arreglos para ponerlo en medio de eje
    ojo();
    glTranslatef((ancho_cabeza-(pos_ojo*2)),0,0);
    ojo();
    glTranslatef(- (ancho_cabeza-pos_ojo),-alto_cabeza/1.7,0);
    cubo.setTipoPintar(tipo_pintar);
    cubo.setModoPintar(modo_pintar);
    cubo.draw();
    glPopMatrix();
    
}

void ModeloJerarquico::brazo_izq(int posicion_brazos)
{
    glPushMatrix();
    glRotatef(posicion_brazos,0,0,1);
    glTranslatef(0,-alto_muslo,0);
    cubo.setTipoPintar(tipo_pintar);
    esfera.setModoPintar(modo_pintar);
    esfera.draw();
    muslo();
    glPopMatrix();
}
void ModeloJerarquico::brazo_dcha()
{
    brazo_izq(-grados_brazos);
}

void ModeloJerarquico::minicuello()
{
    glPushMatrix();
    glScalef(1,libertad4,1);
    glTranslatef((-largo_cuello/2), 0,(largo_cuello)/2);
    glScalef(factor_cuello,factor_cuello,factor_cuello);
    cubo.setTipoPintar(tipo_pintar);
    cubo.setModoPintar(modo_pintar);
    cubo.draw();
    glPopMatrix();
}

void ModeloJerarquico::mover(float n)
{
    // glPushMatrix();
    //     glTranslatef(-tam_c*20/2,-tam_c*5,0);
    //     glScalef(20,1,1);
    //     glTranslatef(0,0,tam_c/2);
    //     glColor3f(255.0,255.0,0.0);
    //     cubo.setTipoPintar(tipo_pintar);
    //     cubo.setModoPintar(modo_pintar);
    //     cubo.draw();
    // glPopMatrix();

    luzExamen.posicionar();
     glTranslatef(-20,0,0);
   

}
