#include "Algorithmus.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Brett.h"
#include "Zug.h"

 /*
 * Funktion:
 * Funktionsbeschreibung: Recursive function, tries the given move on the given board and all subsequent moves by the Warnsdorf heuristic
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * x: X - Koordinate
 * y: Y - Koordinate
 * n: aktuelle Anzahl der Durchlaeufe
 * geschlossen: Geschlossener oder Offener Weg
 *
 * Rückgabewert: boolean-Wert ob Loesung gefunden wurde oder nicht
 */
bool pfadTesten(Brett* brett, unsigned int x, unsigned int y, unsigned int n, bool geschlossen) {

    unsigned int brettGroesse = (*brett).brettGroesse;

    // Setzt an (x|y) den Wert der aktuellen Anzahl der Durchläufe n (Startwert = 0)
    brettSetPositionswert(brett, x, y, n);

    // Wenn Anzahl der Durchlaeufe = Anzahl der Felder => Loesung gefunden
    // bei offenem Weg: Anzahl der Durchlaeufe -1, weil n bei 0 anfängt
    // bei geschlossenem Weg: nichts abziehen
    int unterschied = 0;
    if(geschlossen) unterschied = 0;
    else unterschied = 1;
    if(n == (brettGroesse*brettGroesse - unterschied)) {
        return true;
    }

    // Entscheidet ob der Startpunkt mit in der Liste vorhanden sein soll (Variable startwertEinbeziehen) --> geschlossener Weg
    bool startwertEinbeziehen = (geschlossen && n == (brettGroesse * brettGroesse) - 1);
    ZugListe zugListe = erstelleZugListe(brett, x, y, startwertEinbeziehen);
    HeuristikZugListe liste = erstelleHeuristik(brett, &zugListe, startwertEinbeziehen);

    // Schleife über alle moeglichen Wege
    for(unsigned int i = 0; i < liste.anzahlZuege; ++i) {
        HeuristikZug* zug = &liste.zuege[i];
        bool loesungVorhanden = pfadTesten(brett, (*zug).zug.x, (*zug).zug.y, n+1, geschlossen);
        if(loesungVorhanden) {
            // Loesung gefunden
            return true;
        }
    }
    // Keine Loesung, setzt das Feld wieder auf "unbesucht" (-1)
    brettSetPositionswert(brett, x, y, -1);
    return false;
}


 /*
 * Funktion:
 * Initialisieren des Boards mit den uebergebenen Variablen
 * Methode für geschlossenenen bzw, offenen Weg aufrufen
 *
 * Parameter:
 * brettGroesse: Groesse des Boards
 * x : Start X - Koordinate
 * y : Start Y - Koordinate
 * geschlossen: Geschlosser oder offener Weg
 *
 * Rückgabewert: void
 */
void springen(unsigned int brettGroesse, unsigned int x, unsigned int y, bool geschlossen) {
    Brett brett;
    brettInitialisieren(&brett, brettGroesse);
    bool loesungVorhanden = false;
    if(geschlossen) {
        loesungVorhanden = pfadTesten(&brett, 0, 0, 0, geschlossen);
        if(loesungVorhanden) {
          brettWiederbeschreiben(&brett, x, y);
        }
    } else {
        loesungVorhanden = pfadTesten(&brett, x, y, 0, geschlossen);
    }

    if(loesungVorhanden) {
        brettAusgeben(&brett);
    } else {
        printf("%s", "Keine Loesung gefunden");
    }
   brettSpeicherFreigeben(&brett);
}
