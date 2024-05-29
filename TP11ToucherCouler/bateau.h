/*****************************************************************
Auteurs : KORTAM Nirmine, SEYE Fatou DARGERE Lucas et LAVAUX Bastien
projet : projet SMP 1er Année "Bataille Navale"
Date : 22 mai 2024
But : fichier En-tete de la classe bateau
Description : classe permettant de créer des bateau de différentes tailles et de gérés leurs vies

*****************************************************************/
#pragma once

#include "case.h"
#include <iostream>
using namespace std;

class Bateau {

protected:

  string nom;
  int longueur;
  int vie;
  

public:
  Bateau(int taille);
  //Case position[longueur]
  

  //accesseurs en lecture
  int getLong();
  string getnom();
  bool EStCoule() const;

  //accesseurs en ecriture
  bool estCoule() const;

};

/*
class porte_avion: public bateau {

public:

  porte_avion(Case c, string direction);
  void setnom(string nom);
  void setlong(int longueur);
  void settbl(bool statut);

};

class croisiere: public bateau {
  
private:

  croisiere(Case c, string direction);
  Case tbl_pos[long];

public:

void setnom(string nom);
void setlong(int longueur);
void settbl(bool statut);
  
};


class torpilleur: public bateau {


private:

  torpilleur(Case c, string direction);
  Case tbl_pos(long);

public:

  void setnom(string nom);
  void setlong(int longueur);
  void settbl(bool statut);

};


class contre_torpilleur: public bateau {

private:

  contre_torpilleur(Case c, string direction);
  Case tbl_pos(long);

public:

  void setnom(string nom);
  void setlong(int longueur);
  void settbl(bool statut);

};*/