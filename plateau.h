/**
*file : plateau.h
*@authors : KORTAM Nirmine, SEYE Fatou, DARGERE Lucas et LAVAUX Bastien
*@date : 22 mai 2024
*@brief création du plateau de jeu
* @details Le plateau contient un tableau de 100 cases qui par leurs valeurs
définissent ce que contient chaque case,

*/

#include "bateau.h"
#include "case.h"
#include <iostream>
#include <vector>
#pragma once
using namespace std;

class Plateau {

private:
  // tableau de 100 cases qui regroupe les coordonnées du plateau
  int tableau[1][100] = {};

  int Ia_tire[1][100] = {};
  int flottevie = 5;          /** nombre de bateaux restants*/
  int toucher = 0;            /** si le dernier tir touche*/
  int derniertire = 10;        /** dernier tir*/
  Bateau *porte_avion;        /**pointeur du bateau porte avion*/
  Bateau *croiseur;           /**pointeur du bateau croisseur*/
  Bateau *contre_torpilleur1; /**pointeur du bateau contre torpilleur 1*/
  Bateau *contre_torpilleur2; /**pointeur du bateau contre torpilleur 2*/
  Bateau *torpilleur;         /**pointeur du bateau torpilleur  */
  vector<Bateau *> flotte =
      {}; /** vecteur flotte qui regroupe les bateaux du joueur */

public:
  /** mise en place des constructeurs de plateau */
  Plateau();
  Plateau(string type);

  // accesseurs en ecriture
  void init(int type); /** initialisation du bateau */

  // méthodes
  void initialisation();     /** initialisation du plateau */
  void afficherPlateau();    /** affichage du plateau */
  void placer(int x, int y); /** placer le bateau sur le plateau */
  string verifNotation(
      string action); /** verifie les notations rentrées par l'utilisateur */
  int transfoChar(string &notation); /** transforme les coordonnées rentrées par
                                        l'utilisateur en entier */
  int retourCoor(string message);    /** retourne les coordonnées rentrées par
                                        l'utilisateur */
  int tirer(int X, int Y); /** tire sur le plateau avec les coordonnées x et y*/

  void placement(Bateau *typebateau); /** place les bateaux sur le plateau */

  /**@brief placement des bateaux en fonction de l'orientation rentrée par
   * l'utilisateur haut, bas , gauche ou droite*/
  void placementVerHaut(Bateau *typebateau, int coordbateau);
  void placementVerBas(Bateau *typebateau, int coordbateau);
  void placementHorzDroite(Bateau *typebateau, int coordbateau);
  void placementHorzGauche(Bateau *typebateau, int coordbateau);

  /** @brief étude de la possibilité de placer des bateaux
   * @param typebateau : bateau à placer
   * @param coordbateau : coordonnées du bateau à placer
   * @return : vrai si le bateau peut être placé, faux sinon
   *@details : vérifie si le bateau peut être placé en fonction de l'orientation
   *rentrée, de la taille du bateau et des coordonnées rentrées par
   *l'utilisateur par rapport au plateau
   */
  bool verifcase(int coordonées, int etat);
  bool verifVerHaut(Bateau *typebateau, int coordbateau);
  bool verifVerBas(Bateau *typebateau, int coordbateau);
  bool verifHorzDroite(Bateau *typebateau, int coordbateau);
  bool verifHorzGauche(Bateau *typebateau, int coordbateau);

  /** 
  *@brief propose les choix possible a l'utilisateur pour   les directions dans lesquels placer les bateaux
  *@param typebateau : bateau à placer, coordonner où l'on souhaite poser.
  */
  void choix(Bateau *typebateau, int coordbateau);


  bool bateautouche(int position); /** vérifie si un bateau est touché et
                                      renvoie un booléen */
  void modifCase(int position,
                 int etat); /** modifie l'état d'une case du plateau en  */
  bool flottevivante();     /** vérifie si la flotte du joueur est vivante  et
                               renvoie un booléen*/
  void
  modifFlotteVie(); /** modifie le nombre de bateaux restants pour le joueur */
  void PlacementCaseIA(int coordbateau, int j,
                       int flottetour); /** placement d'un bateau de l'IA */

  void placementIA(int i);   /** placeement des 5 bateaux*/
  bool tireIA(Plateau *def); /** tire sur le plateau de l'IA */
  int tracking(Plateau *def);/**  */
  int trackingComplexe(Plateau *def);
};
