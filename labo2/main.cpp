/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo_2_Puzzle_Impossible
 Fichier     : main.cpp
 Auteur(s)   : Arthur Bécaud, Loic Geinoz, Gildas Houlmann
 Date        : 06.03.2019

 But         :

 Remarque(s) :

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
*/
#include <cstdlib>
#include "pieces.h"
#include <array>
#include <vector>
#include <algorithm> // peut etre enlever
#include <iostream> // pour tests

using namespace std;


bool motifsComplementaires(AttachementType motif1, AttachementType motif2) {
	if (motif1 < motif2) {
		AttachementType temp = motif1;
		motif1 = motif2;
		motif2 = temp;
	}
	if ((motif1 % 2 && motif1 == motif2 + 1 && (motif1 < 8))) {
		return true;
	}
	return false;
}


bool VerifierJointures(unsigned noCase, vector<unsigned>& sens, vector<unsigned>& ordrePieces) {
	bool estOk = true;
	Piece pieceAVerifier = PIECES[ordrePieces[noCase]];
	Piece secondePiece;
	//Vérifier à gauche
	if (!(noCase % 3)) {
		secondePiece = PIECES[ordrePieces[noCase - 1]];
		estOk = estOk && motifsComplementaires(pieceAVerifier[3], secondePiece[1]);
	}

	//Vérifier en haut
	if (noCase > 2) {
		secondePiece = PIECES[ordrePieces[noCase - 3]];
		estOk = estOk && motifsComplementaires(pieceAVerifier[0], secondePiece[2]);
	}
	return estOk;
}

void tournerPiece(Piece& piece, char sens)
{
	Piece pieceRetour;
	for (int i = 0; i < 4; ++i)
	{
		pieceRetour[i] = i != 3 ? piece[i + 1] : piece[0];
		sens = sens != 'd' ? sens++ : sens = 'a';
	}
	piece = pieceRetour;
}

Piece pieceVide{ NONE, NONE, NONE, NONE };
vector<Piece> grille{ pieceVide, pieceVide, pieceVide, pieceVide,
					 pieceVide, pieceVide, pieceVide, pieceVide, pieceVide };


void Permuter(unsigned noCase, Pieces piecesRestantes) {
	// Essaye de poser chaque pièces restantes sur la case
	char ui = 'a';
	for (size_t i = 0; i < piecesRestantes.size(); ++i) {
		for (size_t j = 0; j < 4; ++j) {
			//tourner puis poser la piece
			tournerPiece(piecesRestantes[i], ui);
			grille[noCase] = piecesRestantes[i];

			if (true && noCase != 8) {
				piecesRestantes.erase(piecesRestantes.begin() + i);
				Permuter(noCase + 1, piecesRestantes);
			}
			else
			{
				if (noCase == 8) {
					cout << " i = " << i << endl << "j = " << j << endl;
					piecesRestantes = PIECES;
				}
			}
		}
	}
}

int main() {
	vector<unsigned> sens(9);
	vector<unsigned> ordrePieces(9);

	/*AttachementType m1 = AttachementType::ARROSOIR_DROIT;
	AttachementType m2 = AttachementType::ARROSOIR_GAUCHE;
	AttachementType m3 = AttachementType::ARROSOIR_INVERSE;
	AttachementType m4 = AttachementType::NONE;
	AttachementType m5 = AttachementType::FILLE_BAS;
	AttachementType m6 = AttachementType::FILLE_HAUT;
	AttachementType m7 = AttachementType::DAME_HAUT;

	cout << motifsComplementaires(m1, m2) << endl;
	cout << motifsComplementaires(m2, m1) << endl;
	cout << motifsComplementaires(m1, m3) << endl;
	cout << motifsComplementaires(m3, m5) << endl;
	cout << motifsComplementaires(m6, m5) << endl;
	cout << motifsComplementaires(m7, m5) << endl;
	cout << motifsComplementaires(m5, m7) << endl;
	cout << motifsComplementaires(m3, m3) << endl;
	cout << motifsComplementaires(m1, m1) << endl;*/
	Pieces copiePieces = PIECES;

	Permuter(0, copiePieces);

	system("PAUSE");
   return EXIT_SUCCESS;
}
