#include<iostream>
#include<fstream>
#include<fstream>
#include<string>
#include "sculptor.h"
using namespace std;


int main() {

  //criacao da classe principal
  Sculptor campo(61,61,60);

  //monta o campo
  campo.setColor(0,1,0,1);
  campo.putBox(19,20,0,41,0,21);

  //marcacao lateral
  campo.setColor(1,1,1,1);
  campo.putBox(19,20,1,2,1,20);

  //linha trave
  campo.setColor(1,1,1,1);
  campo.putBox(19,20,1,40,1,2);
  //marcacao lateral
  campo.setColor(1,1,1,1);
  campo.putBox(19,20,39,40,1,20);
  //linha trave
  campo.setColor(1,1,1,1);
  campo.putBox(19,20,1,40,19,20);
  //marcacao meio campo
  campo.setColor(1,1,1,1);
  campo.putBox(19,20,20,21,1,20);
  //circulo do meio campo
  campo.setColor(1,1,1,1);
  campo.putVoxel(19,17,10);
  campo.putVoxel(19,18,11);
  campo.putVoxel(19,19,12);
  campo.putVoxel(19,18,9);
  campo.putVoxel(19,19,8);
  campo.putVoxel(19,23,10);
  campo.putVoxel(19,22,11);
  campo.putVoxel(19,21,12);
  campo.putVoxel(19,22,9);
  campo.putVoxel(19,21,8);
  //marcacao da area de 1 a 6 no eixo y;
  campo.putBox(19,20,1,5,5,6);
  campo.putBox(19,20,1,5,15,16);
  campo.putBox(19,20,5,6,5,16);
  //marcacacao da area de 35 a 40
  campo.putBox(19,20,35,40,5,6);
  campo.putBox(19,20,35,40,15,16);
  campo.putBox(19,20,35,36,5,16);
  //trave de y=1,2
  campo.putBox(19,23,1,2,6,7);
  campo.putBox(19,23,1,2,13,14);
  campo.putBox(23,24,1,2,6,14);
  //trave em y=39,40
  campo.putBox(19,23,39,40,7,8);
  campo.putBox(19,23,39,40,13,14);
  campo.putBox(23,24,39,40,7,14);
  //boneco
  //chuteira
  campo.setColor(0,0,0,1);
  campo.putBox(20,21,18,21,5,6);
  campo.cutVoxel(20,19,5);
  //perna
  campo.setColor(0.9,0.8,0.7,1);
  campo.putBox(21,23,18,21,5,6);
  campo.cutVoxel(22,19,5);
  campo.cutVoxel(21,19,5);
  //bermuda
  campo.setColor(0,0,1,1);
  campo.putBox(23,25,17,22,5,6);
  //camisa
  campo.setColor(1,1,0,1);
  campo.putBox(25,28,17,22,5,6);
  //pescoço
  campo.setColor(0.9,0.8,0.7,1);
  campo.putBox(28,29,19,20,5,6);
  //cabeça
  campo.putBox(29,32,17,22,4,7);
  campo.setColor(0,0,0,0.5);
  campo.putVoxel(30,18,6);
  campo.putVoxel(30,20,6);
  campo.putBox(32,33,17,22,4,7);
  //bracos
  campo.setColor(1,1,0,1);
  campo.putBox(27,28,16,17,5,6);
  campo.putBox(27,28,22,23,5,6);
  campo.setColor(0.9,0.8,0.7,1);
  campo.putBox(28,32,16,17,5,6);
  campo.putBox(28,32,22,23,5,6);
  //bola
  campo.setColor(1,1,1,1);
  campo.putVoxel(20,20,7);
  

campo.writeOFF((char*)"campo.off");

  /*teste das funcoes que nao foram usadas na classe principal campo*/
    /* Sculptor teste(60,60,60);
    teste.setColor(1,1,0,1);
    teste.putSphere(40,40,40,10);
    teste.cutSphere(20,20,20,10);
    
    teste.setColor(1,0.54,1,1);
    teste.putEllipsoid(20,20,20,15,10,7);
    teste.cutEllipsoid(20,20,19,14,9,8);
  teste.writeOFF((char*)"teste.off");*/

}
