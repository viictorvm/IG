//******************************************************************************
// class to read ply files of triangles
//
// Domingo Martín Perandres (c) 2017
//
// Gnu Public Licence
//******************************************************************************

#include "file_ply_stl.h"

using namespace std;

//******************************************************************************
//
//******************************************************************************

int _file_ply::open(const string &File_name)
{
  File.open(File_name.c_str(),ios::in);

  if (File.good()) return 1;
  else {
    cout << "Error: the file " << File_name << " cannot be opened" << endl;
    return 0;
  }
}

//******************************************************************************
//
//******************************************************************************

void _file_ply::get_token(istringstream &Line_stream1,string &Token1)
{
//  cout <<  "buscando en:" << Line_stream1.str() << endl;
  getline(Line_stream1,Token1,' ');
//  cout <<  "salida:" << Token1 << endl;
}

//******************************************************************************
//
//******************************************************************************

bool _file_ply::get_new_line(ifstream &File,istringstream &Line_stream)
{
  string Line;
  if (getline(File,Line)){
//    cout << "leido:" << Line << endl;
    Line_stream.str(Line);
    Line_stream.seekg(0);
    return true;
  }
  else return false;
}


//******************************************************************************
//
//******************************************************************************

void _file_ply::read(vector<Vertices> &vertices,vector<Caras> &caras)
{
  vector<float> Verticesf;
  vector<float> Triangles;
  string Token;
  istringstream Line_stream;

  setlocale(LC_ALL, "C");

  get_new_line(File,Line_stream);
  get_token(Line_stream,Token);
  if(Token=="ply"){
    get_new_line(File,Line_stream);
    get_token(Line_stream,Token);
    if(Token=="format"){
      get_token(Line_stream,Token);
      if(Token=="ascii"){
        do{
          get_new_line(File,Line_stream);
          get_token(Line_stream,Token);
        } while (Token!="element");
        get_token(Line_stream,Token);
        if(Token=="vertex"){
          get_token(Line_stream,Token);
          Verticesf.resize(stoi(Token)*3);
          do{
            get_new_line(File,Line_stream);
            get_token(Line_stream,Token);
          } while (Token!="element");
          get_token(Line_stream,Token);
          if(Token=="face"){
            get_token(Line_stream,Token);
            Triangles.resize(stoi(Token)*3);
            do{
              get_new_line(File,Line_stream);
              get_token(Line_stream,Token);
            } while (Token!="end_header");
            for (unsigned int i=0;i<Verticesf.size()/3;i++)
            {
              get_new_line(File,Line_stream);
              
              get_token(Line_stream,Token);
              Verticesf[i*3]=stof(Token);
              get_token(Line_stream,Token);
              Verticesf[i*3+1]=stof(Token);
              get_token(Line_stream,Token);
              Verticesf[i*3+2]=stof(Token);

              vertices.push_back(Vertices(Verticesf[i*3]*30,Verticesf[i*3+1]*30,Verticesf[i*3+2]*30));

            // cout << " leido " << vertices[i].v1 << " " << vertices[i].v2 << " " << vertices[i].v3 << endl;
            }
            for (unsigned int i=0;i<Triangles.size()/3;i++){
              get_new_line(File,Line_stream);
              
              get_token(Line_stream,Token);
              if (stoi(Token)==3)
              {
                get_token(Line_stream,Token);
                Triangles[i*3]=stoi(Token);
                get_token(Line_stream,Token);
                Triangles[i*3+1]=stoi(Token);
                get_token(Line_stream,Token);
                Triangles[i*3+2]=stoi(Token);

                caras.push_back(Caras(Triangles[i*3],Triangles[i*3+1],Triangles[i*3+2]));

              }
            }
          }
          else{
            cerr << "Error: no face element found" << endl;
          }
        }
        else{
          cerr << "Error: no vertex element found" << endl;
        }
      }
      else{
        cerr << "Error: only ascii format is allowed" << endl;
      }
    }
    else{
      cerr << "Error: no format found" << endl;
    }
  }
  else{
    cerr << "Error: the file is not a PLY file" << endl;
  }
}

//******************************************************************************
//
//******************************************************************************

void _file_ply::close()
{
  File.close();
}

