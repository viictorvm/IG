#include "file_ply_stl.h"
#include "objetoPly.h"

ObjetoPly::ObjetoPly(string fichero)
{
    _file_ply File_ply;

    if (File_ply.open(fichero))
    {
        File_ply.read(vertices,caras);
        std::cout << "File read correctly in ply class" << std::endl;
    }
}

