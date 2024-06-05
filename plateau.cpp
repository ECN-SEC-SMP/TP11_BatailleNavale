/**
 *file : plateau.cpp
 *@authors : KORTAM Nirmine, SEYE Fatou, DARGERE Lucas et LAVAUX Bastien
 *@date : 22 mai 2024
 *@brief Création du plateau de jeu
 *@details Classe permettant de créer des plateaux sur lesquels les bateaux
 *peuvent être placés et où les tirs peuvent être effectués
 */

#include "plateau.h"
#include "bateau.h"
#include "case.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <thread>
#include <vector>

using namespace std;

/**
 *On définit les constantes nécessaires au fonctionnement du jeu pour
 *caractériser les différents états d'une case
 */
#define EAU 0
#define BATEAU 1
#define FAIL 2
#define TOUCHER_ATT 3
#define INTERDIT 4
#define TOUCHER_DEF 5

/**
 *Le constructeur de la classe plateau mettant les attributs a leur valeur par
 *défaut de début de partie.
 */
Plateau::Plateau() {
  /** initialisation du plateau avec de l'eau */
  for (int i = 0; i < 100; ++i) {
    tableau[0][i] = 0;
  }
  /** initialisation du tableau de case disponible pour tirer avec l'IA */
  for (int i = 0; i < 100; ++i) {
    Ia_tire[0][i] = 0;
  }
  /** creation des bateaux */
  porte_avion = new Bateau(5);
  flotte.push_back(porte_avion);
  croiseur = new Bateau(4);
  flotte.push_back(croiseur);
  contre_torpilleur1 = new Bateau(3);
  flotte.push_back(contre_torpilleur1);
  contre_torpilleur2 = new Bateau(3);
  flotte.push_back(contre_torpilleur2);
  torpilleur = new Bateau(2);
  flotte.push_back(torpilleur);
}

/**
 *La fonction init permet de placer les bateaux sur le plateau de jeu, elle
 *différencie si le joueur en face est une IA ou un ami et procède en
 *conséquence.
 */
void Plateau::init(int type) {
  if (type == 1) {
    placement(porte_avion);
    afficherPlateau();
    placement(croiseur);
    afficherPlateau();
    placement(contre_torpilleur1);
    afficherPlateau();
    placement(contre_torpilleur2);
    afficherPlateau();
    placement(torpilleur);
    for (int i = 0; i < 100; ++i) {
      if (tableau[0][i] == INTERDIT){
        tableau[0][i] = EAU;
      }
    }
  } else if (type == 2) {
    placementIA(0);
  }
}

/**
 *La fonction afficherPlateau permet d'afficher le plateau de jeu avec une mise
 *en forme selon les règles du jeu.
 */
void Plateau::afficherPlateau() {
  /** Afficher les en-têtes de colonnes */
  cout << "  |";
  for (char lettre = 'A'; lettre < 'A' + 10; ++lettre) {
    cout << ' ' << lettre << ' ' << '|';
  }
  cout << "\n  ";
  for (char lettre = 'A'; lettre < 'A' + 10; ++lettre) {
    cout << "----";
  }
  cout << endl;
  /** Afficher chaque ligne */
  for (int y = 0; y < 10; ++y) {
    /** Afficher l'en-tête de ligne*/
    cout << y + 1 << (y + 1 < 10 ? " |" : "|");
    /** Afficher les cases de la ligne*/
    for (int x = 0; x < 10; ++x) {
      int val = y * 10 + x;
      int statut = tableau[0][val];
      if (statut == 1) {

        cout << " B |";
      } else if (statut == 2) {
        cout << " . |";
      } else if (statut == 3) {
        cout << " "
             << "\033[31m" << '.' << "\033[0m"
             << " |";

      } else if (statut == 4) {
        cout << " "
             << "\033[31m" << 'x' << "\033[0m"
             << " |";

      } else if (statut == 5) {
        cout << " "
             << "\033[31m" << 'B' << "\033[0m"
             << " |";

      } else if (statut == 0) {
        cout << "   |";
        // cout << " "
        //   << "\033[31m" << tableau[0][val]  << "\033[0m"
        //   << " |";
      } else {
        cout << " E |";
      }
    }
    cout << "\n  ";
    /** Derniere ligne */
    for (int x = 0; x < 10; ++x) {
      cout << "----";
    }
    cout << endl;
  }
  cout << "\n " << endl;
}

