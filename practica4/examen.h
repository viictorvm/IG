#ifndef _EXAMEN_H
#define _EXAMEN_H

#include <OpenGL/gl.h>
#include <string>
#include <GLUT/glut.h>
#include "objeto3D.h"
#include "modeloJerarquico.h"
#include "cubo.h"

class Examen : public Objeto3D
{
    private:
        SolidoRevolucion sr;
        Cubo c;
    
    public:
        Examen();
        void pintar();
        
};

#endif