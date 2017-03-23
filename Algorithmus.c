#include "Algorithmus.h"
#include "HeuristikZug.h"

#include "stdio.h"

 /*
 * Funktion:
 * Rekursive Methode, die alle gegebenen Zuege mit ihren nachfolgenden Zuegen auf dem Brett ausprobiert bis sie eine Loesung
 * gefunden oder alle moeglichen Zuege ausprobiert hat.
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * x: X - Koordinate
 * y: Y - Koordinate
 * n: aktuelle Anzahl der Durchlaeufe
 * brettGroesse: Groesse des Bretts
 * unterschied: Bei geschlossenem Weg = 0 | Bei offenem Weg = 1
 * geschlossen: Geschlossener oder Offener Weg
 *
 * Rueckgabewert: boolean-Wert ob Loesung gefunden wurde oder nicht
 */
bool pfadTesten(Brett* brett, unsigned int x, unsigned int y, unsigned int n, unsigned int brettGroesse ,int unterschied, bool geschlossen) {

    // Setzt an (x|y) den Wert der aktuellen Anzahl der Durchläufe n (Startwert = 0)
    brettSetPositionswert(brett, x, y, n);

    // Wenn Anzahl der Durchlaeufe = Anzahl der Felder => Loesung gefunden
    if(n == (brettGroesse*brettGroesse - unterschied)) {
        return true;
    }

    // Entscheidet ob der Startpunkt mit in der Liste vorhanden sein soll (Variable startwertEinbeziehen) --> geschlossener Weg
    bool startwertEinbeziehen = (geschlossen && n == (brettGroesse * brettGroesse) - 1);
    ZugListe zugListe = erstelleZugListe(brett, x, y, startwertEinbeziehen);
    HeuristikZugListe heuristikListe = erstelleHeuristik(brett, &zugListe, startwertEinbeziehen);

    // Schleife über alle moeglichen Wege
    for(unsigned int i = 0; i < heuristikListe.anzahlZuege; ++i) {
        HeuristikZug* zug = &heuristikListe.zuege[i];
        bool loesungVorhanden = pfadTesten(brett, (*zug).zug.x, (*zug).zug.y, n+1, brettGroesse, unterschied, geschlossen);
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
 * Initialisieren des Bretts mit den uebergebenen Variablen
 * Methode für geschlossenenen bzw, offenen Weg aufrufen
 *
 * Parameter:
 * brettGroesse: Groesse des Boards
 * x : Start X - Koordinate
 * y : Start Y - Koordinate
 * geschlossen: Geschlosser oder offener Weg
 *
 * Rueckgabewert: void
 */
void springen(unsigned int brettGroesse, unsigned int x, unsigned int y, bool geschlossen) {
    Brett brett;
    brettInitialisieren(&brett, brettGroesse);

    // bei offenem Weg: Anzahl der Durchlaeufe -1, weil n bei 0 anfängt
    // bei geschlossenem Weg: nichts abziehen
    int unterschied = geschlossen? 0 : 1;

    bool loesungVorhanden = false;
    if(geschlossen) {
        loesungVorhanden = pfadTesten(&brett, 0, 0, 0, brettGroesse, unterschied, geschlossen);
        if(loesungVorhanden) {
          brettWiederbeschreiben(&brett, x, y);
        }
    } else {
        loesungVorhanden = pfadTesten(&brett, x, y, 0, brettGroesse , unterschied, geschlossen);
    }

    if(loesungVorhanden) {
        brettAusgeben(&brett, x, y,geschlossen);
    } else {
        printf("%s", "Keine Loesung gefunden");
    }
   brettSpeicherFreigeben(&brett);
}
