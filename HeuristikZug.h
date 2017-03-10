#ifndef HEURISTIKZUG_H_INCLUDED
#define HEURISTIKZUG_H_INCLUDED

#include <stdbool.h>
#include "Brett.h"
#include "Zug.h"

/*
 * HeuristikZug Struktur
 * zug: Instanz der Zug Struktur
 * anzahlNachbarn: Anzahl von Nachbarn
 *
 * Struktur wird benutzt, um Zuege in einer Liste in sortierter (aufsteigender) Reihenfolge nach Anzahl der Nachbarn abzuspeichern
 */
typedef struct HeuristikZug {
    Zug zug;
    unsigned int anzahlNachbarn;
} HeuristikZug;

/*
 * Die heuristische Version von der ZugListe
 * zuege: heuristische Schritte in der Liste
 * anzahlZuege: Anzahl der schon erledigten Schritte
 */
typedef struct HeuristikZugListe {
    HeuristikZug zuege[8];
    unsigned int anzahlZuege;
} HeuristikZugListe;

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
HeuristikZugListe erstelleHeuristik(Brett* brett, ZugListe* moveList, bool startwertEinbeziehen);

#endif // HEURISTIKZUG_H_INCLUDED
