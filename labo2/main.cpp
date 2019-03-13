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

void tournerPiece(Piece& piece)
{
	Piece pieceRetour;
	for (int i = 0; i < 4; ++i)
	{
		pieceRetour[i] = i != 3 ? piece[i + 1] : piece[0];
	}
	piece = pieceRetour;
}

int main() {
	vector<unsigned> sens(9);
	vector<unsigned> ordrePieces(9);

	AttachementType m1 = AttachementType::ARROSOIR_DROIT;
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
	cout << motifsComplementaires(m1, m1) << endl;
	system("PAUSE");
   return EXIT_SUCCESS;
}
