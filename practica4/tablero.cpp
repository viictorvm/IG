#include <cstdio>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "tablero.h"
#include <cmath>

Tablero::Tablero(int n)
{    
    n = 4;
    int tamVertices=0;
    int aumentar=10;
    float distancia=(float)1.0/(n-1);
    float texturaX=0.0;
    float texturaY=0.0;
    for(int i=0;i<n;i++)
    {
        vertices.push_back(Vertices(i*aumentar, 0.0,0.0)); // hacemos la primera fila, empezando por abajo
        //vertices_texturas.push_back(Vertices2D(texturaX,0.0));
      //  cout<< "(" << texturaX << "," << 0.0 << ") "; 
        texturaX+=distancia;
    }
    cout <<"\n";
    for(int j=1;j<n;j++)
    {
        texturaX=distancia;
        texturaY+=distancia;
        vertices.push_back(Vertices(0.0,j*aumentar,0.0));  // 
        //vertices_texturas.push_back(Vertices2D(0.0, texturaY));
       // cout<< "(" << 0.0 << "," << texturaY << ") ";
        for(int x=1;x<n;x++)
        {  // cout<< "(" << texturaX << "," << texturaY << ") "; 
           // vertices_texturas.push_back(Vertices2D(texturaX, texturaY));
            vertices.push_back(Vertices(x*aumentar, j*aumentar, 0.0));
            tamVertices=vertices.size()-1;
            caras.push_back(Caras(tamVertices-1, tamVertices-1-n, tamVertices-n));
            caras.push_back(Caras(tamVertices, tamVertices-1, tamVertices-n));
            texturaX+=distancia;

        }
                    cout <<"\n";
    }
    
     float contadorx=1.0;
    float contador=0.0;
    for(int i=0;i<n;i++)
    {
        contador=0.0;
         for(int j=0;j<n;j++)
        {
           //  cout<< "(" << contador << "," << contadorx << ") ";
            vertices_texturas.push_back(Vertices2D(contador, contadorx));
            contador+=distancia;

        }
        cout << "\n";
        contadorx-=distancia;

    }

    //girarTextura(360.0);
    crearNormalesCaras();

}
 void Tablero::desplazarTextura(float incremento)
 {
    for(int i=0;i<vertices_texturas.size();i++)
    {
        vertices_texturas[i]=Vertices2D(vertices_texturas[i].v1+incremento,vertices_texturas[i].v2);
    }
 }
 void Tablero::girarTextura(float grados)
 {
      
     for(int i=0;i<vertices_texturas.size();i++)
     {
        
         float x=vertices_texturas[i].v1* cos(grados) - vertices_texturas[i].v2*sin(grados);
         float y=vertices_texturas[i].v2* cos(grados) + vertices_texturas[i].v1* sin(grados);
            vertices_texturas[i]=Vertices2D(x , y);
     }
    
 }
