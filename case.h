/*****************************************************************
Auteurs : KORTAM Nirmine, SEYE Fatou DARGERE Lucas et LAVAUX Bastien
projet : projet SMP 1er Année "Bataille Navale"
Date : 22 mai 2024
But : fichier en-tete de la classe case
Description : classe permettant de créer des cases de différentes types pour définir ceux qu'elles continnent

*****************************************************************/

#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;


class Case{

private:
  char x;
  int y;
  int status;

public:

//constructeur
  Case();
  Case(char x, int y, int status);

  
//getter
  char getx() const;

  int gety() const;

  int getstatus(); 

//setter
  void setx(char x);

  void sety(int y);

  void setstatus(int status);
};

