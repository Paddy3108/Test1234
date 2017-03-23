#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdbool.h>

/*
 * Funktion:
 * Struct "Brett"
 *
 * Parameter:
 * brettGroesse: Brettgroesse
 * daten: Daten des Schachbrettes
 */
typedef struct Brett{
    unsigned int brettGroesse;
    int* daten;
} Brett;


/*
 * Funktion:
 * Dem Brett wird zu Beginn die Brettgroesse zugewiesen und es werden so viele Felder allokiert wie die Brettgroesse ist.
 * Alle Felder werden auf -1 gesetzt --> -1 = unbesucht
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * brettgroesse: Brettgroesse
 *
 * Rueckgabewert: void
 */
void brettInitialisieren(Brett* brett, unsigned int brettGroesse);


/*
 * Funktion:
 * Gibt den zuvor allokierten Speicher wieder frei
 *
 * Parameter:
 * brett: Pointer auf das Brett
 *
 * Rueckgabewert: void
 */
void brettSpeicherFreigeben(Brett* brett);


/*
 * Funktion:
 * Liefert den Positionswert an der jeweiligen Position zurueck
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * x: X - Koordinate
 * Y: Y - Koordinate
 *
 * Rueckgabewert: Wert der Position (integer)
 */
int brettGetPositionswert(Brett* brett, unsigned int x, unsigned int y);


/*
 * Funktion:
 * Setzt den Wert an der jeweiligen Position
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * x: X - Koordinate
 * Y: Y - Koordinate
 * wert: Wert des Feldes
 *
 * Rueckgabewert: void
 */
void brettSetPositionswert(Brett* brett, unsigned int x, unsigned int y, int wert);


/*
 * Funktion:
 * Gibt das Brett in der Konsole aus
 * Rot: Markiert das Startfeld
 * Gruen: Markiert das Endfeld
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * startX: Start X - Koordinate
 * startY: Start Y - Koordinate
 * geschlossen: Geschlosser oder offener Weg
 *
 * ASCII Tabelle fuer den Rahmen:
 * 185: ╣
 * 186: ║
 * 187: ╗
 * 188: ╝
 * 200: ╚
 * 201: ╔
 * 202: ╩
 * 203: ╦
 * 204: ╠
 * 205: ═
 * 206: ╬
 *
 * Rueckgabewert: void
 */
void brettAusgeben(Brett* brett, int startX, int startY, bool geschlossen);

/*
 * Funktion:
 * Nimmt das geloeste Brett mit dem Startwert 0|0
 * und verschiebt die ganzen Werte um den Wert der auf der eigentlichen Startposition steht
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * startX: urspruengliche X - Koordinate
 * startY: urspruengliche Y - Koordinate
 *
 * Rueckgabewert: void
 */
void brettWiederbeschreiben(Brett* brett, unsigned int startX, unsigned int startY);

#endif // BOARD_H_INCLUDED
