 #include <cstdio>
#include <iostream>
#include "textura.h"

Textura::Textura(const char * fichero)
{
    Surface = IMG_Load(fichero);
}
void Textura::activarTextura()
{
    glBindTexture(GL_TEXTURE_2D, TextureID);
     glEnable(GL_TEXTURE_2D);
}
void Textura::desactivarTextura()
{
    glDisable(GL_TEXTURE_2D);
}
void Textura::cargarTextura()
{     
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    
    int Mode = GL_RGB;
    
    if(Surface->format->BytesPerPixel == 4) {
        Mode = GL_RGBA;
    }
 
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
