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
    int zielX,zielY;
    printf("\t ");
	for (int zahl = 0; zahl < (*brett).brettGroesse; zahl++)
	{
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
                zielX = x;
                zielY = y;
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
        if (y!=(*brett).brettGroesse-1)
        {
            printf("\n\t%c", 204);
            for (int i = 0; i < (*brett).brettGroesse-1; i++)
            {
                printf("%c%c%c%c%c", 205, 205, 205, 205, 206);
            }
            printf("%c%c%c%c%c\n", 205, 205, 205, 205, 185);
        }
        else  //Trennlinie im Feld
		{
			printf("\n\t%c", 200);
			for (int i = 0; i<(*brett).brettGroesse-1; i++)
			{
				printf("%c%c%c%c%c", 205, 205, 205, 205, 202);
			}
            printf("%c%c%c%c%c\n", 205, 205, 205, 205, 188);

        }

    }
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
   if((*brett).brettGroesse == 8) brettErstelleDatei(brett,geschlossen);

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
void brettErstelleDatei (Brett* brett, bool geschlossen)
{
   int brettGroesse = ((*brett).brettGroesse) * ((*brett).brettGroesse);
   int xKoordinaten[brettGroesse];
   int yKoordinaten[brettGroesse];
   for(int y=0; y <(*brett).brettGroesse; y++)
   {
       for(int x=0; x<(*brett).brettGroesse;x++)
       {
        int wert = brettGetPositionswert(brett, x, y);
           xKoordinaten[wert] = x;
           yKoordinaten[wert] = y;
       }
   }
   FILE *out = fopen("Springerproblem.svg","w");
   fprintf(out, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?> \n");
   fprintf(out, "<svg width=\"340\" height=\"340\" version=\"1.1\" viewBox=\"0 0 340 340\" xmlns=\"http://www.w3.org/2000/svg\">  \n\n");
   fprintf(out, "<g transform=\"translate(10,10) scale(40)\">\n");
   fprintf(out, "<g fill=\"white\" stroke=\"gray\" stroke-width=\"0.025\">\n");
   fprintf(out, " <rect x=\"0\" y=\"0\" width=\"8\" height=\"8\" />\n\n");
   fprintf(out, " <rect x=\"0\" y=\"0\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"0\" y=\"1\" width=\"1\" height=\"1\" fill=\"white\" />\n");/**<  */
   fprintf(out, " <rect x=\"0\" y=\"2\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"0\" y=\"3\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"0\" y=\"4\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"0\" y=\"5\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"0\" y=\"6\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"0\" y=\"7\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"1\" y=\"0\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"1\" y=\"1\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"1\" y=\"2\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"1\" y=\"3\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"1\" y=\"4\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"1\" y=\"5\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"1\" y=\"6\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"1\" y=\"7\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"2\" y=\"0\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"2\" y=\"1\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"2\" y=\"2\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"2\" y=\"3\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"2\" y=\"4\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"2\" y=\"5\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"2\" y=\"6\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"2\" y=\"7\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"3\" y=\"0\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"3\" y=\"1\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"3\" y=\"2\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"3\" y=\"3\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"3\" y=\"4\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"3\" y=\"5\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"3\" y=\"6\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"3\" y=\"7\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"4\" y=\"0\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"4\" y=\"1\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"4\" y=\"2\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"4\" y=\"3\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"4\" y=\"4\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"4\" y=\"5\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"4\" y=\"6\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"4\" y=\"7\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"5\" y=\"0\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"5\" y=\"1\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"5\" y=\"2\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"5\" y=\"3\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"5\" y=\"4\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"5\" y=\"5\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"5\" y=\"6\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"5\" y=\"7\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"6\" y=\"0\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"6\" y=\"1\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"6\" y=\"2\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"6\" y=\"3\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"6\" y=\"4\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"6\" y=\"5\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"6\" y=\"6\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"6\" y=\"7\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"7\" y=\"0\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"7\" y=\"1\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"7\" y=\"2\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"7\" y=\"3\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"7\" y=\"4\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"7\" y=\"5\" width=\"1\" height=\"1\" fill=\"black\" />\n");
   fprintf(out, " <rect x=\"7\" y=\"6\" width=\"1\" height=\"1\" fill=\"white\" />\n");
   fprintf(out, " <rect x=\"7\" y=\"7\" width=\"1\" height=\"1\" fill=\"black\" />\n\n");
   fprintf(out,"<line x1=\"0\" x2=\"8\" y1=\"1\" y2=\"1\" />\n");
   fprintf(out,"<line x1=\"0\" x2=\"8\" y1=\"2\" y2=\"2\" />\n");
   fprintf(out,"<line x1=\"0\" x2=\"8\" y1=\"3\" y2=\"3\" />\n");
   fprintf(out,"<line x1=\"0\" x2=\"8\" y1=\"4\" y2=\"4\" />\n");
   fprintf(out,"<line x1=\"0\" x2=\"8\" y1=\"5\" y2=\"5\" />\n");
   fprintf(out,"<line x1=\"0\" x2=\"8\" y1=\"6\" y2=\"6\" />\n");
   fprintf(out,"<line x1=\"0\" x2=\"8\" y1=\"7\" y2=\"7\" />\n\n");
   fprintf(out," <line y1=\"0\" y2=\"8\" x1=\"1\" x2=\"1\" />\n");
   fprintf(out," <line y1=\"0\" y2=\"8\" x1=\"2\" x2=\"2\" />\n");
   fprintf(out," <line y1=\"0\" y2=\"8\" x1=\"3\" x2=\"3\" />\n");
   fprintf(out," <line y1=\"0\" y2=\"8\" x1=\"4\" x2=\"4\" />\n");
   fprintf(out," <line y1=\"0\" y2=\"8\" x1=\"5\" x2=\"5\" />\n");
   fprintf(out," <line y1=\"0\" y2=\"8\" x1=\"6\" x2=\"6\" />\n");
   fprintf(out," <line y1=\"0\" y2=\"8\" x1=\"7\" x2=\"7\" />\n");
   fprintf(out," </g>\n\n");
   fprintf(out," <g transform=\"translate(0.5,0.5)\">\n\n");
   fprintf(out," <circle cx=\"");
   fprintf(out, "%d", xKoordinaten[0] );
   fprintf(out, "\" cy=\"");
   fprintf(out,"%d", yKoordinaten[0]);
   fprintf(out, "\" r=\"0.1\" stroke=\"none\" fill=\"red\" />\n\n");
   fprintf(out," <text id=\"eins\" x=\"");
   fprintf(out,"%d",xKoordinaten[0]);
   fprintf(out,"\" y=\"");
   fprintf(out,"%d",yKoordinaten[0]);
   fprintf(out,"\" style=\"font-size:0.3px; font-family:Arial\" fill=\"red\" transform=\"translate(-0.3,0.1)\">\n");
   fprintf(out,"S\n");
   fprintf(out,"</text>\n\n");
   if (!geschlossen)
   {
        fprintf(out," <circle cx=\"");
        fprintf(out, "%d", xKoordinaten[brettGroesse-1] );
        fprintf(out, "\" cy=\"");
        fprintf(out,"%d", yKoordinaten[brettGroesse-1]);
        fprintf(out, "\" r=\"0.1\" stroke=\"none\" fill=\"green\" />\n\n");
        fprintf(out," <text id=\"eins\" x=\"");
        fprintf(out,"%d", xKoordinaten[brettGroesse-1]);
        fprintf(out,"\" y=\"");
        fprintf(out,"%d", yKoordinaten[brettGroesse-1]);
        fprintf(out,"\" style=\"font-size:0.3px; font-family:Arial\" fill=\"green\" transform=\"translate(-0.3,0.1)\">\n");
        fprintf(out,"E\n");
        fprintf(out,"</text>\n\n");
   }

   fprintf(out,"<polyline points=\"");
   for(int wert=0; wert < ((*brett).brettGroesse) * ((*brett).brettGroesse);wert++)
   {
        fprintf(out,"%d,%d ", xKoordinaten[wert], yKoordinaten[wert]);
   }
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
