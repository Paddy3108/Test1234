#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Algorithmus.h"
/*
 * Funktion:
 * Startmenue, ueberprueft, welcher Aufgabentyp geloest werden soll.
 *
 * Frei waehlbare Optionen:
 * Anschlie�end wird die Brettgroesse eingelesen und
 * ueberprueft ob die Brettgroesse im Gueltigkeitsbereich liegt.
 * Danach wird die Startposition eingelesen und
 * ueberprueft ob sie im Gueltigkeitsbereich liegt.
 * Anschlie�end versucht das Programm das Springerproblem zu loesen.
 *
 * Zufaellige Optionen:
 * Das Programm erzeugt zwei Zufallszahlen, die die Startposition angeben.
* Anschlie�end versucht das Programm fuer die Brettgroesse 8x8 das Springerproblem zu loesen.
 *
 *
 * R�ckgabewert: void
 */
void start()
{
    printf("=== Springerproblem ===\n");
    printf("1. Offener Pfad (frei waehlbar)\n");
    printf("2. Geschlossener Pfad (frei waehlbar)\n");
    printf("3. Offener Pfad (Zufaellig)\n");
    printf("4. Geschlossener Pfad (Zufaellig)\n> ");

    int wahl = 0;
    bool geschlossen;
    int brettGroesse = 0;
    int x = -1 ,y = -1;
    scanf("%d", &wahl);

    switch (wahl)
    {
        case 1:
        case 2:
                if (wahl == 2) geschlossen = true;
                else geschlossen = false;

                printf("Groesse des Brettes (5 bis 70): ");
                while (brettGroesse<5 || brettGroesse > 70) //prueft ob die eingelesenen Werte korrekt sind
                {
                    while((scanf("%d", &brettGroesse))!= 1) //prueft ob Zahlen eingelesen wurden
                    {
                        fflush(stdin); // loescht Eingabepuffer, um die Variablen neue Werte zu zu weisen.
                        printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                    }
                    if(brettGroesse<5 || brettGroesse > 70) printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                }
                printf("%s", "Startfeld. Format: %d %d\nLinke obere Ecke: 1 1\n> ");

                while (x<1 || x>brettGroesse || y<1 || y>brettGroesse) //prueft ob die eingebene Position moeglich ist
                {
                    while ((scanf("%d %d", &x, &y)) != 2) //prueft ob Zahlen eingelesen wurden
                    {
                        fflush(stdin); // loescht Eingabepuffer, um die Variablen neue Werte zu zu weisen.
                        printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                    }
                    if((x<1 || x>brettGroesse || y<1 || y>brettGroesse)) printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                }
                knightsTour(brettGroesse, --x, --y, geschlossen);
                break;
        case 3:
        case 4:
                if (wahl == 4) geschlossen = true;
                else geschlossen = false;
                srand(time (NULL)); // wird benoetigt, um abhaengig von der Zeit eine Zufallszahl zu erstellen, ohne das => immer die gleiche Zufallszahl
                x = rand() % 8; //erzeugt Zufalszahl
                y = rand() % 8;
                printf("%s %s (%d|%d)\n", geschlossen ? "Geschlossener" : "Offener", "Weg", x, y);
                knightsTour(8, x, y, geschlossen);
                break;

        default: printf("Falsche Eingabe.");
                    break;
    }
}

int main()
{
    start();
    return 0;
}