/**
 *La fonction verifNotation vérifie que la valeur rentrée par l'utilisateur
 *correspond à une valeur attendue.
 *@param notation : la notation rentrée par l'utilisateur.
 *@return : la valeur rentrée par l'utilisateur sous la forme de coordonnée.
 */
string Plateau::verifNotation(string action) {
  string notation = "";
  cout << action << "\n";
  cin >> notation;

  char lettre = toupper(notation[0]); // mettre en majuscule
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

/**
 *La fonction transfoChar permet de transformer une lettre en un chiffre.
 *@param lettre : la valeur rentrée passé en paramètre.
 *@return : la valeur rentrée paramètre sous la forme de coordonnée dans le
 *tableau.
 */
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

/**
 *La fonction retourCoor récupère la coordonnée rentrée par l'utilisateur et la
 *transforme en une position du tableau.
 */

int Plateau::retourCoor(string message) {
  string retour = Plateau::verifNotation(message);
  int coord = Plateau::transfoChar(retour);
  return coord;
}


/** @brief étude de la possibilité de placer des bateaux
 * @param typebateau : bateau à placer
 * @param coordbateau : coordonnées du bateau à placer
 * @return : vrai si le bateau peut être placé, faux sinon
 *@details : vérifie si le bateau peut être placé en fonction de l'orientation
 *rentrée, de la taille du bateau et des coordonnées rentrées par
 *l'utilisateur par rapport au plateau
 */
bool Plateau::verifcase(int coordonées, int etat) {
  if (tableau[0][coordonées] == etat)
    return true;
  else {
    return false;
  }
}

bool Plateau::verifVerHaut(Bateau *typebateau, int coordbateau) {
  for (int y = 1; y <= typebateau->getLong() - 1; ++y) {
    if (coordbateau - (y * 10) < 0) {
      return false;
    } else if (tableau[0][coordbateau - (y * 10)] == 1) {
      return false;

    } else if (tableau[0][coordbateau - (y * 10)] == 4) {
      return false;
    }
  }
  return true;
}

bool Plateau::verifVerBas(Bateau *typebateau, int coordbateau) {
  for (int y = 1; y <= typebateau->getLong() - 1; ++y) {
    if (coordbateau + (y * 10) >= 100) {
      return false;
    } else if (tableau[0][coordbateau + (y * 10)] == 1) {
      return false;

    } else if (tableau[0][coordbateau + (y * 10)] == 4) {
      return false;
    }
  }
  return true;
}

bool Plateau::verifHorzDroite(Bateau *typebateau, int coordbateau) {
  for (int y = 1; y <= typebateau->getLong() - 1; ++y) {
    if ((coordbateau / 10) != (coordbateau + y) / 10) {
      return false;
    } else if (tableau[0][coordbateau + y] == 1) {
      return false;

    } else if (tableau[0][coordbateau + y] == 4) {
      return false;
    }
  }
  return true;
}

bool Plateau::verifHorzGauche(Bateau *typebateau, int coordbateau) {
  for (int y = 1; y <= typebateau->getLong() - 1; ++y) {
    if (coordbateau - y < 0) {
      return false;
    }
    if (round(coordbateau / 10) != round((coordbateau - y) / 10)) {
      return false;
    } else if (tableau[0][coordbateau - y] == 1) {
      return false;

    } else if (tableau[0][coordbateau - y] == 4) {
      return false;
    }
  }
  return true;
}
/**
 *@brief propose les choix possible a l'utilisateur pour   les directions dans
 *lesquels placer les bateaux
 *@param typebateau : bateau à placer, coordonner où l'on souhaite poser.
 */
void Plateau::choix(Bateau *typebateau, int coordbateau) {
  string verifchoix = "";
  string input = "";
  if (verifVerHaut(typebateau, coordbateau) == false &&
      verifVerBas(typebateau, coordbateau) == false &&
      verifHorzDroite(typebateau, coordbateau) == false &&
      verifHorzGauche(typebateau, coordbateau) == false) {
    cout << " vous ne pouvez pas positionner le bateau ici" << endl;
    placement(typebateau);
  } else {
    cout << "choissez l'orientation de votre bateau parmis les différents "
            "choix \n";
    if (verifVerHaut(typebateau, coordbateau)) {
      cout << "1: vers le haut \n";
      verifchoix = "1";
    };
    if (verifVerBas(typebateau, coordbateau)) {
      cout << "2: vers le bas \n";
      verifchoix = verifchoix + "2";
    };
    if (verifHorzDroite(typebateau, coordbateau)) {
      cout << "3: vers droite \n";
      verifchoix = verifchoix + "3";
    };
    if (verifHorzGauche(typebateau, coordbateau)) {
      cout << "4: vers gauche \n";
      verifchoix = verifchoix + "4";
    };
    string input;
    cin >> input;
    if (input.length() == 1) {
      for (int i = 0; i < verifchoix.length(); ++i) {
        if (input[0] == verifchoix[i]) {
          cout << "vous avez choisi l'orientation " << input << endl;

          if (input[0] == '1') {
            placementVerHaut(typebateau, coordbateau);
          } else if (input[0] == '2') {
            placementVerBas(typebateau, coordbateau);
          } else if (input[0] == '3') {
            placementHorzDroite(typebateau, coordbateau);

          } else if (input[0] == '4') {
            placementHorzGauche(typebateau, coordbateau);
          }
          return;
        }
      }
      cout << "vous n'avez pas renseigné un chiffre valable" << endl;
      choix(typebateau, coordbateau);
    } else {
      cout << "vous n'avez pas renseigné un chiffre valable" << endl;
      choix(typebateau, coordbateau);
    }
  }
}

/**@brief placement des bateaux en fonction de l'orientation rentrée par
 * l'utilisateur haut, bas , gauche ou droite
 */
void Plateau::placementVerHaut(Bateau *typebateau, int coordbateau) {
  for (int y = -1; y <= typebateau->getLong(); ++y) {
    if (y >= 0 && y < typebateau->getLong()) {
      tableau[0][coordbateau - (y * 10)] = 1;
      typebateau->writePosition(coordbateau - (y * 10));
      typebateau->getPosition(1);
    } else {
      tableau[0][coordbateau - (y * 10)] = 4;
    }
    if (round((coordbateau - (y * 10)) / 10) ==
            round((coordbateau - (y * 10) + 1) / 10) &&
        coordbateau - (y * 10) + 1 >= 0 && coordbateau - (y * 10) + 1 <= 100) {
      tableau[0][coordbateau - (y * 10) + 1] = 4;
    }
    if (round((coordbateau - (y * 10)) / 10) ==
            round((coordbateau - (y * 10) - 1) / 10) &&
        coordbateau - (y * 10) - 1 >= 0 && coordbateau - (y * 10) + 1 <= 100) {
      tableau[0][coordbateau - (y * 10) - 1] = 4;
    }
  }
}

void Plateau::placementVerBas(Bateau *typebateau, int coordbateau) {
  for (int y = -1; y <= typebateau->getLong(); ++y) {
    if (y >= 0 && y < typebateau->getLong()) {
      tableau[0][coordbateau + (y * 10)] = 1;
      typebateau->writePosition(coordbateau + (y * 10));
    } else {
      tableau[0][coordbateau + (y * 10)] = 4;
    }
    if (round((coordbateau + (y * 10)) / 10) ==
            round((coordbateau + (y * 10) + 1) / 10) &&
        coordbateau + (y * 10) + 1 > 0 && coordbateau + (y * 10) + 1 <= 100) {
      tableau[0][coordbateau + (y * 10) + 1] = 4;
    }
    if (round((coordbateau + (y * 10)) / 10) ==
            round((coordbateau + (y * 10) - 1) / 10) &&
        coordbateau + (y * 10) - 1 >= 0 && coordbateau + (y * 10) + 1 <= 100) {
      tableau[0][coordbateau + (y * 10) - 1] = 4;
    }
  }
}

void Plateau::placementHorzDroite(Bateau *typebateau, int coordbateau) {

  for (int y = -1; y <= typebateau->getLong(); ++y) {

    if (y >= 0 && y < typebateau->getLong()) {
      tableau[0][coordbateau + y] = 1;
      typebateau->writePosition(coordbateau + y);

    } else if (round(coordbateau / 10) == round((coordbateau + (y)) / 10)) {
      tableau[0][coordbateau + y] = 4;
    }

    if (coordbateau + y - 10 >= 0 &&
        round(coordbateau / 10) == round((coordbateau + (y - 10)) / 10 + 1)) {
      tableau[0][coordbateau + y - 10] = 4;
    }
    if (coordbateau + y + 10 <= 100 &&
        round(coordbateau / 10) + 1 == round((coordbateau + (y + 10)) / 10)) {
      tableau[0][coordbateau + y + 10] = 4;
    }
  }
}

void Plateau::placementHorzGauche(Bateau *typebateau, int coordbateau) {
  for (int y = -1; y <= typebateau->getLong(); ++y) {

    if (y >= 0 && y < typebateau->getLong()) {
      tableau[0][coordbateau - y] = 1;
      typebateau->writePosition(coordbateau - y);
    } else if (round(coordbateau / 10) == round((coordbateau - (y)) / 10)) {
      tableau[0][coordbateau - y] = 4;
    }

    if (coordbateau - y - 10 >= 0 &&
        round(coordbateau / 10) + 1 == round((coordbateau - (y - 10)) / 10)) {
      tableau[0][coordbateau - y - 10] = 4;
    }
    if (coordbateau - y + 10 <= 100 &&
        round(coordbateau / 10) == round((coordbateau - (y + 10)) / 10) + 1) {
      tableau[0][coordbateau - y + 10] = 4;
    }
    if (coordbateau < 10 &&
        round(coordbateau / 10) == round((coordbateau - (y + 10)) / 10)) {
      tableau[0][coordbateau - y + 10] = 4;
    }
  }
}

/**
 * place les bateaux sur le plateau
 * @param typebateau : bateau à placer
 * @detais : vérifie si le bateau peut être placé, si oui, place le bateau,
 * sinon, redemande à l'utilisateur de rentrer des coordonnées
 */
void Plateau::placement(Bateau *typebateau) {
  int coordbateau =
      retourCoor("Entrez la position de votre " + typebateau->getnom() + " : ");

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
    choix(typebateau, coordbateau);
    // placementcase(typebateau, coordbateau, choixcase);
  }
}

