#include <cstdio>
#include <iostream>
#include "esfera.h"
#include <cmath>

#define M_PI

Esfera::Esfera()
{
    for(float angulo=(3.14)/2; angulo<(3.14/2)*3;angulo+=3.14/100)
    {
        vertices.push_back(Vertices(cos(angulo)*10, sin(angulo)*10, 0));
    }
    revolution(vertices,100 , false);
}