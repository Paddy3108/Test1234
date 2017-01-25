#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "Board.h"
#include <stdbool.h>

/*
 * Move Struct, mit der x und y - Koordinate
 */
typedef struct Move
{
    unsigned int x;
    unsigned int y;
} Move;

/*
 * Sortiert die naechsten Zuege nach moeglichen Nachbarn in aufsteigender Reihenfolge und speichert es in diesem struct
 * move: Instanz von dem Move struct
 * neighborCount: Moegliche Anzahl von Schritten in diesem Schritt
 */
typedef struct HeuristicMove
{
    Move move;
    unsigned int neighborCount;
} HeuristicMove;

/*
 * Move Liste behaelt maximal 8 Schritte
 * data: Schritte in der Liste
 * dataCount: Anzahl der schon erledigten Schritte
 */
typedef struct MoveList
{
    Move data[8];
    unsigned int dataCount;
} MoveList;

/*
 * Die heuristische Version von der MoveListe
 * data: heuristischen Schritte in der Liste
 * dataCount: Anzahl der schon erledigten Schritte
 */
typedef struct HeuristicMoveList
{
    HeuristicMove data[8];
    unsigned int dataCount;
} HeuristicMoveList;

/*
 * moveList: Pointer auf die moveListe
 * Initialisiert die MoveListe
 */
void moveList_initialize(MoveList* moveList);

/*
 * list: Pointer auf die moveList
 * move: Pointer auf Move
 * Fuegt ein Schritt ans Ende der Liste hinzu
 */
void moveList_push(MoveList* list, Move* move);

/*
 * list: Pointer auf die moveList
 * index: Stelle der Liste
 * Liefert den Pointer, der auf den Wert an der Stelle des index in der Liste zeigt
 */
Move* moveList_get(MoveList* list, unsigned int index);

/*
 * list: Pointer auf die HeuristicMoveList
 * move: Pointer auf Move
 * Fuegt ein Schritt ans Ende der Liste hinzu
 */
void heuristicMoveList_push(HeuristicMoveList* list, HeuristicMove* move);

/*
 * list: Pointer auf die HeuristicMoveList
 * Sortierung der heuristischen Liste, um den Warnsdorf Algorithmus umzusetzen
 */
void heuristicMoveList_sort(HeuristicMoveList* list);

/*
 * board: Pointer auf das Board
 * x: X - Koordinate
 * y: Y - Koordinate
 * shouldOfferStart: Ist der Startpunkt Inhalt der Liste oder nicht
 * Liefert alle Schritte, die an der aktuellen Position des Boards moeglich sind
 */
MoveList generateMoveList(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart);

/*
 * board: Pointer auf das Board
 * moveList: Pointer auf die moveList
 * shouldOfferStart: Ist der Startpunkt Inhalt der Liste oder nicht
 * Liefert eine sortierte Liste mit allen moeglichen Schritten mit ihren Nachbarn zurueck
 */
HeuristicMoveList generateHeuristic(Board* board, MoveList* moveList, bool shouldOfferStart);

#endif // MOVE_H_INCLUDED
