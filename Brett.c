#include "Brett.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <windows.h>
#define FOREGROUND_WHITE   7

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
void brettInitialisieren(Brett* brett, unsigned int brettGroesse) {
    (*brett).daten = malloc((brettGroesse * brettGroesse)*sizeof(int));
    (*brett).brettGroesse = brettGroesse;

    for(unsigned int i = 0; i < brettGroesse*brettGroesse ; ++i) {
        (*brett).daten[i] = -1;
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
    free((*brett).daten);
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
    int position = y * (*brett).brettGroesse + x;
    return (*brett).daten[position];
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
    int position = y * (*brett).brettGroesse + x;
    (*brett).daten[position] = wert;
}


/*
 * Funktion:
 * Gibt das Brett in der Konsole aus
 * Rot: Markiert das Startfeld
 * Gruen: Markiert das Endfeld
 *
 * Parameter:
 * brett: Pointer auf das Brett
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
 * Rückgabewert: void
 */
void brettAusgeben(Brett* brett, bool geschlossen){
    printf("\t ");
	for (int zahl = 0; zahl < (*brett).brettGroesse; zahl++) {
		printf("%3c  ", 97 + zahl);
    }
    printf("\n\t%c", 201);
    for(unsigned int i = 0; i < (*brett).brettGroesse-1; ++i) {
      printf("%c%c%c%c%c", 205, 205, 205, 205, 203);
	}
    printf("%c%c%c%c%c\n", 205, 205, 205, 205, 187); //Ende Linie oben

    for(unsigned int y = 0; y < (*brett).brettGroesse; ++y) {
        printf("    %2d\t%c", y+1,186);
        for(unsigned int x = 0; x < (*brett).brettGroesse; ++x) {
            int wert = brettGetPositionswert(brett, x, y);
                if (wert == (*brett).brettGroesse*(*brett).brettGroesse -1) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN );
                printf("%3d ", wert);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_WHITE);
                printf("%c", 186);
            } else if (wert == 0) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED );
                printf("%3d ", wert);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_WHITE);
                printf("%c", 186);
            }
            else printf("%3d %c", wert, 186);
        }
        if (y!=(*brett).brettGroesse-1) {
            printf("\n\t%c", 204);
            for (int i = 0; i < (*brett).brettGroesse-1; i++) {
                printf("%c%c%c%c%c", 205, 205, 205, 205, 206);
            }
            printf("%c%c%c%c%c\n", 205, 205, 205, 205, 185);
        }
        else {  //Trennlinie im Feld
			printf("\n\t%c", 200);
			for (int i = 0; i<(*brett).brettGroesse-1; i++) {
				printf("%c%c%c%c%c", 205, 205, 205, 205, 202);
			}
            printf("%c%c%c%c%c\n", 205, 205, 205, 205, 188);

        }

    }
    printf("\nEine weitere Ausgabe ist in Form einer SVG-Datei im direkten Projektpfad zu finden.\nEs wird empfohlen die Datei \"Springerproblem.svg\" mit einem Internetbrowser zu oeffnen.\n\n");

    printf("\nEntwickler: \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
    printf("Patrick Eichert");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_WHITE );
    printf(", ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN );
    printf("Theresa Reus");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_WHITE );
    printf(", ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN );
    printf("Kristin Angelstein ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_WHITE );
    printf("und ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN );
    printf("Nico Frischkorn\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_WHITE );
    brettErstelleDatei(brett,geschlossen);

}

/*
 * Funktion:
 * Erstellt eine svg Datei, die die Spruenge darstellt
 *
 * Parameter:
 * brett: Pointer auf das Brett
 * bool: Geschlosser oder offener Weg
 *
 * Rueckgabewert: void
 */
void brettErstelleDatei(Brett* brett, bool geschlossen)
{
   int brettGroesse = ((*brett).brettGroesse) * ((*brett).brettGroesse);
   int xKoordinaten[brettGroesse];
   int yKoordinaten[brettGroesse];

   // Speichert die Anzahl der Schachfelder pro Zeile / Spalte
   int dimension =(*brett).brettGroesse;

   // Berechnet die Abmessungen, welche die SVG-Datei hat. +4 wird gerechnet, damit noch je 2 Pixel Abstand zu den Rändern sind.
   int hoeheBreite = 42 * dimension + 4;

   for(int y=0; y <dimension; y++) {
       for(int x=0; x<dimension;x++) {
           int wert = brettGetPositionswert(brett, x, y);
           xKoordinaten[wert] = x;
           yKoordinaten[wert] = y;
       }
   }
   FILE *out = fopen("Springerproblem.svg","w");
   /*
    * Als Grundlage fuer die SVG-Ausgabe diente eine SVG-Datei von Wikipedia:
    * https://de.wikipedia.org/wiki/Springerproblem#/media/File:Knight%27s_tour.svg
    */

   /* Der Kopf der SVG-Datei wird beschrieben */
   fprintf(out, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?> \n");
   /* width + height = Breite + Hoehe des gesamten SVG's; viewBox gibt an, welcher Bereich davon angezeigt werden soll, die ersten 2 Stellen verruecken das Bild ggf. */
   fprintf(out, "<svg width=\"%d\" height=\"%d\" version=\"1.1\" viewBox=\"0 0 %d %d\" xmlns=\"http://www.w3.org/2000/svg\">  \n\n", hoeheBreite, hoeheBreite, hoeheBreite, hoeheBreite);
   /* transform erstellt einen Abstand um das eigentliche Bild; scale vergroessert das Bild in dem angegebenen Bereich */
   fprintf(out, "<g transform=\"translate(10,10) scale(40)\">\n");
   /* Linienstaerke + -Farbe fuer Schachbrettraster */
   fprintf(out, "<g fill=\"white\" stroke=\"gray\" stroke-width=\"0.025\">\n");
   /* Aeußeres Rechteck um das Schachbrettmuster.*/
   fprintf(out, " <rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" />\n\n", dimension, dimension);

   /* Schachbrettmuster dynamisch generieren */
   for (int x=0; x<dimension; x++){
    for(int y= 0; y<dimension; y++){
        if((x+y)%2 == 0) {
           fprintf(out, "<rect x=\"%d\" y=\"%d\" width=\"1\" height=\"1\" fill=\"black\" />\n", x, y);
        }
        else {
            fprintf(out, "<rect x=\"%d\" y=\"%d\" width=\"1\" height=\"1\" fill=\"white\" />\n", x, y);
        }
    }
   }
   fprintf(out," </g>\n\n");
   /* Die Verbindungspunkte werden in der Mitte der Schachfelder positioniert */
   fprintf(out," <g transform=\"translate(0.5,0.5)\">\n\n");
   /* Definition des Startpunktes */
   fprintf(out," <circle cx=\"%d\" cy=\"%d\" r=\"0.15\" stroke=\"none\" fill=\"red\" />\n\n", xKoordinaten[0], yKoordinaten[0] );
   /* Beschriftung des Startpunktes */
   fprintf(out," <text id=\"eins\" x=\"%d\" y=\"%d\" " , xKoordinaten[0], yKoordinaten[0]);
   fprintf(out,"style=\"font-size:0.3px; font-family:Arial\" fill=\"red\" transform=\"translate(-0.35,0.1)\">\n");
   fprintf(out,"S\n");
   fprintf(out,"</text>\n\n");
   if (geschlossen) {
        /* Definition des Endpunktes im geschlossenen System. Hier ist Start- und Endpunkt der gleiche. */
        fprintf(out,"<circle cx=\"%d\" cy=\"%d\" ", xKoordinaten[0], yKoordinaten[0] );
        fprintf(out,"r=\"0.1\" stroke=\"none\" fill=\"green\" />\n\n");
        /* Beschriftung des Endpunktes */
        fprintf(out,"<text id=\"eins\" x=\"%d\" y=\"%d\" ", xKoordinaten[0], yKoordinaten[0]);
        fprintf(out,"style=\"font-size:0.3px; font-family:Arial\" fill=\"green\" transform=\"translate(0.12,0.1)\">\n");
        fprintf(out,"E\n");
        fprintf(out,"</text>\n\n");
   }
   else{
        /* Definition des Endpunktes im offenen System*/
        fprintf(out,"<circle cx=\"%d\" cy=\"%d\" ", xKoordinaten[brettGroesse-1], yKoordinaten[brettGroesse-1] );
        fprintf(out,"r=\"0.1\" stroke=\"none\" fill=\"green\" />\n\n");
        /* Beschriftung des Endpunktes */
        fprintf(out,"<text id=\"eins\" x=\"%d\" y=\"%d\" ", xKoordinaten[brettGroesse-1], yKoordinaten[brettGroesse-1]);
        fprintf(out,"style=\"font-size:0.3px; font-family:Arial\" fill=\"green\" transform=\"translate(0.12,0.1)\">\n");
        fprintf(out,"E\n");
        fprintf(out,"</text>\n\n");
   }
   /* Generieren der einzelnen Verbindungspunkte. Wichtig ist, dass die Punkte in der richtigen Reihenfolge generiert werden */
   fprintf(out,"<polyline points=\"");
   for(int wert=0; wert < brettGroesse;wert++) {
        fprintf(out,"%d,%d ", xKoordinaten[wert], yKoordinaten[wert]);
   }
   /* Im geschlossenen System muss noch die letzte Verbindungslinie zurück zum Startpunkt mit angegeben werden. */
   if(geschlossen) fprintf(out,"%d,%d ",xKoordinaten[0],yKoordinaten[0] );
   fprintf(out,"\" stroke=\"blue\" stroke-width=\"0.05\" fill=\"none\" />\n\n");
   fprintf(out,"</g>\n");
   fprintf(out,"</g>\n");
   fprintf(out,"</svg>\n");
   fclose(out);
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
