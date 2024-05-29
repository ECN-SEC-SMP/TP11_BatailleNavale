#include "case.h"
#include "bateau.h"
#include <iostream>
#pragma once
using namespace std;

class Plateau {

  private:
    int TAILLE = 10;
    static const int LMAX = 10;
    static const int HMAX = 10;
    int tableau[1][99] = {};
    string joueur;
  
  public:
    //constructeurs
    Plateau();
    Plateau(string type);

    //accesseurs en lecture

    //accesseurs en ecriture
    void init();

    //méthodes
    void initialisation();
    void afficherPlateau();
    void placer(int x, int y);
    string verifNotation(string action);
    int transfoChar(string &notation);
    int retourCoor(string message);
    int tirer(int X, int Y);
    void placement(Bateau typebateau);
    bool verifcase(int coordonées , int etat);
    bool verifHorzHaut(Bateau typebateau, int coordbateau);
    void choix(Bateau typebateau ,int coordbateau);
    
};