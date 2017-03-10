#include "Brett.h"

#include <stdlib.h>
#include <stdio.h>

#include <windows.h>
#define FOREGROUND_WHITE   7

/*
 * Funktion:
 * Dem Brett wird zu Beginn die Boardgroesse zugewiesen und es werden so viele Felder allokiert wie die Brettgroesse ist.
 * Alle Felder werden auf -1 gesetzt --> -1 = unbesucht
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * brettgroesse: Brettgroesse
 *
 * Rueckgabewert: void
 */
void brettInitialisieren(Brett* brett, unsigned int brettGroesse) {
    (*brett).data = malloc((brettGroesse * brettGroesse)*sizeof(int));
    (*brett).brettGroesse = brettGroesse;

    for(unsigned int i = 0; i < brettGroesse*brettGroesse ; ++i) {
        (*brett).data[i] = -1;
    }
}


/*
 * Funktion:
 * Gibt den zuvor allokierten Speicher wieder frei
 *
 * Parameter:
 * brett: Pointer auf das Brett
 *
 * Rueckgabewert: void
 */
void brettSpeicherFreigeben(Brett* brett) {
    free((*brett).data);
}


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
int brettGetPositionswert(Brett* brett, unsigned int x, unsigned int y) {
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
 * Rueckgabewert: void
 */
void brettSetPositionswert(Brett* brett, unsigned int x, unsigned int y, int wert) {
    (*brett).data[y * (*brett).brettGroesse + x] = wert;
}


/*
 * Funktion:
 * Gibt das Brett in der Konsole aus
 * Rot: Markiert das Startfeld
 * Gruen: Markiert das Endfeld
 *
 * Parameter:
 * brett: Pointer auf das Brett
 *
 * Rückgabewert: void
 */
void brettAusgeben(Brett* brett){
    printf("%s", "|");
    for(unsigned int i = 0; i < (*brett).brettGroesse; ++i) {
        printf("%s", "-----");
    }
    printf("|\n");
    for(unsigned int y = 0; y < (*brett).brettGroesse; ++y) {
        printf("%s", "|");
        for(unsigned int x = 0; x < (*brett).brettGroesse; ++x) {
            int wert = brettGetPositionswert(brett, x, y);
                if (wert == (*brett).brettGroesse*(*brett).brettGroesse -1) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN );
                printf("%3d", wert);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_WHITE);
                printf(" |");
            } else if (wert == 0) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED );
                printf("%3d", wert);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_WHITE);
                printf(" |");
            }
            else printf("%3d |", wert);
        }
        printf("%s", "|\n");
    }
    printf("%s", "|");
    for(unsigned int i = 0; i < (*brett).brettGroesse; ++i) {
        printf("%s", "-----");
    }
    printf("|\n");
}


/*
 * Funktion:
 * Nimmt das geloeste Brett mit dem Startwert 0|0
 * und verschiebt die ganzen Werte um den Wert der auf der eigentlichen Startposition steht
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * startX: urspruengliche X - Koordinate
 * startX: urspruengliche Y - Koordinate
 *
 * Rueckgabewert: void
 */
void brettWiederbeschreiben(Brett* brett, unsigned int startX, unsigned int startY){
    int wertStartposition = brettGetPositionswert(brett, startX, startY);
    if(wertStartposition == 0) return;
    unsigned int brettGroesse = (*brett).brettGroesse*(*brett).brettGroesse;
    for(unsigned int x = 0; x < (*brett).brettGroesse; ++x) {
        for(unsigned int y = 0; y < (*brett).brettGroesse; ++y) {
            int neuerWert = (((brettGetPositionswert(brett, x, y) - wertStartposition) % brettGroesse) + brettGroesse) % brettGroesse;
            brettSetPositionswert(brett, x, y, neuerWert);
        }
    }
}
