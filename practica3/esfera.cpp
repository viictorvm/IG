#include <cstdio>
#include <iostream>
#include "esfera.h"
#include <cmath>

Esfera::Esfera(float radio)
{
    for(float angulo=(3.14)/2; angulo<(3.14/2)*3;angulo+=3.14/10)
    {
        vertices.push_back(Vertices(cos(angulo)*radio, sin(angulo)*radio, 0));
    }
    revolution(vertices,10, false);
}