/*****************************************************************
Auteurs : KORTAM Nirmine, SEYE Fatou DARGERE Lucas et LAVAUX Bastien
projet : projet SMP 1er Année "Bataille Navale"
Date : 22 mai 2024
But : fichier source de la classe bateau
Description : classe permettant de créer des bateau de différentes tailles et de gérés leurs vies

*****************************************************************/

#include "bateau.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Bateau::Bateau(int taille){
  longueur = taille;
  if(taille == 5)
  {
    nom = "porte-avion";
    vie = taille;
  }
  else if(taille == 4)
  {
    nom = "croiseur";
    vie = taille;
  }
  else if(taille == 3)
  {
    nom = "contre-torpilleur";
    vie = taille;
  }
  else{
    nom = "torpilleur";
    vie = taille;
  }
}

string Bateau::getnom(){
    return nom;
}

int Bateau::getLong(){
    return longueur;
}

/*bool Plateau::PlacerBateau(Bateau& bateau, int x, int y, char orientation) {
    int taille = ship.getTaille();
    if (orientation == 'H') {
        if (x + taille > LMAX) return false;
        for (int i = 0; i < taille; ++i) {
            if (plateau[x + i][y].hasShip()) return false;
        }
        for (int i = 0; i < taille; ++i) {
            plateau[x + i][y].placeShip();
        }
    } else if (orientation == 'V') {
        if (y + taille > HMAX) return false;
        for (int i = 0; i < taille; ++i) {
            if (plateau[x][y + i].hasShip()) return false;
        }
        for (int i = 0; i < taille; ++i) {
            plateau[x][y + i].placeShip();
        }
    } else {
        return false;
    }
    ships.push_back(ship);
    return true;
}
*/