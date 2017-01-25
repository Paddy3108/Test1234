#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Algorithmus.h"

int main()
{
    printf("=== Springerproblem ===\n");
    printf("%s", "1. Offener Pfad (frei waehlbar)\n");
    printf("%s", "2. Geschlossener Pfad (frei waehlbar)\n");
    printf("%s", "3. Offener Pfad (Zufaellig)\n");
    printf("%s", "4. Geschlossener Pfad (Zufaellig)\n> ");

    int wahl = 0;
    bool geschlossen;
    int groesse = 0;
    int x = -1 ,y = -1;
    scanf("%d", &wahl);

    switch (wahl)
    {
        case 1:
        case 2:
                if (wahl == 2) geschlossen = true;
                else geschlossen = false;

                printf("Groesse des Brettes (5 bis 13): ");
                while (groesse<5 || groesse > 13)
                {
                    while((scanf("%d", &groesse))!= 1)
                    {
                        fflush(stdin); // loescht Eingabepuffer, um die Variablen neue Werte zu zu weisen.
                        printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                    }
                    if(groesse<5 || groesse > 13) printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                }
                printf("%s", "Startfeld. Format: %d %d\nLinke obere Ecke: 0 0\n> ");

                while (x<0 || x>groesse-1 || y<0 || y>groesse-1)
                {
                    while ((scanf("%d %d", &x, &y)) != 2)
                    {
                        fflush(stdin); // loescht Eingabepuffer, um die Variablen neue Werte zu zu weisen.
                        printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                    }
                    if((x<0 || x>groesse-1 || y<0 || y>groesse-1)) printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                }
                knightsTour(groesse, x, y, geschlossen);
                break;
        case 3:
        case 4:
                if (wahl == 4) geschlossen = true;
                else geschlossen = false;
                time_t t;
                time(&t);
                srand((unsigned int)t); // wird benoetigt, um abhaengig von der Zeit eine Zufallszahl zu erstellen, ohne das => immer die gleiche Zufallszahl
                x = rand() % 8; //erzeugt Zufalszahl
                y = rand() % 8;
                printf("%s %s (%d|%d)\n", geschlossen ? "Geschlossener" : "Offener", "Weg", x, y);
                knightsTour(8, x, y, geschlossen);
                break;

        default: printf("Falsche Eingabe.");
                    break;
    }
    return 0;
}
