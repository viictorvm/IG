#ifndef _SOLIDO_REVOLUCION_H
#define _SOLIDO_REVOLUCION_H

#include "objeto3D.h"
#include "file_ply_stl.h"


class SolidoRevolucion: public Objeto3D
{
    private:
        int  n_revoluciones;
        string fichero;
        bool tapas;
        vector<Vertices> full_vertices;  //guardaremos todos los vertices sin depender de si queremos o no tapas
        vector<Caras> full_caras; // lo mimo con las caras

    public:
        SolidoRevolucion(){}
        SolidoRevolucion(vector<Vertices> v, int n, bool);
        SolidoRevolucion(string fichero, int n, bool);
        Vertices rotar(Vertices p, float);
        void revolution(vector<Vertices> perfil, int n=15, bool tapas=true);
        double pasarRadianes(double);
        int getN();
        bool getTapas();
        string getFichero();
        void modificar_tapas(bool);
};
#endif


/*
Pasos:

1- introducimos todos los vertices del perfil en el vector de vertices.
2- vamos a rotar todos los vertices del perfil.
3- volvemos a añadir los vertices al vector, como en el paso 1.
4- volvemos a rotar los vertices , y mismo procedimiento.

*/