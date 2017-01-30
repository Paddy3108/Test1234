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
bool tryPath(Brett* brett, unsigned int x, unsigned int y, unsigned int n, bool closedTour)
{

    unsigned int boardSize = (*brett).brettGroesse;
    // Setzt an (x|Y) den Wert n (Startwert = 0)
    brettSetPositionswert(brett, x, y, n);


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
    ZugListe moveList = erstelleZugListe(brett, x, y, shouldOfferStart);
    HeuristikZugListe list = erstelleHeuristik(brett, &moveList, shouldOfferStart);

    // Geht alle moeglichen Wege ab
    for(unsigned int i = 0; i < list.anzahlZuege; ++i)
    {
        HeuristikZug* move = &list.zuege[i];
        bool result = tryPath(brett, (*move).zug.x, (*move).zug.y, n+1, closedTour);
        if(result)
        {
            // Loesung gefunden
            return true;
        }
    }
    // Keine Loesung, setzt das Feld wieder auf "unbesucht" (-1)
    brettSetPositionswert(brett, x, y, -1);
    return false;
}

/*
 * boardSize: Groesse des Boards
 * x : Start X - Koordinate
 * y : Start Y - Koordinate
 * closedTour: Geschlosser oder offener Weg
 * Versucht das Springerproblem mit den gegeben Variablen zu loesen
 */
void knightsTour(unsigned int brettGroesse, unsigned int x, unsigned int y, bool closedTour)
{
    Brett brett;
    brettInitialisieren(&brett, brettGroesse);
    bool result = false;
    if(closedTour)
    {
        result = tryPath(&brett, 0, 0, 0, closedTour);
        if(result)
        {
          brettWiederbeschreiben(&brett, x, y);
        }
    }
    else
    {
        result = tryPath(&brett, x, y, 0, closedTour);
    }

    if(result)
    {
        brettAusgeben(&brett);
    }
    else
    {
        printf("%s", "No solution found");
    }
   brettSpeicherFreigeben(&brett);
}
