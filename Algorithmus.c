#include "Algorithmus.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Brett.h"
#include "Zug.h"


/*
 * Recursive function, tries the given move on the given board and all subsequent moves by the Warnsdorf heuristic
 * board: Pointer auf das Board
 * x: X - Koordinate
 * y: Y - Koordinate
 * n: aktuelle Anzahl der Durchlaeufe
 * closedTour: Geschlossener oder Offener Weg
 */
bool tryPath(Board* board, unsigned int x, unsigned int y, unsigned int n, bool closedTour)
{

    unsigned int boardSize = (*board).boardSize;
    // Setzt an (x|Y) den Wert n (Startwert = 0)
    board_setValue(board, x, y, n);


    // Wenn Anzahl der Durchlaeufe gleich der Anzahl der Felder => Loesung gefunden
    // Wenn wir einen offenen Weg haben wollen, muessen wir eins abziehen, weil n bei 0 anfaengt
    // Bei einem geschlossenen Weg ziehen wir nichts ab
    int dif = 0;
    if(closedTour) dif = 0;
    else dif = 1;
    if(n == (boardSize*boardSize - dif))
    {
        return true;
    }

    // Entscheidet ob der Startpunkt mit in der Liste vorhanden sein soll
    // Dies ist der Fall bei einem geschlossenen Weg
    bool shouldOfferStart = (closedTour && n == (boardSize * boardSize) - 1);
    ZugListe moveList = erstelleZugListe(board, x, y, shouldOfferStart);
    HeuristikZugListe list = erstelleHeuristik(board, &moveList, shouldOfferStart);

    // Geht alle moeglichen Wege ab
    for(unsigned int i = 0; i < list.anzahlZuege; ++i)
    {
        HeuristikZug* move = &list.zuege[i];
        bool result = tryPath(board, (*move).zug.x, (*move).zug.y, n+1, closedTour);
        if(result)
        {
            // Loesung gefunden
            return true;
        }
    }
    // Keine Loesung, setzt das Feld wieder auf "unbesucht" (-1)
    board_setValue(board, x, y, -1);
    return false;
}

/*
 * boardSize: Groesse des Boards
 * x : Start X - Koordinate
 * y : Start Y - Koordinate
 * closedTour: Geschlosser oder offener Weg
 * Versucht das Springerproblem mit den gegeben Variablen zu loesen
 */
void knightsTour(unsigned int boardSize, unsigned int x, unsigned int y, bool closedTour)
{
    Board board;
    board_initialize(&board, boardSize);
    bool result = false;
    if(closedTour)
    {
        result = tryPath(&board, 0, 0, 0, closedTour);
        if(result)
        {
          board_rewriteClosed(&board, x, y);
        }
    }
    else
    {
        result = tryPath(&board, x, y, 0, closedTour);
    }

    if(result)
    {
        board_print(&board);
    }
    else
    {
        printf("%s", "No solution found");
    }
   board_destruct(&board);
}
