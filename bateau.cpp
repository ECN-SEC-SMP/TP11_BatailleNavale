
/**
* @file bateau.h
* @authors KORTAM Nirmine, SEYE Fatou, 
*          DARGERE Lucas, LAVAUX Bastien
* @date 22 mai 2024
* @brief Définition de la classe bateau.  
* @details Mise en place d'une classe Bateau qui permettra de donner un nom au
* bateau, une taille (5, 4, 3, 3, 2), leur état de vie et leur position dans le
* plateau de jeu.
*/

#include "bateau.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <vector>
using namespace std;



Bateau::Bateau(int taille) { 

/** 
*@brief Définition du constructeur, qui prend en paramètre la taille du bateau,
*et qui initialise les variables de la classe.
*/ 
    
  longueur = taille;
  if (taille == 5) {
    nom = "porte-avion";
    vie = taille;
  } else if (taille == 4) {
    nom = "croiseur";
    vie = taille;
  } else if (taille == 3) {
    nom = "contre-torpilleur";
    vie = taille;
  } else {
    nom = "torpilleur";
    vie = taille;
  }
}


/** 
*@brief Définition de la méthode getnom qui retourne le nom du bateau.
*/

string Bateau::getnom() { return nom; }

/** 
*@brief Définition de la méthode getLong, qui retourne la longueur du bateau.*/

int Bateau::getLong() { return longueur; } 

/**
 Définition de la méthode getvie, qui retourne la vie du bateau.*/

int Bateau::getvie() { return vie; } 

/** Définition de la méthode writePosition, qui ajoute une coordonnée à la liste position.
*/
/** Définition de la méthode writePosition, qui ajoute une coordonnée à la liste position.*/

void Bateau::writePosition(int coordonne) { position.push_back(coordonne);                             }  


/** Définition de la méthode getPosition, qui retourne la liste position.*/
/** Définition de la méthode getPosition, qui récupère la valeur de l'attribut position sans le toucher.
*/
int Bateau::getPosition(int i){
    return position[i];
}

/** Définition de la méthode getvie, qui retourne la vie du bate */

/** Définition de la méthode diminuerVie, qui diminue la vie du bateau.
*/
void Bateau::diminuerVie() {
    vie--; }


