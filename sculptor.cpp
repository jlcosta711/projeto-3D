#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

//Construtor da classe
Sculptor::Sculptor(int nx, int ny, int nz){
    this->nx = nx;
    this->ny = ny;
    this->nz = nz;
    fix = 0.5;
    r = 0.5;
    g = 0.5; 
    b = 0.5;
    a = 0.5;
    //Alocacao dinamica da matriz 3D
    v = new Voxel**[nx];
     for (int i =0; i<nx; i++){
      v[i] = new Voxel*[ny];

     for (int j =0; j<ny; j++){
       v[i][j]= new Voxel[nz];
      }
    }
}
//Destrutor da classe
Sculptor::~Sculptor(){
    for(int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
               delete[] v[i][j];
            }
        }
        for (int i=0; i <nx; i++){
            delete[] v[i];
        }

        delete[] v;

        nx = 0;
        ny = 0;
        nz = 0;}
/*Ativa os Voxel na posicao (x,y,z)(fazendo isOn = true) e atribui ao mesmo a cor atual de desenho*/
void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;    

}
// /*Desativa o voxel na posicao (x,y,z) (fazendo isOn = false)
void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}
/*Define a cor atual de desenho nos parametros da tabela rgb*/
void Sculptor::setColor(float r, float g, float b, float alpha) 
{
    this-> r = r;
    this-> g = g;
    this-> b = b;
    a = alpha;
}
/*Ativa todos os voxels no intervalo x[x0,x1], y[y0,y1], z[z0,z1] e atribui aos mesmos a cor atual de desenho*/
void  Sculptor::putBox ( int x0_, int x1_, int y0_, int y1_, int z0_, int z1_){
    for ( int x = x0_; x<x1_; x++){
       for ( int y = y0_; y<y1_; y++){
           for ( int z = z0_; z<z1_; z++){
               v[x][y][z]. isOn = true ;
               v[x][y][z]. r = r;
               v[x][y][z]. g = g;
               v[x][y][z]. b = b;
               v[x][y][z]. a = a;
           }
       }
    }
    
}
/* todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1*/
void  Sculptor::cutBox ( int x0, int x1, int y0, int y1, int z0, int z1)
{
    for ( int x = x0; x<x1; x++){
       for ( int y = y0 ; y< y1 ; y++){
           for ( int z = z0; z<z1; z++){
               v[x][y][z]. isOn = false ;
           }
       }
    }
}
/*ativa todos os voxels que satisfazem à equação da esfera e atribui aos mesmos a cor atual de desenho (r,g,b,a)*/
void  Sculptor::putSphere ( int xcenter, int ycenter, int zcenter, int radius){
  for ( int i = -radius; i<=radius; i++){
      for ( int j = -radius; j<=radius; j++){
          for ( int k = -radius; k<=radius; k++){
         
            if ((i*i+j*j+k*k) < radius*radius){
              putVoxel (i+xcenter,j+ycenter,k+zcenter);
            }
          }
      }
  }

}
/*Desativa todos os voxels que satisfazem à equação da esfera*/
void  Sculptor::cutSphere ( int xcenter, int ycenter, int zcenter, int radius){
  for ( int i = -radius; i<radius; i++){
      for ( int j = -radius; j<radius; j++){
          for ( int k = -radius; k<radius; k++){
            if ((i*i+j*j+k*k) < radius*radius){
              cutVoxel (i+xcenter,j+ycenter,k+zcenter);
            }
          }
      }
  }
}
/*Ativa todos os voxels que satisfazem à equação do elipsóide e atribui aos mesmos a cor atual de desenho*/
void  Sculptor::putEllipsoid ( int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
   float newx, newy, newz;

    for ( int x = 0 ; x < nx; x++){
        for ( int y = 0 ; y < ny; y++){
            for ( int z = 0 ; z < nz; z++){
            newx = (( float )(x-xcenter)*( float )(x-xcenter))/(rx * rx);
            newy = (( float )(y-ycenter)*( float )(y-ycenter))/(ry * ry);
            newz = (( float )(z-zcenter)*( float )(z-zcenter))/(rz * rz);

            if ((newx + newy + newz) < 1 ){
                putVoxel (x,y,z);
            }
            }
        }
    }
}
/*Desativa todos os voxels que satisfazem à equação do elipsóide*/
void  Sculptor::cutEllipsoid ( int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
   double newx, newy, newz;

    for ( int x = 0 ; x < nx; x++){
        for ( int y = 0 ; y < ny; y++){
            for ( int z = 0 ; z < nz; z++){
            newx = (( float )(x-xcenter)*( float )(x-xcenter))/(rx * rx);
            newy = (( float )(y-ycenter)*( float )(y-ycenter))/(ry * ry);
            newz = (( float )(z-zcenter)*( float )(z-zcenter))/(rz * rz);

            if ((newx + newy + newz) < 1 ){
                cutVoxel (x,y,z);
            }
            }
        }
    }
}
/*Grava a escultura no formato OFF no arquivo filename*/
void Sculptor::writeOFF(char *filename){

  std::ofstream fout;
  
  fout.open(filename);
  if(!fout.is_open()){
    std::cout << "deu errado\n";
    exit(1);
  }
  
  int quantvox=0;
  int ref;
  fout << "OFF\n";
 // Confere todos os voxel e analisa os que devem ser exibidos no .off
 for (int i = 0; i < nx; i++){
      for (int j = 0; j <ny; j++){
           for (int k = 0; k <nz; k++){
                if(v[i][j][k].isOn == true){
                quantvox++;
                }
           }
       }
  }
   fout<<quantvox * 8<<" "<<quantvox * 6 << " " << "0" << "\n";//Mostra a quantidade total de vertices, faces e arestas

  for (int a = 0; a < nx; a++){
      for (int b = 0; b < ny; b++){
           for (int c = 0; c < nz; c++){
                if(v[a][b][c].isOn == true){
                fout << a - fix << " " << b + fix << " " << c - fix << "\n" << flush;
                fout << a - fix << " " << b - fix << " " << c - fix << "\n" << flush;
                fout << a + fix << " " << b - fix << " " << c - fix << "\n" << flush;
                fout << a + fix << " " << b + fix << " " << c - fix << "\n" << flush;
                fout << a - fix << " " << b + fix << " " << c + fix << "\n" << flush;
                fout << a - fix << " " << b - fix << " " << c + fix << "\n" << flush;
                fout << a + fix << " " << b - fix << " " << c + fix << "\n" << flush;
                fout << a + fix << " " << b + fix << " " << c + fix << "\n" << flush;
                }
           }
      }
  }

  quantvox = 0;

  //Descrever cada voxel
  for (int a= 0; a<nx; a++){
      for (int b = 0; b<ny; b++){
           for (int c= 0; c<nz; c++){
                if(v[a][b][c].isOn == true){
                ref = quantvox * 8;
                fout << fixed; 


                //Montar linha que realiza a construção das faces a partir do vertices e mostrar as propriedades rgba do voxel
                fout << "4" << " " << 0+ref << " " << 3+ref << " " << 2+ref << " " << 1+ref << " ";
                fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

               fout << "4" << " " << 4+ref << " " << 5+ref << " " << 6+ref << " " << 7+ref << " ";
                fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                fout << "4" << " " << 0+ref << " " << 1+ref << " " << 5+ref << " " << 4+ref << " ";
                fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                fout << "4" << " " << 0+ref << " " << 4+ref << " " << 7+ref << " " << 3+ref << " ";
                fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                fout << "4" << " " << 3+ref << " " << 7+ref << " " << 6+ref << " " << 2+ref << " ";
                fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                fout << "4" << " " << 1+ref << " " << 2+ref << " " << 6+ref << " " << 5+ref << " ";
                fout << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

                quantvox = quantvox + 1;
                }
           }
       }
  }
  fout.close();
} 
