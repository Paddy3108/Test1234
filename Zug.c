#include "Zug.h"
#include "string.h"

/*
 * Funktion:
 * Fuegt ein Schritt ans Ende der Liste hinzu
 *
 * Parameter:
 * liste: Pointer auf die zugliste
 * zug: Pointer auf zug
 *
 * Rueckgabewert: void
 *
 */
void zugHinzufuegen(ZugListe* liste, Zug* zug){
    if((*liste).anzahlZuege < 8){
        memcpy(&(*liste).zuege[(*liste).anzahlZuege++], zug, sizeof(Zug));
        return;
    }
}


/*
 * Funktion:
 * kontrolliert, ob moegliche Zuege valide sind
 * (x/y-Wert ist größer-gleich null und kleiner als die Brettbreite
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * zug: Pointer auf zug
 *
 * Rueckgabewert: boolean
 * Zug valide - true - 1
 * Zug nicht valide - false - 0
 */
bool zugValidieren(Brett* brett, Zug* zug) {
    return 	((*zug).x >= 0) &&
    		((*zug).x < (*brett).brettGroesse) &&
			((*zug).y >= 0) &&
			((*zug).y < (*brett).brettGroesse);
}

/*
 * Funktion:
 * Kontrolliert im Schachbrett, ob das Feld frei ist (-1, bzw. auch 0 wenn das Startfeld dazugehören darf)
 *
 * Parameter
 * brett: Pointer auf das Schachbrett
 * zug: Pointer auf Zug
 * shouldOfferStart: ob der Startpunkt dazuzaehlt oder nicht
 *
 * Rueckgabewert: bool
 * Feld ist frei: true - 1
 * Feld ist besetzt: false - 0
 */
bool brettUeberpruefen(Brett* brett, Zug* zug, bool shouldOfferStart) {
    return brettGetPositionswert(brett, (*zug).x, (*zug).y) == -1 || (shouldOfferStart && brettGetPositionswert(brett, (*zug).x, (*zug).y) == 0);
}

/*
 * Funktion:
 * liefert den Wert der Liste an einem bestimmten Index zurück
 *
 * Parameter:
 * liste: Pointer auf die ZugListe
 * index: Stelle der Liste
 *
 * Rueckgabewert: Zug-Pointer
 */
Zug* erhalteZugAusZugliste(ZugListe* list, unsigned int index) {
    return &(*list).zuege[index];
}

/*
 * Funktion:
 * Liefert eine Liste aller Schritte, die an der aktuellen Position des Schachbretts moeglich sind
 *
 * Parameter:
 * brett: Pointer auf das Board
 * x: X - Koordinate
 * y: Y - Koordinate
 * startwertEinbeziehen: Gehoert der Startpunkt der Liste zum Inhalt oder nicht
 *
 * Rueckgabewert: ZugListe
 */
ZugListe erstelleZugListe(Brett* brett, int x, int y, bool startwertEinbeziehen) {
	ZugListe zugListe;
	zugListe.anzahlZuege = 0;

    int springer_zuege[8][2] = {{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};

    for(int i = 0; i < 8; i++) {
    	Zug zug = {x + springer_zuege[i][0], y + springer_zuege[i][1]};
    	if(zugValidieren(brett, &zug) && brettUeberpruefen(brett, &zug, startwertEinbeziehen))
    		zugHinzufuegen(&zugListe, &zug);
    }

    return zugListe;
}

/*
 * Funktion:
 * liefert Anzahl der moeglichen Schritte zurück, die von einem bestimmten Feld gemacht werden können
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * x: X - Koordinate
 * Y: Y - Koordinate
 * startwertEinbeziehen: Ist der Startpunkt Inhalt der Liste oder nicht
 *
 * Rueckgabewert: integer-Wert ohne Vorzeichen mit der Anzahl der möglichen Zuege
 */
unsigned int anzahlMoeglicherZuegeFinden(Brett* brett, unsigned int x, unsigned int y, bool startwertEinbeziehen) {
    unsigned int anzahlZuege = 0;
    int springer_zuege[8][2] = {{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};

    for(int i = 0; i < 8; i++) {
    	Zug zug = {x + springer_zuege[i][0], y + springer_zuege[i][1]};
    	    if(zugValidieren(brett, &zug) && brettUeberpruefen(brett, &zug, startwertEinbeziehen))
    	        ++anzahlZuege;
    }

    return anzahlZuege;
}
