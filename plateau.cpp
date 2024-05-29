/*****************************************************************
Auteurs : KORTAM Nirmine, SEYE Fatou DARGERE Lucas et LAVAUX Bastien
projet : projet SMP 1er Année "Bataille Navale"
Date : 22 mai 2024
But : fichier source de la classe plateau
Description : classe permettant de créer des palteau sur lesquel les bateaux
peuvent être placés et où les tirs peuvent être effectués
*****************************************************************/




#include "plateau.h"
#include "bateau.h"
#include "case.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

#define EAU 0
#define bateau 1
#define coule 2
#define fail 3
#define interdit 4

Plateau::Plateau() : joueur("humain") { init(); }

Plateau::Plateau(string type) : joueur(type) { init(); }

void Plateau::init() {
  for (int i = 0; i < 100; ++i) {
    tableau[0][i] = 0;
  }
  tableau[0][1] = 1;
}

void Plateau::afficherPlateau() {
  // Afficher les en-têtes de colonnes
  cout << "  |";
  for (char lettre = 'A'; lettre < 'A' + TAILLE; ++lettre) {
    cout << ' ' << lettre << ' ' << '|';
  }
  cout << "\n  ";
  for (char lettre = 'A'; lettre < 'A' + TAILLE; ++lettre) {
    cout << "----";
  }
  cout << endl;
  // Afficher chaque ligne
  for (int y = 0; y < TAILLE; ++y) {
    // Afficher l'en-tête de ligne
    cout << y + 1 << (y + 1 < 10 ? " |" : "|");
    for (int x = 0; x < TAILLE; ++x) {
      int val = y * 10 + x;
      int statut = tableau[0][val];
      if (statut == 1) {

        cout << " B |";
      } else if (statut == 2) {
        cout << " . |";
      } else if (statut == 3) {
        std::cout << " "
                  << "\033[31m" << '.' << "\033[0m"
                  << " |";

      } else {
        cout << "   |";
      }
    }
    cout << "\n  ";
    for (int x = 0; x < TAILLE; ++x) {
      cout << "----";
    }
    cout << endl;
  }
}

string Plateau::verifNotation(string action) {
  string notation;
  cout << action << "\n";
  cin >> notation;

  char lettre = toupper(notation[0]);// mettre en majuscule 
  string chiffre = notation.substr(1);

  while (notation.length() < 2 || (lettre < 'A' || lettre > 'J') ||
         (chiffre.length() > 2 || !std::isdigit(chiffre[0]) ||
          stoi(chiffre) >= 11)) {

    if (notation.length() < 2) {
      cout << "Vous avez renseigné qu'une seule lettre ou qu'un chiffre, "
              "veuillez renseigner une lettre et un chiffre"
           << endl;
    } else if (lettre < 'A' || lettre > 'J') {

      cout << "La lettre doit être comprise entre A et J" << endl;

    } else if (chiffre.length() > 2 || !std::isdigit(chiffre[0]) ||
               stoi(chiffre) >= 11) {

      cout << "Le chiffre doit être compris entre 1 et 10" << endl;
    }
    cout << action;
    cin >> notation;

    lettre = toupper(notation[0]);
    chiffre = notation.substr(1);
  }
  return notation;
};

int Plateau::transfoChar(string &notation) {
  int x = toupper(notation[0]);
  if (x == 'A') {
    x = 0;
  } else if (x == 'B') {
    x = 1;
  } else if (x == 'C') {
    x = 2;
  } else if (x == 'D') {
    x = 3;
  } else if (x == 'E') {
    x = 4;
  } else if (x == 'F') {
    x = 5;
  } else if (x == 'G') {
    x = 6;
  } else if (x == 'H') {
    x = 7;
  } else if (x == 'I') {
    x = 8;
  } else if (x == 'J') {
    x = 9;
  }
  x = x + 10 * (stoi(notation.substr(1))) - 10;

  return x;
}

int Plateau::retourCoor(string message) {
  string retour = Plateau::verifNotation(message);
  int coord = Plateau::transfoChar(retour);
  return coord;
}

bool Plateau::verifcase(int coordonées, int etat) {
  if (tableau[0][coordonées] == etat)
    return true;
  else {
    return false;
  }
}

bool Plateau::verifHorzHaut(Bateau typebateau, int coordbateau) {
  for (int y = 1; y <= typebateau.getLong(); ++y) {
    if (coordbateau - (y * 10) < 0) {
      return false;
    }else
    if (tableau[0][coordbateau - (y * 10)]==1) {
      return false;
      
    }else
    if (tableau[0][coordbateau - (y * 10)]==4) {
      return false;
    }
  }
  return true;
}

void Plateau::choix(Bateau typebateau, int coordbateau) {
  bool choix = verifHorzHaut(typebateau, coordbateau);
  cout << choix << endl;
}

void Plateau::placement(Bateau typebateau) {
  int coordbateau =
      retourCoor("Entrez la position de votre " + typebateau.getnom() + " : ");

  if (verifcase(coordbateau, 1) == true) {
    cout << "cette case est interdit "
         << "\n";
    placement(typebateau);
  } else if (verifcase(coordbateau, 4) == true) {
    cout << "cette case est interdit 2 "
         << "\n";
    ;
    placement(typebateau);
  } else {
    tableau[0][coordbateau] = 1;
  }
  choix(typebateau,  coordbateau);
  
}
