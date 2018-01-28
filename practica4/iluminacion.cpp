#include <cstdio>
#include <iostream>
#include "iluminacion.h"

Iluminacion::Iluminacion( int n )
{
    switch (n)
    {   
        case 0: luz=GL_LIGHT0;
        break;
        case 1: luz=GL_LIGHT1;
        break;
        case 2: luz=GL_LIGHT2;
        break;
        case 3: luz=GL_LIGHT3;
        break;
        case 4: luz=GL_LIGHT4;
        break;
        case 5: luz=GL_LIGHT5;
        break;
        case 6: luz=GL_LIGHT6;
        break;
        case 7: luz=GL_LIGHT7;
        break;
        default: luz=GL_LIGHT0;

    }

    setValoresIniciales();
    encendida=false;
}

void Iluminacion::setAmbient(float a, float b, float c, float d)
{
    ambient[0]=a;
    ambient[1]=b;
    ambient[2]=c;
    ambient[3]=d;

}
void Iluminacion::setSpecular(float a, float b, float c, float d)
{
    specular[0]=a;
    specular[1]=b;
    specular[2]=c;
    specular[3]=d;
}
void Iluminacion::setPosition(float a, float b, float c, float d)
{
    position[0]=a;
    position[1]=b;
    position[2]=c;
    position[3]=d;
}
void Iluminacion::setDiffuse(float a, float b, float c, float d)
{
    diffuse[0]=a;
    diffuse[1]=b;
    diffuse[2]=c;
    diffuse[3]=d;
}

void Iluminacion::conmutar()
{
    if(encendida) apagar();
    else encender();
}

void Iluminacion::encender() // interruptor
{
    encendida=true;
    glEnable(luz);
    glLightfv(luz, GL_AMBIENT, ambient);
    glLightfv(luz, GL_DIFFUSE, diffuse);
    glLightfv(luz, GL_SPECULAR, specular);
    glLightfv(luz, GL_POSITION, position);
    
}
void Iluminacion::apagar()
{
    encendida=false;
    glDisable(luz);
}

void Iluminacion::setValoresIniciales()
{
    setAmbient(0.141, 0.91,0.066, 1.0);
    setDiffuse(0.141, 0.91,0.066, 1.0);
    setPosition(100.0, 100.0, -100.0, 1.0);
    setSpecular(0.141, 0.91,0.066, 1.0);
}
void Iluminacion::posicionar()
{
    glLightfv(luz, GL_POSITION, position);
}
