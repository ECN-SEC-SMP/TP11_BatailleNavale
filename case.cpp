/**
 * @file bateau.h
 * @authors KORTAM Nirmine, SEYE Fatou, 
 *          DARGERE Lucas, LAVAUX Bastien
 * @date 22 mai 2024
 * @brief Création de la classe case.
 * @details Mise en place d'une classe case qui permettra de donner des 
 * coordonnées et son état.
 */


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