/**
 * @brief modifie le statut de la case en fonction de l'état rentré en parametre
 * @param coord : coordonnées de la case à modifier, etat : état future de la
 * case à modifier;
 */
void Plateau::modifCase(int position, int etat) { tableau[0][position] = etat; }

/**
 * Enlève un point de vie au bateau
 */
void Plateau::modifFlotteVie() { flottevie--; }

/**
 *vérifie si la flotte du joueur est vivante
 * @return : true si la flotte du joueur est vivante, false sinon
 */
bool Plateau::flottevivante() {
  if (flottevie == 0) {
    return false;
  }
  return true;
}

/**
 * @brief : vérifie si un bateau est touché en comparant la case viser et les
 * positions des bateaux param : coord : coordonnées de la case visée
 */
bool Plateau::bateautouche(int position) {

  for (int i = 0; i < porte_avion->getLong(); i++) {

    if (porte_avion->getPosition(i) == position) {
      if (0 == porte_avion->getvie() - 1) {
        return true;
      }
      porte_avion->diminuerVie();
    }
  }
  for (int i = 0; i < croiseur->getLong(); i++) {
    if (croiseur->getPosition(i) == position) {
      if (0 == croiseur->getvie() - 1) {
        return true;
      }
      croiseur->diminuerVie();
    }
  }
  for (int i = 0; i < contre_torpilleur1->getLong(); i++) {
    if (contre_torpilleur1->getPosition(i) == position) {
      if (0 == contre_torpilleur1->getvie() - 1) {
        return true;
      }
      contre_torpilleur1->diminuerVie();
    }
  }
  for (int i = 0; i < contre_torpilleur2->getLong(); i++) {
    if (contre_torpilleur2->getPosition(i) == position) {
      if (0 == contre_torpilleur2->getvie() - 1) {
        return true;
      }
      contre_torpilleur2->diminuerVie();
    }
  }
  for (int i = 0; i < torpilleur->getLong(); i++) {
    if (torpilleur->getPosition(i) == position) {
      if (0 == torpilleur->getvie() - 1) {
        return true;
      }
      torpilleur->diminuerVie();
    }
  }
  return false;
}
/**
 * Gestion du placement des bateaux
 * @param i  : choix du bateau dans le vecteur
 */

