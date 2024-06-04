/**
 * @file bateau.h
 * @authors KORTAM Nirmine, SEYE Fatou, 
 *          DARGERE Lucas, LAVAUX Bastien
 * @date 22 mai 2024
 * @brief Déclaration de la classe bateau.
 * @details Mise en place d'une classe Bateau qui permettra de donner un nom au
 * bateau, une taille (5, 4, 3, 3, 2), leur état de vie et leur position dans le
 * plateau de jeu.
 */


#pragma once

#include "case.h"
#include <iostream>
#include <vector>
using namespace std;

class Bateau { // Création d'une classe bateau

protected:
  string nom;
  int longueur;
  int vie;
  vector<int> position{};

public:
  Bateau(int taille);
  // accesseurs en lecture
  int getLong();
  string getnom();
  bool EStCoule() const;
  int getPosition(int i);
  int getvie();

  // accesseurs en ecriture
  bool estCoule() const;
  void writePosition(int coordonne);
  void diminuerVie();
};
