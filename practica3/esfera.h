#ifndef _ESFERA_H
#define _ESFERA_H

#include "solidoRevolucion.h"

class Esfera : public SolidoRevolucion
{
    public:
        Esfera(float radio=10.0);
};
#endif