void Plateau::placementIA(int i) {
  std::random_device rd;
  std::mt19937 gen(rd());

  // Définit une distribution uniforme dans la plage [min, max]
  uniform_int_distribution<> dis1(0, 3);
  uniform_int_distribution<> dis2(0, 100);

  // Génère un nombre aléatoire

  while (i < flotte.size()) {

    int coordbateau = dis2(gen);

    while (verifcase(coordbateau, 1) || verifcase(coordbateau, 4)) {

      coordbateau = dis2(gen);

      if (verifHorzDroite(flotte[i], coordbateau) == false &&
          verifHorzGauche(flotte[i], coordbateau) == false &&
          verifVerBas(flotte[i], coordbateau) == false &&
          verifVerHaut(flotte[i], coordbateau) == false) {
        coordbateau = dis2(gen);
      }
    }

    int temptbl[4] = {0, 0, 0, 0};
    if (verifVerHaut(flotte[i], coordbateau)) {
      temptbl[0] = 1;
    }
    if (verifVerBas(flotte[i], coordbateau)) {
      temptbl[1] = 1;
    }
    if (verifHorzDroite(flotte[i], coordbateau)) {
      temptbl[2] = 1;
    }
    if (verifHorzGauche(flotte[i], coordbateau)) {
      temptbl[3] = 1;
    }
    int j = dis1(gen);
    while (temptbl[j] == 0) {
      j = dis1(gen);
    }
    PlacementCaseIA(coordbateau, j, i);
    i++;
  }
}

