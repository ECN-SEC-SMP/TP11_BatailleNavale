
/**
 * @file bateau.h
 * @authors KORTAM Nirmine, SEYE Fatou,
 *          DARGERE Lucas, LAVAUX Bastien
 * @date 22 mai 2024
 * @brief Programme Principal.
 * @details Affectation de plateau Attaque et Defense pour chaque joueur,
 * Création d'une fonction tirer qui renvoie un booléen indiquant si la flotte
 * est complètement coulée ou pas, * autrement dit, si le jeu est fini ou pas.
 * Création de l'interface joueur- machine, * et de la fonction qui permet de
 * jouer une partie.
 */

#include <cctype>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>
using namespace std;

#include "bateau.h"
#include "plateau.h"

string input1;

Plateau *plateauDefj1 =
    new Plateau(); /** Création du plateau de défense du joueur 1*/
Plateau *plateauAttaj1 =
    new Plateau(); /** Création du plateau d'attaque du joueur 1*/
Plateau *plateauDefj2 =
    new Plateau(); /** Création du plateau de défense du joueur 2*/
Plateau *plateauAttaj2 =
    new Plateau(); /** Création du plateau d'attaque du joueur 2*/
Plateau *plateauDefIA =
    new Plateau(); /** Création du plateau de défense de l'IA*/
Plateau *plateauAttaIA =
    new Plateau(); /** Création du plateau d'attaque de l'IA*/

bool partieencour = true;

bool tirer(Plateau *att,
           Plateau *def) { /** Fonction qui permet de jouer une partie */
  int coordbateau;

  coordbateau = att->retourCoor(
      "Entrez la case où vous voulez tirer : "); /** Demande à l'utilisateur de
                                                    choisir une case où tirer */

  if (att->verifcase(coordbateau,
                     3)) { /** Vérifie si la case choisie est déjà touchée */
    cout
        << " vous avez déjà tiré ici"
        << endl; /** Si la case est déjà touchée, affiche un message d'erreur */
    tirer(att, def); /** Rappelle la fonction pour demander à l'utilisateur de
                        choisir une case où tirer */
  } else if (att->verifcase(
                 coordbateau,
                 2)) { /** Vérifie si la case choisie est déjà manquée */
    cout << " vous avez déjà tiré ici" << endl;
    tirer(att, def);
  } else if (def->verifcase(coordbateau, 1)) { /** Vérifie si la case choisie
                                                  est occupée par un bateau */
    bool etat = def->bateautouche(
        coordbateau); /** Appelle la fonction bateautouche pour vérifier si le
                         bateau est touché */
    att->modifCase(coordbateau, 3);
    def->modifCase(coordbateau, 5);
    if (etat) { /** Si le bateau est coulé, affiche un message de victoire */
      
      def->modifFlotteVie(); /** Modifie la vie de la flotte adverse */
    } else { /** Si le bateau n'est pas coulé, affiche un message de raté */
      
    }
  } else if (att->verifcase(coordbateau,
                            0)) { /** Vérifie si la case choisie est vide */
    att->modifCase(coordbateau,
                   2); /** Si la case est vide, affiche un message de manqué */
    cout << "Manqué" << endl;
  };
  if (def->flottevivante() ==
      false) {    /** Vérifie si la flotte adverse est coulée */
    return false; /** Si la flotte adverse est coulée, retourne false pour
                     indiquer la fin de la partie */
  }
  return true; /** Si la flotte adverse n'est pas coulée, retourne true pour
                  continuer la partie */
}

/** programme principal*/

int main() { /** Création des joueurs et leur plateau de défense et d'attaque */
  // plateauAttaj1->init(0);
  // plateauAttaj1->tracking(plateauAttaj1);
  /** choix du nombre de joueurs*/
  cout << "Bienvenue dans le jeu de la bataille navale\n " << endl;
  string input1 = "3";
  while (
      input1 != "1" &&
      input1 !=
          "2") { /** Demande à l'utilisateur de choisir le nombre de joueurs */

    cout << "choisir le nombre de joueur : 1 ou 2" << endl;
    cin >> input1;
    if (input1 == "1" || input1 == "2") {
      break;
    }
    cout << "vous avez pas renseigné 1 ou 2" << endl;
  }

  /** déroulé de jeu pour un seul joueur avec une IA */
  if (input1 == "1") {
    cout << "Vous avez choisi le mode solo" << endl;
    /** initialisation du plateau de jeu du joueur et de l'IA*/
    plateauDefj1->init(1);
    cout << "tableau joueur def" << endl;
    plateauDefj1->afficherPlateau();
    plateauDefIA->init(2);
    plateauAttaIA->init(0);
    plateauAttaj1->init(0);

    /** le jeu commence entre l'IA et le joueur à tour de role */
    while (true) {
      std::this_thread::sleep_for(std::chrono::milliseconds(
          1500)); /** attendre 1,5 seconde avant de tirer */
      cout << "tableau joueur attaque" << endl;
      plateauAttaj1
          ->afficherPlateau(); /** affiche le tableau de jeu du joueur */
      cout << "A toi de tirer \n " << endl;
      partieencour = tirer(
          plateauAttaj1, plateauDefIA); /** appelle la fonction tirer pour jouer
                                           une partie entre le joueur et l'IA */
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      cout << "tableau joueur attaque" << endl;
      plateauAttaj1->afficherPlateau();
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      if (partieencour ==
          false) { /** si la partie est finie, affiche un message de victoire */
        cout << "tu as gagne \n " << endl;
        break;
      }
      cout << "l IA tire \n  " << endl;
      partieencour = plateauAttaIA->tireIA(
          plateauDefj1); /** appelle la fonction tirer pour jouer une partie
                            entre l'IA et le            joueur */
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      cout << "tableau IA attaque" << endl;
      plateauAttaIA->afficherPlateau();
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      cout << "tableau joueur def" << endl;
      plateauDefj1->afficherPlateau();
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      if (partieencour == false) {
        cout << "IA a gagner \n " << endl;
        break;
      }
    }
  }

  /**déroulé de jeu entre 2 joueurs  */
  else {
    cout << "Le joueur 1 doit placer ses bateaux\n " << endl;
    plateauDefj1->init(1); /** initialisation du plateau de jeu du joueur 1*/
    cout << "Le joueur 2 doit placer ses bateaux\n " << endl;
    plateauDefj2->init(1); /** initialisation du plateau de jeu du joueur 2*/

    while (true) {

      cout << "joueur 1 doit tirer \n " << endl;
      cout << "tableau joueur1 attaque" << endl;
      plateauAttaj1->afficherPlateau();
      partieencour = tirer(plateauAttaj1, plateauDefj2);
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      cout << "tableau joueur2 def" << endl;
      plateauDefj2->afficherPlateau();
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));

      if (partieencour == false) {
        cout << "joueur 1 a gagner \n " << endl;
        break;
      }
      cout << "joueur 2 doit tirer \n  " << endl;
      cout << "tableau joueur2 attaque" << endl;
      plateauAttaj2->afficherPlateau();
      partieencour = tirer(plateauAttaj2, plateauDefj1);
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      cout << "tableau joueur1 attaque" << endl;
      plateauDefj1->afficherPlateau();
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));

      if (partieencour ==
          false) { /** si la partie est finie, affiche un message de victoire */
        cout << "joueur 2 a gagner \n " << endl;
        break;
      }
    }
  }
}
