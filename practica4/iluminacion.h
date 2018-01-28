#ifndef _ILUMINACION_H
#define _ILUMINACION_H
#include <OpenGL/gl.h>
#include <vector>

class Iluminacion
{
    private:
        bool encendida;
        GLenum luz;
        GLfloat ambient[4];
        GLfloat diffuse[4];
        GLfloat specular[4];
        GLfloat position[4];

    public:
        Iluminacion( int numero_foco=0 );
        void encender();
        void apagar();
        void conmutar(); 
        void setAmbient(float, float, float, float);
        void setDiffuse(float, float, float, float);
        void setSpecular(float, float, float, float);
        void setPosition(float, float, float, float);
        void setValoresIniciales();
        void posicionar();

};
#endif