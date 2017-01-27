#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include <stdbool.h>
#include "Brett.h"

/*
 * Move Struct, mit der x und y - Koordinate
 */
typedef struct Zug
{
    int x;
    int y;
} Zug;

/*
 * Sortiert die naechsten Zuege nach moeglichen Nachbarn in aufsteigender Reihenfolge und speichert es in diesem struct
 * move: Instanz von dem Move struct
 * neighborCount: Moegliche Anzahl von Schritten in diesem Schritt
 */
typedef struct HeuristikZug
{
    Zug zug;
    unsigned int anzahlNachbarn;
} HeuristikZug;

/*
 * Move Liste behaelt maximal 8 Schritte
 * data: Schritte in der Liste
 * dataCount: Anzahl der schon erledigten Schritte
 */
typedef struct ZugListe
{
    Zug zuege[8];
    unsigned int anzahlZuege;
} ZugListe;

/*
 * Die heuristische Version von der MoveListe
 * data: heuristischen Schritte in der Liste
 * dataCount: Anzahl der schon erledigten Schritte
 */
typedef struct HeuristikZugListe
{
    HeuristikZug zuege[8];
    unsigned int anzahlZuege;
} HeuristikZugListe;

/*
 * moveList: Pointer auf die moveListe
 * Initialisiert die MoveListe
 */
void zugListeInitialisieren(ZugListe* zugListe);

/*
 * list: Pointer auf die moveList
 * move: Pointer auf Move
 * Fuegt ein Schritt ans Ende der Liste hinzu
 */
void moveList_push(ZugListe* zugListe, Zug* zug);

/*
 * list: Pointer auf die moveList
 * index: Stelle der Liste
 * Liefert den Pointer, der auf den Wert an der Stelle des index in der Liste zeigt
 */
Zug* moveList_get(ZugListe* zugListe, unsigned int index);

/*
 * list: Pointer auf die HeuristicMoveList
 * move: Pointer auf Move
 * Fuegt ein Schritt ans Ende der Liste hinzu
 */
void heuristicMoveList_push(HeuristikZugListe* heuristikZugListe, HeuristikZug* heuristikZug);

/*
 * list: Pointer auf die HeuristicMoveList
 * Sortierung der heuristischen Liste, um den Warnsdorf Algorithmus umzusetzen
 */
void heuristicMoveList_sort(HeuristikZugListe* heuristikZugListe);

/*
 * board: Pointer auf das Board
 * x: X - Koordinate
 * y: Y - Koordinate
 * shouldOfferStart: Ist der Startpunkt Inhalt der Liste oder nicht
 * Liefert alle Schritte, die an der aktuellen Position des Boards moeglich sind
 */
ZugListe erstelleZugListe(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart);

/*
 * board: Pointer auf das Board
 * moveList: Pointer auf die moveList
 * shouldOfferStart: Ist der Startpunkt Inhalt der Liste oder nicht
 * Liefert eine sortierte Liste mit allen moeglichen Schritten mit ihren Nachbarn zurueck
 */
HeuristikZugListe erstelleHeuristik(Board* board, ZugListe* moveList, bool shouldOfferStart);

#endif // MOVE_H_INCLUDED
