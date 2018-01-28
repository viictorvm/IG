#ifndef _OBJETO_PLY_H
#define _OBJETO_PLY_H

#include "objeto3D.h"

class ObjetoPly: public Objeto3D
{
    public:
      ObjetoPly(){}
      ObjetoPly(string fichero);
};
#endif