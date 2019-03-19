/**
 \file main.cpp
 \author Arthur Bécaud, Loïc Geinoz et Gildas Houlmann
 \date 18.03.2019
 Labo 2 : Mise à disposition d'une fonction récursive pour chercher toutes les
          solutions possibles d'un puzzle 'impossible'.
          Les solutions sont rendues sous la forme d'un code indiquant la
          position et rotation de toutes les pièces dans la grille du puzzle.
          Exemple '1b 5d 4a 7a 6a 2a 8a 3a 9d', les numéros '123456789'
          représentent les pièces et les lettres 'abcd' donnent les rotations.

          Toutes les solutions sont vérifiables sur le site suivant :
          https://ocuisenaire.github.io/ASD1-Labs/puzzle/
*/
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "pieces.h"

using namespace std;

using Sens = vector<unsigned>;

/**
 * @brief Tourne une pièce dans le sens anti-horaire
 * @param indiceCase Position de la pièce
 * @param grille Grille du puzzle
 */
void tournerPiece(size_t indiceCase, Pieces& grille);

/**
 * @brief Vérifie si deux motifs sont compatibles
 * @param motif1
 * @param motif2
 * @return Vrai si les deux motifs sont compatibles
 */
bool verifierMotifs(AttachementType motif1, AttachementType motif2);

/**
 * @brief Vérifie qu'une pièce sur la grille soit compatible avec la pièce du haut et de gauche
 * @param indiceCase Position de la pièce
 * @param grille Grille du puzzle
 * @return Vrai si la pièce est compatible
 */
bool verifierJointures(size_t indiceCase, const Pieces& grille);

/**
 * @brief Vérifie qu'une certaine pièce ne se trouve pas déjà dans la grille
 * @param numPiece Le numéro de la pièce
 * @param listePiecesPlacees Liste indiquant quelles pièces sont déjà placées
 * @return Vrai si la pièce n'est pas trouvée
 */
bool piecePasPresenteDansLaGrille(const size_t& numPiece, const vector<unsigned>& listePiecesPlacees);

/**
 * @brief Converti une pièce et sa rotation sous forme '1a', '3b', etc
 * @param numPiece Numéro de la pièce
 * @param rotation Rotation de la pièce
 * @return Code de la pièce, exemple '4c'
 */
string codePieceEtRotation(const size_t& numPiece, const size_t& rotation);

/**
 * @brief Fonction résursive de recherche des solutions du puzzle
 * @param piecesAEssayer Liste des pièces plaçables dans la grille
 * @param solutions Liste des solutions
 * @param solutionCourante Passage du code de la solution courante
 */
void permutationRecursive(const Pieces& piecesAEssayer, vector<string>& solutions, string solutionCourante = "");

int main() {

   vector<string> solutions;

   permutationRecursive(PIECES, solutions);

   // Affichage des solutions
   cout << "-------- " << solutions.size() << " Solutions -------- " << endl;
   for (const string& solution : solutions) {
      cout << solution << endl;
   }

   return EXIT_SUCCESS;
}

void tournerPiece(size_t indiceCase, Pieces& grille) {
   // Recule les éléments du vecteur : [1,2,3,4] -> [2,3,4,1]
   rotate(grille.at(indiceCase).begin(), grille.at(indiceCase).begin() + 3, grille.at(indiceCase).end());
}

bool verifierMotifs(AttachementType motif1, AttachementType motif2) {
   // Si motif Arrosoire inversé ou None
   if (motif1 > 7 or motif2 > 7) {
      return false;
   }

   // Trouve le motif devant correspondre à motif1
   unsigned motifCorrespondant = (unsigned) (motif1 + (motif1 % 2 ? -1 : 1));

   return motifCorrespondant == (unsigned) motif2;
}

bool verifierJointures(size_t indiceCase, const Pieces& grille) {

   // Jointure valide automaitquement si première case de la grille
   if (!indiceCase)
      return true;

   // Vérification verticale si ligne 2 ou 3
   if (indiceCase > 2) {

      // Motif du bas de la case supérieur de l'indice de case choisit
      AttachementType motifCaseSuperieur = grille.at(indiceCase - 3).at(2);

      // Motif du haut de la casse courante de l'indice de case choisit
      AttachementType motifCaseInferieur = grille.at(indiceCase).at(0);

      // Vérification des deux motifs
      if (!verifierMotifs(motifCaseSuperieur, motifCaseInferieur))
         return false;
   }

   // Vérification horizontale si colonne 2 ou 3
   if (indiceCase % 3) {

      // Motif de droite de la case à gauche de l'indice de case choisit
      AttachementType motifCaseGauche = grille.at(indiceCase - 1).at(1);

      // Motif de gauche de la casse courante de l'indice de case choisit
      AttachementType motifCaseDroite = grille.at(indiceCase).at(3);

      // Vérification des deux motifs
      if (!verifierMotifs(motifCaseGauche, motifCaseDroite))
         return false;
   }

   // Pièce validée si elle a passé tous les tests
   return true;
}

bool piecePasPresenteDansLaGrille(const size_t& numPiece, const vector<unsigned>& listePiecesPlacees) {
   return find(listePiecesPlacees.begin(), listePiecesPlacees.end(), numPiece) == listePiecesPlacees.end();
}

string codePieceEtRotation(const size_t& numPiece, const size_t& rotation) {
   // Boucle rotation : quand j == 1 -> sens 'd'
   //                         j == 3 -> sens 'b'
   return to_string(numPiece + 1) + (char) ('a' + (unsigned) (rotation % 2 ? 4 - rotation : rotation));
}

void permutationRecursive(const Pieces& piecesAEssayer, vector<string>& solutions, string solutionCourante) {

   static Pieces grille;
   static vector<unsigned> piecesPlaces;
   static size_t indiceCase = 0;

   // Essaye de poser toutes les pièces restantes à l'indice de case courant
   for (size_t i = 0; i < piecesAEssayer.size(); ++i) {

      // Si première pièce ou si la pièceAEssayer n'est pas déjà sur la grille
      if (grille.empty() or piecePasPresenteDansLaGrille(i, piecesPlaces)) {

         // Pose la pièce et l'ajoute au suivi des pièces placées
         grille.push_back(piecesAEssayer.at(i));
         piecesPlaces.push_back(i);

         // Essaye chaque rotation d'une pièce
         for (size_t j = 0; j < 4; ++j) {

            // Permet de tourner 3 fois la pièce
            if (j)
               tournerPiece(indiceCase, grille);

            // Si la pièce placée est valide
            if (verifierJointures(indiceCase, grille)) {
               // Ajoute la nouvelle pièce à la solution courante
               solutionCourante += codePieceEtRotation(i,j) + " ";

               // Si la grille est complète
               if (grille.size() == 9) {
                  // Ajoute la solution courante à la liste des solutions
                  solutions.push_back(solutionCourante);
               } else {
                  // Appel à la récursivité en incrémentant l'indice de la case courante
                  ++indiceCase;
                  permutationRecursive(piecesAEssayer, solutions, solutionCourante);
                  // Lors de la fin de la récursivité, l'indice de case est décrémenté
                  --indiceCase;
               }
               // Enlève le code de la pièce de la solution courante
               solutionCourante = solutionCourante.substr(0, solutionCourante.size() - 3);
            }
         }
         // Supprime la pièce de la grille et enlève la pièce du suivi des pièces placées
         grille.pop_back();
         piecesPlaces.pop_back();
      }
   }
}
