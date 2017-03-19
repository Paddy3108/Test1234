#include "HeuristikZug.h"
#include <string.h>

/*
 * Funktion:
 * Fuegt ein Feld/Schritt ans Ende der Liste hinzu
 *
 * Parameter:
 * heuristikListe: Pointer auf die HeuristikZugListe
 * zug: Pointer auf HeuristikZug
 *
 * Rueckgabewert: void
 *
 */
void heuristikZugHinzufuegen(HeuristikZugListe* heuristikListe, HeuristikZug* zug) {
    if((*heuristikListe).anzahlZuege < 8) {
        memcpy(&(*heuristikListe).zuege[(*heuristikListe).anzahlZuege++], zug, sizeof(HeuristikZug));
        return;
    }
}

/*
 * Funktion:
 * Sortiert die Liste nach der Warnsdorf Heuristik - die Felder mit den wenigsten Nachfolgern kommen zuerst dran
 *
 * Parameter:
 * heuristikListe: Pointer auf die HeuristikZugListe
 *
 * Rueckgabewert: void
 */

void heuristikZugListeSortieren(HeuristikZugListe* heuristikListe) {
	// Sortiert die Liste nach Insertion Sort Verfahren
	for(int i = 1; i < (*heuristikListe).anzahlZuege; i++) {
		HeuristikZug temp = (*heuristikListe).zuege[i];
		int j = i-1;
		while(temp.anzahlNachbarn < (*heuristikListe).zuege[j].anzahlNachbarn && j >=0) {
			(*heuristikListe).zuege[j+1] = (*heuristikListe).zuege[j];
			j--;
		}
		(*heuristikListe).zuege[j+1] = temp;
	}

}

/*
 * Funktion:
 * Liefert eine sortierte Liste mit allen moeglichen Schritten mit ihren Nachbarn zurueck
 *
 * Parameter:
 * brett: Pointer auf das Schachbrett
 * zugListe: Pointer auf die ZugListe
 * startwertEinbeziehen: Ist der Startpunkt Inhalt der Liste oder nicht
 *
 * Rueckgabewert: HeuristikZugListe, vollstaendig sortierte Liste nach der Warnsdorf-Heuristik
 */
HeuristikZugListe erstelleHeuristik(Brett* brett, ZugListe* zugListe, bool startwertEinbeziehen) {
    HeuristikZugListe heuristikZugListe;
    heuristikZugListe.anzahlZuege = 0;

    for(unsigned int i = 0; i < (*zugListe).anzahlZuege; ++i) {
    	Zug* zug = erhalteZugAusZugliste(zugListe, i);
        unsigned int anzahlZuege = anzahlMoeglicherZuegeFinden(brett, (*zug).x, (*zug).y, startwertEinbeziehen);
        // Warnsdorf Heuristik: Bevorzugt Felder mit weniger naechsten Schritten
        HeuristikZug heuristikZug = {{(*zug).x, (*zug).y}, anzahlZuege};
        heuristikZugHinzufuegen(&heuristikZugListe, &heuristikZug);
    }
    heuristikZugListeSortieren(&heuristikZugListe);
    return heuristikZugListe;
}
