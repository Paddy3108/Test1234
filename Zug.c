#include "Zug.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

/*
 * moveList: Pointer auf die moveListe
 * Initialisiert die MoveListe
 */
void zugListeInitialisieren(ZugListe* zugListe)
{
    (*zugListe).anzahlZuege = 0;
}

/*
 * list: Pointer auf die moveList
 * move: Pointer auf Move
 * Fuegt ein Schritt ans Ende der Liste hinzu
 */
void moveList_push(ZugListe* liste, Zug* zug)
{
    if((*liste).anzahlZuege < 8)
    {
        memcpy(&(*liste).zuege[(*liste).anzahlZuege++], zug, sizeof(Zug));
        return;
    }
    assert(!"Out of memory in move list");
}

/*
 * moveList: Pointer auf die HeuristicmMoveListe
 * Initialisiert die HeuristikZugListe
 */
void heuristikZugListeInitialisieren(HeuristikZugListe* zugListe)
{
    (*zugListe).anzahlZuege = 0;
}

/*
 * list: Pointer auf die HeuristicMoveList
 * move: Pointer auf HeuristicMove
 * Fuegt ein Schritt ans Ende der Liste hinzu
 */
void heuristicMoveList_push(HeuristikZugListe* liste, HeuristikZug* zug)
{
    if((*liste).anzahlZuege < 8)
    {
        memcpy(&(*liste).zuege[(*liste).anzahlZuege++], zug, sizeof(HeuristikZug));
        return;
    }
    assert(!"Out of memory in heuristic move list");
}

/*
 * list: Pointer auf die HeuristikZugListe
 * Sortierung der Liste mit den Heuristischen Zügen, um den Warnsdorf Algorithmus umzusetzen
 */
void heuristikZugListeSortieren(HeuristikZugListe* liste)
{
	// Sortiert die Liste nach Insertion Sort Verfahren
	for(int i = 1; i < (*liste).anzahlZuege; i++) {
		HeuristikZug temp = (*liste).zuege[i];
		int j = i-1;
		while(temp.anzahlNachbarn < (*liste).zuege[j].anzahlNachbarn && j >=0) {
			(*liste).zuege[j+1] = (*liste).zuege[j];
			j--;
		}
		(*liste).zuege[j+1] = temp;
	}

}

/*
 * board: Pointer auf das Board
 * move: Pointer auf Move
 * Kontrolliert, ob moegliche Zuege valide sind
 */
bool zugValidieren(Board* board, Zug* zug)
{
    return 	((*zug).x >= 0) &&
    		((*zug).x < (*board).boardSize) &&
			((*zug).y >= 0)
			&& ((*zug).y < (*board).boardSize);
}

/*
 * board: Pointer auf das Board
 * move: Pointer auf Move
 * shouldOfferStart: ob der Startpunkt dazuz�hlt oder nicht
 * Kontrolliert das Board
 */
bool brettUeberpruefen(Board* board, Zug* move, bool shouldOfferStart)
{
    return board_getValue(board, (*move).x, (*move).y) == -1 || (shouldOfferStart && board_getValue(board, (*move).x, (*move).y) == 0);
}

/*
 * list: Pointer auf die MoveList
 * index: Stelle der Liste
 * Liefert den Wert der Liste an Index
 */
Zug* moveList_get(ZugListe* list, unsigned int index)
{
    assert((*list).anzahlZuege > index);
    return &(*list).zuege[index];
}

/*
 * board: Pointer auf das Board
 * x: X - Koordinate
 * y: Y - Koordinate
 * shouldOfferStart: Ist der Startpunkt Inhalt der Liste oder nicht
 * Liefert alle Schritte, die an der aktuellen Position des Boards moeglich sind
 */
ZugListe erstelleZugListe(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart)
{
	ZugListe zugListe;
	zugListeInitialisieren(&zugListe);

    int springer_zuege[8][2] = {{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};

    for(int i = 0; i < 8; i++) {
    	Zug zug = {x + springer_zuege[i][0], y + springer_zuege[i][1]};
    	if(zugValidieren(board, &zug) && brettUeberpruefen(board, &zug, shouldOfferStart))
    		moveList_push(&zugListe, &zug);
    }

    return zugListe;
}

/*
 * board: Pointer auf das Board
 * x: X - Koordinate
 * Y: Y - Koordinate
 * shouldOfferStart: Ist der Startpunkt Inhalt der Liste oder nicht
 * Liefert die Anzahl der moeglischen Schritte
 */
unsigned int generateMoveCount(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart)
{
    unsigned int moveCount = 0;
    int springer_zuege[8][2] = {{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};

    for(int i = 0; i < 8; i++) {
    	Zug move = {x + springer_zuege[i][0], y + springer_zuege[i][1]};
    	    if(zugValidieren(board, &move) && brettUeberpruefen(board, &move, shouldOfferStart))
    	        ++moveCount;
    }

    return moveCount;
}

/*
 * board: Pointer auf das Board
 * moveList: Pointer auf die moveList
 * shouldOfferStart: Ist der Startpunkt Inhalt der Liste oder nicht
 * Liefert eine sortierte Liste mit allen moeglichen Schritten mit ihren Nachbarn zurueck
 */
HeuristikZugListe erstelleHeuristik(Board* board, ZugListe* zugListe, bool shouldOfferStart)
{
    HeuristikZugListe heuristikZugListe;
    heuristikZugListeInitialisieren(&heuristikZugListe);
    for(unsigned int i = 0; i < (*zugListe).anzahlZuege; ++i)
    {
    	Zug* move = moveList_get(zugListe, i);
        unsigned int moveCount = generateMoveCount(board, (*move).x, (*move).y, shouldOfferStart);
        // Warnsdorf heuristic: Bevorzugt Felder mit weniger naechsten Schritten
        HeuristikZug heuristicMove = {{(*move).x, (*move).y}, moveCount};
        heuristicMoveList_push(&heuristikZugListe, &heuristicMove);
    }
    heuristikZugListeSortieren(&heuristikZugListe);
    return heuristikZugListe;
}