/**
 * Placement des bateaux sur le plateau
 * @param coordbateau  : coordonnée de la case où le bateau doit être placé
 * @param j  : choix de l'acces via un ramdon
 * @param flottetour  : bateau qui doit etre placé
 */

void Plateau::PlacementCaseIA(int coordbateau, int j, int flottetour) {
  if (j == 0) {
    placementVerHaut(flotte[flottetour], coordbateau);
    // this_thread::sleep_for(chrono::milliseconds(100));
  } else if (j == 1) {
    placementVerBas(flotte[flottetour], coordbateau);
    // this_thread::sleep_for(chrono::milliseconds(100));
  } else if (j == 2) {
    placementHorzDroite(flotte[flottetour], coordbateau);
    // this_thread::sleep_for(chrono::milliseconds(100));
  } else if (j == 3) {
    placementHorzGauche(flotte[flottetour], coordbateau);
    // this_thread::sleep_for(chrono::milliseconds(100));
  } else {
    // placementIA(flottetour);
  }
  // this_thread::sleep_for(chrono::milliseconds(100));
}

/**
 * Tire de l'IA grace a une fonction random
 * @param Plateau : plateau du joueur defensive
 */

bool Plateau::tireIA(Plateau *def) {
  std::random_device rd;
  std::mt19937 gen(rd());
  bool etat = false;

  vector<int> caselibre;
  int tour = 0;

  for (int i = 0; i < 101; ++i) {
    if (0 == Ia_tire[0][i]) {
      caselibre.push_back(i);
      tour++;
    }
  }
  if (toucher == 1) {
    int i = tracking(def);
    if (i == 0) {
    }
    if (i == 1)
      return true;
    if (i == 2) {
      return false;
    }
  }
  uniform_int_distribution<> dis1(0, tour);
  int coordonne = dis1(gen);

  for (int i = 0; i < caselibre.size(); ++i) {
    if (coordonne == caselibre[i]) {

      if (def->verifcase(coordonne, 1)) {

        etat = def->bateautouche(coordonne);
        def->modifCase(coordonne, 5);
        modifCase(coordonne, 3);
        Ia_tire[0][coordonne] = 1;
        if (etat) {
          cout << "Touché Coulé !" << endl;
          def->modifFlotteVie();
        } else {
          cout << "Touché !" << endl;
        }
        if (def->flottevivante() == false) {
          return false;
        }
      } else {
        modifCase(coordonne, 2);
        cout << "Manquer" << endl;
      }
    }
  }
  return true;
}

