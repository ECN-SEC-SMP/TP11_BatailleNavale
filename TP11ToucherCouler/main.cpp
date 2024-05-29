/*****************************************************************
Auteurs : KORTAM Nirmine, SEYE Fatou DARGERE Lucas et LAVAUX Bastien
projet : projet SMP 1er Année "Bataille Navale"
Date : 22 mai 2024
But : fichier Principale
Description : fichier contenant la boucle principale du jeu
*****************************************************************/

#include <cctype>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

#include "bateau.h"
#include "plateau.h"

string input1;

int main() {
  Bateau *porte_avion = new Bateau(5);
  Bateau croiseur(4);
  Bateau contre_torpilleur(3);
  Bateau torpilleur(3);
  Plateau plateau;
  plateau.afficherPlateau();
  plateau.placement(*porte_avion);
  plateau.afficherPlateau();
  
}