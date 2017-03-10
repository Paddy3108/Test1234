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
ZugListe erstelleZugListe(Brett* brett, int x, int y, bool startwertEinbeziehen);

#endif // ZUG_H_INCLUDED