int Plateau::tracking(Plateau *def) {
  random_device rd;
  mt19937 gen(rd());
  vector<int> valid = {};
  if (derniertire / 10 == (derniertire + 1) / 10 || derniertire + 1 > 100) {
    valid.push_back(derniertire + 1);
    
  }
  if (derniertire / 10 == (derniertire - 1) / 10 || derniertire - 1 > 0) {
    valid.push_back(derniertire - 1);
   
  }
  if (derniertire - 10 > 0) {
    valid.push_back(derniertire - 10);
    
  }
  if (derniertire + 10 < 100) {
    valid.push_back(derniertire + 10);
  }
  if (valid.size() == 0) {
    return 0;
  } else {
    while (true) {
      uniform_int_distribution<> dis1(0, valid.size() - 1);
      cout << valid.size() << endl;
      int choixc = dis1(gen);
      cout << choixc << endl;
      this_thread::sleep_for(chrono::milliseconds(100));
      if (def->verifcase(valid[choixc], 1)) {
        bool etat = def->bateautouche(choixc);
        def->modifCase(valid[choixc], 5);
        modifCase(valid[choixc], 3);
        Ia_tire[0][valid[choixc]] = 1;
        if (etat) {
          cout << "Touché Coulé ! \n" << endl;
          def->modifFlotteVie();
          toucher = 0;
          derniertire = 0;
          cout << "traking désactivé \n" << endl;
        } else {
          cout << "Touché ! \n" << endl;
          toucher = 1;
          derniertire = valid[choixc];
          cout << "traking activé \n " << endl;
        }
        if (def->flottevivante() == false) {
          return 2;
        } else {
          return 1;
        }
        break;
      } else if (verifcase(valid[choixc], 0)) {
        modifCase(valid[choixc], 2);
        cout << "Manquer \n" << endl;
        toucher = 0;
        cout << "traking désactivé \n" << endl;
        return 1;
      }
    }
  }
}

int Plateau::trackingComplexe(Plateau *def){
  random_device rd;
    mt19937 gen(rd());
    vector<int> valid = {};
    if (derniertire / 10 == (derniertire + 1) / 10 || derniertire + 1 > 100) {
      valid.push_back(derniertire + 1);
    }
    if (derniertire / 10 == (derniertire - 1) / 10 || derniertire - 1 > 0) {
      cout << (derniertire / 10) <<endl;
      cout << (derniertire -1) / 10 <<endl;
      valid.push_back(derniertire - 1);
    }
    if (derniertire - 10 > 0) {
      valid.push_back(derniertire - 10);
    }
    if (derniertire + 10 < 100) {
      valid.push_back(derniertire + 10);
    }
    if (valid.size() == 0) {
      return 0;
    } else {
      while (true) {
        uniform_int_distribution<> dis1(0, valid.size() - 1);
        int choixc = dis1(gen);
        this_thread::sleep_for(chrono::milliseconds(100));
        if (def->verifcase(valid[choixc], 1)) {
          bool etat = def->bateautouche(choixc);
          def->modifCase(valid[choixc], 5);
          modifCase(valid[choixc], 3);
          Ia_tire[0][valid[choixc]] = 1;
          if (etat) {
            cout << "Touché Coulé ! \n" << endl;
            def->modifFlotteVie();
            toucher = 1;
            derniertire = 0;
            cout << "traking désactivé \n" << endl;
          } else {
            cout << "Touché ! \n" << endl;
            toucher = 1;
            derniertire = valid[choixc];
            cout << "traking activé \n " << endl;
          }
          if (def->flottevivante() == false) {
            return 2;
          } else {
            return 1;
          }
          break;
        } else if (verifcase(valid[choixc], 0)) {
          modifCase(valid[choixc], 2);
          cout << "Manquer \n" << endl;
          if(toucher==1){
            cout << "traking toujours actif \n" << endl;
            return 1;
          }else{
          toucher =0;
          cout << "traking fini \n" << endl;
          return 1;}
        }
      }
    }
  
}
