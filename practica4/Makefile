# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica4

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
#
CFLAGS=    -g -I/usr/include -I. -lSDL2
CXXFLAGS=  -g -O3 -I/usr/include -I. -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2
# -I/Library/Frameworks/SDL2_image.frameworks  #-I/opt/X11/include


# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
#LDFLAGS=  -lGLU -lGL -lglut
LDFLAGS= -framework GLUT -framework OpenGL -framework Cocoa -framework SDL2 -framework SDL2_image
# definicion del compilador
#
CC = g++

# definicion de objetos
#
OBJECTS= practica4.o escena.o ejes.o objeto3D.o cubo.o tetraedro.o octaedro.o casa3d.o solidoRevolucion.o objetoPly.o file_ply_stl.o esfera.o modeloJerarquico.o iluminacion.o tablero.o textura.o 
# orden que sera ejecutada por defecto 
#
default : $(TARGETS)

# regla de ejecucion
#
$(TARGETS) : $(OBJECTS)
	$(CC) -o $@ $(CXXFLAGS) $(OBJECTS) $(LDFLAGS)

#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *

