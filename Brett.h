#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


/*
 * Funktion:
 * Struct "Brett"
 *
 * Parameter:
 * brettGroesse: Brettgroesse
 * data: Daten des Schachbrettes
 *
 *
 */

typedef struct Brett
{
    unsigned int brettGroesse;
    int* data;
} Brett;


/*
 * Funktion:
 * Initialisiert das Brett mit den zwei Variablen
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * brettgroesse: Brettgroesse
 *
 * Rückgabewert: void
 *
 */

void brettInitialisieren(Brett* brett, unsigned int brettGroesse);


/*
 * Funktion:
 * Gibt zuvor allokierten Speicher wieder frei
 *
 * Parameter:
 * brett: Pointer auf das Brett
 *
 * Rückgabewert: void
 *
 */

void brettSpeicherFreigeben(Brett* brett);


/*
 * Funktion:
 * Gibt den Wert von dem Board an der Stelle x und y zurück
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * x: X - Koordinate
 * Y: Y - Koordinate
 *
 * Rückgabewert: int - Wert der Position
 *
 */

int brettGetPositionswert(Brett* brett, unsigned int x, unsigned int y);


/*
 * Funktion:
 * Setzt den Wert von dem Board an der Stelle x und y zurück
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * x: X - Koordinate
 * Y: Y - Koordinate
 * wert: Wert des Feldes
 *
 * Rückgabewert: void
 *
 */

void brettSetPositionswert(Brett* brett, unsigned int x, unsigned int y, int wert);


/*
 * Funktion:
 * Gibt das Brett in der Konsole aus
 *
 * Parameter:
 * brett: Pointer auf das Brett
 *
 * Rückgabewert: void
 *
 */

void brettAusgeben(Brett* brett);

/*
 * Funktion:
 * Nimmt das geloeste Brett mit dem Startwert 0|0
 * und verschiebt die ganzen Werte um den Wert der auf der eigentlichen Startposition steht
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * x: X - Koordinate
 * Y: Y - Koordinate
 *
 * Rückgabewert: void
 *
 */

void brettWiederbeschreiben(Brett* brett, unsigned int x, unsigned int y);

#endif // BOARD_H_INCLUDED
