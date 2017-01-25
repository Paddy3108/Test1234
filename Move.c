#include "Move.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

/*
 * moveList: Pointer auf die moveListe
 * Initialisiert die MoveListe
 */
void moveList_initialize(MoveList* moveList)
{
    (*moveList).dataCount = 0;
}

/*
 * list: Pointer auf die moveList
 * move: Pointer auf Move
 * Fuegt ein Schritt ans Ende der Liste hinzu
 */
void moveList_push(MoveList* list, Move* move)
{
    if((*list).dataCount < 8)
    {
        memcpy(&(*list).data[(*list).dataCount++], move, sizeof(Move));
        return;
    }
    assert(!"Out of memory in move list");
}

/*
 * moveList: Pointer auf die HeuristicmMoveListe
 * Initialisiert die HeuristicMoveListe
 */
void heuristicMoveList_initialize(HeuristicMoveList* moveList)
{
    (*moveList).dataCount = 0;
}

/*
 * list: Pointer auf die HeuristicMoveList
 * move: Pointer auf HeuristicMove
 * Fuegt ein Schritt ans Ende der Liste hinzu
 */
void heuristicMoveList_push(HeuristicMoveList* list, HeuristicMove* move)
{
    if((*list).dataCount < 8)
    {
        memcpy(&(*list).data[(*list).dataCount++], move, sizeof(HeuristicMove));
        return;
    }
    assert(!"Out of memory in heuristic move list");
}

/*
 * move1: Pointer auf den ersten HeuristicMove
 * move2: Pointer auf den zweiten HeuristicMove
 * Tauscht die zwei Schritte
 */
void swapHeuristic(HeuristicMove* move1, HeuristicMove* move2)
{
    HeuristicMove tmp = *move1;
    *move1 = *move2;
    *move2 = tmp;
}

/*
 * list: Pointer auf die HeuristicMoveList
 * Sortierung der heuristischen Liste, um den Warnsdorf Algorithmus umzusetzen
 */
void heuristicMoveList_sort(HeuristicMoveList* list)
{
    // Sortiert die Liste nach dem Bubble Sort Verfahren
    for(unsigned int outer = (*list).dataCount; outer; --outer)
    {
        bool didSwap = false;
        for(unsigned int inner = 0; inner < (outer - 1); ++inner)
        {
            HeuristicMove* current = &(*list).data[inner];
            HeuristicMove* next = &(*list).data[inner + 1];
            if((*current).neighborCount > (*next).neighborCount)
            {
                swapHeuristic(current, next);
                didSwap = true;
            }
        }
        if(!didSwap) break;
    }
}

/*
 * board: Pointer auf das Board
 * move: Pointer auf Move
 * Kontrolliert die Grenzen des Boards
 */
bool checkBounds(Board* board, Move* move)
{
    return (*move).x >= 0 && (*move).x < (*board).boardSize && (*move).y >= 0 && (*move).y < (*board).boardSize;
}

/*
 * board: Pointer auf das Board
 * move: Pointer auf Move
 * shouldOfferStart: ob der Startpunkt dazuzählt oder nicht
 * Kontrolliert das Board
 */
bool checkBoard(Board* board, Move* move, bool shouldOfferStart)
{
    return board_getValue(board, (*move).x, (*move).y) == -1 || (shouldOfferStart && board_getValue(board, (*move).x, (*move).y) == 0);
}

/*
 * list: Pointer auf die MoveList
 * index: Stelle der Liste
 * Liefert den Wert der Liste an Index
 */
Move* moveList_get(MoveList* list, unsigned int index)
{
    assert((*list).dataCount > index);
    return &(*list).data[index];
}

/*
 * board: Pointer auf das Board
 * x: X - Koordinate
 * y: Y - Koordinate
 * shouldOfferStart: Ist der Startpunkt Inhalt der Liste oder nicht
 * Liefert alle Schritte, die an der aktuellen Position des Boards moeglich sind
 */
MoveList generateMoveList(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart)
{
    MoveList moveList;
    moveList_initialize(&moveList);

    Move move = {x + 1, y + 2}; //Schrittfolge des Springers
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x + 2, y + 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x + 2, y - 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x + 1, y - 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x - 1, y - 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x - 2, y - 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x - 2, y + 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x - 1, y + 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    return moveList;
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

    Move move = {x + 1, y + 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x + 2, y + 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x + 2, y - 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x + 1, y - 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x - 1, y - 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x - 2, y - 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x - 2, y + 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x - 1, y + 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    return moveCount;
}

/*
 * board: Pointer auf das Board
 * moveList: Pointer auf die moveList
 * shouldOfferStart: Ist der Startpunkt Inhalt der Liste oder nicht
 * Liefert eine sortierte Liste mit allen moeglichen Schritten mit ihren Nachbarn zurueck
 */
HeuristicMoveList generateHeuristic(Board* board, MoveList* moveList, bool shouldOfferStart)
{
    HeuristicMoveList heuristicMoveList;
    heuristicMoveList_initialize(&heuristicMoveList);
    for(unsigned int i = 0; i < (*moveList).dataCount; ++i)
    {
        Move* move = moveList_get(moveList, i);
        unsigned int moveCount = generateMoveCount(board, (*move).x, (*move).y, shouldOfferStart);
        // Warnsdorf heuristic: Bevorzugt Felder mit weniger naechsten Schritten
        HeuristicMove heuristicMove = {{(*move).x, (*move).y}, moveCount};
        heuristicMoveList_push(&heuristicMoveList, &heuristicMove);
    }
    heuristicMoveList_sort(&heuristicMoveList);
    return heuristicMoveList;
}
