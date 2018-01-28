#include <cstdio>
#include <iostream>
#include "solidoRevolucion.h"
#include <cmath>

#define _USE_MATH_DEFINES
#define M_PI           3.14159265358979323846  /* pi */


SolidoRevolucion::SolidoRevolucion(string f, int n, bool tapas)
{
    fichero=f;
    _file_ply File_ply;
    vector<Vertices> v;
    if (File_ply.open(f))
    {
        File_ply.read(v,caras);
    }

    revolution(v, n, tapas);
}

SolidoRevolucion::SolidoRevolucion(vector<Vertices> v, int n, bool tapas)
{
    revolution(v, n, tapas);
}

Vertices SolidoRevolucion::rotar(Vertices p, float ang)
{
    float xgi = (p.v1 * cos(ang)+ p.v3*sin(ang));                                   
    float zgi = (p.v1*-sin(ang)+p.v3*cos(ang)); 
    
    Vertices prot(xgi,p.v2,zgi);
    
    return prot;
}

double SolidoRevolucion::pasarRadianes(double grados)
{
    return grados*M_PI/180.0;
}


void SolidoRevolucion::revolution(vector<Vertices> perfil, int n, bool tapas)
{
    n_revoluciones=n;
    double angulo=360.0/n;
    double angulo_actual=angulo;
    Vertices primero, ultimo;
    bool pcambiados=true;

    if(perfil.front().v2 < perfil.back().v2)  //para ver si empezamos desde la parte de abajo de la figura
    {
        pcambiados=false;
        reverse(perfil.begin(), perfil.end());
    }
    
    if(perfil[0].v1==0.0 && perfil[0].v3==0.0) // miramos si el primer punto es tapa
    {
        primero=perfil[0];
        perfil.erase(vertices.begin());
    } 
    else
    {
        primero.v1=primero.v3=0.0;   // sino hay ningun punto que coincida con el eje y, lo creamos
        primero.v2=perfil[0].v2;
    }
    if(perfil[perfil.size()].v1==0.0 && perfil[perfil.size()].v3==0.0) // igual con el ultimo punto
    {
        ultimo.v1=ultimo.v3=0.0;
        ultimo.v2=perfil[perfil.size()-1].v2;
        perfil.pop_back();
    }
    else
    {
        ultimo.v1=ultimo.v3=0.0;
        ultimo.v2=perfil[perfil.size()-1].v2;
    }

    caras.clear();
    vertices=perfil;
    
    int tam=perfil.size();
    
    for(int i=0;i<n;i++) //vamos a girarlo segun las vueltas que queramos dar
    {
        for(int index=0;index<tam;index++) //tenemos hacerlo por cada punto q nos dan en el perfil
        {
            vertices.push_back(rotar(perfil[index],pasarRadianes(angulo_actual)));                
        }
        angulo_actual+=angulo;
    }
    

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < perfil.size()-1; k++)
        {
            // caras pares 
            int _0 = k+((1+i) % n)*perfil.size();
            int _1 = k+1+((1+i) % n)*perfil.size();
            int _2 = k+1+i*perfil.size();
            
            caras.push_back(Caras(_1,_0, _2));
            
            // cara impares 
            _0 = k+1+i*perfil.size();
            _1 = k+i*perfil.size();
            _2 = k+((i+1)%n)*perfil.size();
        
            caras.push_back(Caras(_1,_0,_2));
        }
    }
    if(tapas)
    {
        //caras de las tapas 
        vertices.push_back(primero); //punto para la tapa de arriba
        vertices.push_back(ultimo); //punto para la tapa de abajo
        int j=0;
        int i;
        for(i=0;i<=n;i++) // creamos las tapas
        {
            caras.push_back(Caras(j,(j+perfil.size())%vertices.size(),vertices.size()-2));
            
            j+=perfil.size();
        }
        j=perfil.size()-1;
        for(i=0;i<=n;i++)
        {
           caras.push_back(Caras((j+perfil.size())%vertices.size(),j,vertices.size()-1));
            
            j+=perfil.size();
        }
    }

    full_vertices=vertices;
    full_caras=caras;

    crearNormalesCaras();
}


int SolidoRevolucion::getN()
{
    return n_revoluciones;
}
bool SolidoRevolucion::getTapas()
{
    return tapas;
}
string SolidoRevolucion::getFichero()
{
    return fichero;
}
void SolidoRevolucion::modificar_tapas(bool tapas)
{
    vertices.clear();
    caras.clear();
    if(tapas)
    {
        vertices=full_vertices;
        caras=full_caras;
    }
    else
    {
        vertices.insert(vertices.begin(), full_vertices.begin(), full_vertices.end()-2);
        caras.insert(caras.begin(), full_caras.begin(), full_caras.end()-(2*n_revoluciones)-2);
    }
}

