#ifndef ZUG_H_INCLUDED
#define ZUG_H_INCLUDED

#include <stdbool.h>
#include "Brett.h"

/*
 * Zug Struktur
 * x und y - Koordinate
 */
typedef struct Zug {
    int x;
    int y;
} Zug;

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
 * ZugListe Struktur
 *
 * ZugListe behaelt maximal 8 Schritte (wegen 8 Nachfolgern von einem Feld)
 * zuege: Schritte in der Liste
 * anzahlZuege: Anzahl der schon erledigten Schritte
 */
typedef struct ZugListe {
    Zug zuege[8];
    unsigned int anzahlZuege;
} ZugListe;

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
 * Liefert eine Liste aller Schritte, die an der aktuellen Position des Schachbretts moeglich sind
 *
 * Parameter:
 * brett: Pointer auf das Board
 * x: X - Koordinate
 * y: Y - Koordinate
 * startwertEinbeziehen: Gehoert der Startpunkt der Liste zum Inhalt oder nicht
 *
 * Rückgabewert: ZugListe
 */
ZugListe erstelleZugListe(Brett* brett, int x, int y, bool startwertEinbeziehen);

/*
 * Funktion:
 * Liefert eine sortierte Liste mit allen moeglichen Schritten mit ihren Nachbarn zurueck
 *
 * Parameter:
 * brett: Pointer auf das Schachbrett
 * zugListe: Pointer auf die ZugListe
 * startwertEinbeziehen: Ist der Startpunkt Inhalt der Liste oder nicht
 *
 * Rückgabewert: HeuristikZugListe, vollstaendig sortierte Liste nach der Warnsdorf-Heuristik
 */
HeuristikZugListe erstelleHeuristik(Brett* brett, ZugListe* moveList, bool startwertEinbeziehen);

#endif // ZUG_H_INCLUDED
