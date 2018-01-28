#ifndef _TEXTURA_H
#define _TEXTURA_H

#include <OpenGL/gl.h>
#include <string>
#include <GLUT/glut.h>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


using namespace std;

class Textura
{
    private:
    SDL_Surface* Surface;
    GLuint TextureID;
        
    public:
        Textura(const char * );
        void activarTextura();
        void desactivarTextura();
        void cargarTextura();
       
        
}; 
#endif