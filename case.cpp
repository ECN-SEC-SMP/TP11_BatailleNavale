/*****************************************************************
Auteurs : KORTAM Nirmine, SEYE Fatou DARGERE Lucas et LAVAUX Bastien
projet : projet SMP 1er Année "Bataille Navale"
Date : 22 mai 2024
But : fichier source de la classe case
Description : classe permettant de créer des cases de différentes types pour définir ceux qu'elles continnent

*****************************************************************/

#include "case.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

#define EAU 0
#define BATEAU 1
#define COULE 2
#define FAIL 3
#define INTERDIT 4


Case::Case(){
  x=0;
  y=0;
  status = EAU;
}

Case::Case(char x, int y,int status){//constructeur
  this->x = x;
  this->y = y;
  
};

char Case::getx() const{ return x;}

int Case::gety() const{ return y;}

int Case::getstatus() { return status;}


void Case::setx(char x) { this->x = x;}

void Case::sety(int y) { this->y = y;}

void Case::setstatus(int status) { this->status = status;}







