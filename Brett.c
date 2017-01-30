#include "Brett.h"

#include <stdlib.h>
#include <stdio.h>


/*
 * Funktion:
 * Dem Board wird zu Beginn die Boardgroesse zugewiesen und es werden so viele Felder reserviert
 * Alle Felder werden erstmal auf -1 gesetzt
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * brettgroesse: Brettgroesse
 *
 * Rückgabewert: void
 *
 */

void brettInitialisieren(Brett* brett, unsigned int brettGroesse)
{
    (*brett).brettGroesse = brettGroesse;
    (*brett).data = (int*)malloc(((*brett).brettGroesse * (*brett).brettGroesse)*sizeof(int));

    int brettFelder = ((*brett).brettGroesse*(*brett).brettGroesse);
    for(unsigned int i = 0; i < brettFelder ; ++i)
    {
        (*brett).data[i] = -1;
    }
}


/*
 * Funktion:
 * Kann den reservierten Speicher wieder frei geben
 *
 * Parameter:
 * brett: Pointer auf das Brett
 *
 * Rückgabewert: void
 *
 */

void brettSpeicherFreigeben(Brett* brett)
{
    free((*brett).data);
}


/*
 * Funktion:
 * Liefert den Wert an der jeweiligen Position zurueck
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * x: X - Koordinate
 * Y: Y - Koordinate
 *
 * Rückgabewert: Wert der Position
 *
 */

int brettGetPositionswert(Brett* brett, unsigned int x, unsigned int y)
{
    return (*brett).data[y * (*brett).brettGroesse + x];
}


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
 * Rückgabewert: void
 *
 */

void brettSetPositionswert(Brett* brett, unsigned int x, unsigned int y, int wert)
{
    (*brett).data[y * (*brett).brettGroesse + x] = wert;
}


/*
 * Funktion:
 * Gibt das Brett aus
 *
 * Parameter:
 * brett: Pointer auf das Brett
 *
 * Rückgabewert: void
 *
 */

void brettAusgeben(Brett* brett)
{
    printf("%s", "|");
    for(unsigned int i = 0; i < (*brett).brettGroesse; ++i)
    {
        printf("%s", "---");
    }
    printf("|\n");
    for(unsigned int y = 0; y < (*brett).brettGroesse; ++y)
    {
        printf("%s", "|");
        for(unsigned int x = 0; x < (*brett).brettGroesse; ++x)
        {
            int wert = brettGetPositionswert(brett, x, y);
            if(wert == -1)
                printf("% 3c", 'x');
            else if(wert == (*brett).brettGroesse*(*brett).brettGroesse)
                printf("% 3c", 'X');
            else
                printf("% 3d", wert);
        }
        printf("%s", "|\n");
    }
    printf("%s", "|");
    for(unsigned int i = 0; i < (*brett).brettGroesse; ++i)
    {
        printf("%s", "---");
    }
    printf("|\n");
}


/*
 * Funktion:
 * Nimmt das geloeste Brett mit dem Startwert 0|0 und verschiebt die ganzen Werte um den Wert der auf der eigentlichen Startposition steht
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * rx: X - Koordinate
 * ry: Y - Koordinate
 *
 * Rückgabewert: void
 *
 */

void brettWiederbeschreiben(Brett* brett, unsigned int rx, unsigned int ry)
{

    int relative = brettGetPositionswert(brett, rx, ry);
    if(relative == 0) return;
    unsigned int brettGroesse = (*brett).brettGroesse*(*brett).brettGroesse;
    for(unsigned int x = 0; x < (*brett).brettGroesse; ++x)
    {
        for(unsigned int y = 0; y < (*brett).brettGroesse; ++y)
        {
            int neuerWert = (((brettGetPositionswert(brett, x, y) - relative) % brettGroesse) + brettGroesse) % brettGroesse;
            brettSetPositionswert(brett, x, y, neuerWert);
        }
    }
}
