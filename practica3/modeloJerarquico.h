#ifndef _MODELO_JERARQUICO_H
#define _MODELO_JERARQUICO_H

#include "objeto3d.h"
#include "cubo.h"
#include "esfera.h"

class ModeloJerarquico : public Objeto3D
{
    protected:
        Cubo cubo;
        Esfera esfera;

        float tam_c=50.0;
        float tam_e=5.0;
        float w=10.0;
        float body_size_y=100.0;
        float libertad1,libertad3;
        int libertad2;
        int libertad4;

        float ancho_cuerpo;
        float altura_cuerpo;
        float _x;

        float ancho_muslo;
        float alto_muslo;

        int grados_brazos;

        float ancho_cabeza;
        float alto_cabeza;

        float factor_cuello;
        float largo_cuello;
    public:
        ModeloJerarquico();
        void draw_mj();
        void ojo();
        void pierna_izq(float libertad1, float posicion=60.0);
        void pierna_dcha(float libertad1);
        void cuerpo(int libertad2);
        void muslo();
        void cabeza(float libertad3);
        void brazo_izq(int posicion_brazos);
        void brazo_dcha();
        void setLibertad1(float &);
        void setLibertad2(int &);
        void setLibertad3(float &);
        void setLibertad4(int &);
        void minicuello();

};
#endif