#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Algorithmus.h"
/*
 * Funktion:
 * Startmenue, ueberprueft, welcher Aufgabentyp geloest werden soll.
 *
 * Frei waehlbare Optionen:
 * Anschliessend wird die Brettgroesse eingelesen und
 * ueberprueft ob die Brettgroesse im Gueltigkeitsbereich liegt.
 * Danach wird die Startposition eingelesen und
 * ueberprueft ob sie im Gueltigkeitsbereich liegt.
 * Anschliessend versucht das Programm das Springerproblem zu loesen.
 *
 * Zufaellige Optionen:
 * Das Programm erzeugt zwei Zufallszahlen, die die Startposition angeben.
 * Anschliessend versucht das Programm fuer die Brettgroesse 8x8 das Springerproblem zu loesen.
 *
 *
 * Rueckgabewert: void
 */
void start() {
    printf("=== Springerproblem ===\n");
    printf("1. Offener Pfad (frei waehlbar)\n");
    printf("2. Geschlossener Pfad (frei waehlbar)\n");
    printf("3. Offener Pfad (Brettgroesse: 8x8, Startpunkt: Zufaellig)\n");
    printf("4. Geschlossener Pfad (Brettgroesse: 8x8, Startpunkt: Zufaellig)\n> ");

    int wahl = 0;
    bool geschlossen;
    int brettGroesse = 0;
    int x = -1 ,y = -1;
    scanf("%d", &wahl);

    switch (wahl) {
        case 1:
        case 2:
            if(wahl == 1) {
                geschlossen = false;
            }
            else if (wahl == 2) {
                geschlossen = true;
            }
                printf("(Ab einer Brettgroesse > 8 kann, je nach Startposition, die Berechnung sehr lange dauern. \n Es wird kein Ergebnis garantiert)\n");
                printf("Eingabe Brettgroesse (5 bis 70):\n");
                while (brettGroesse<5 || brettGroesse > 70) { //prueft ob die eingelesenen Werte korrekt sind
                    while((scanf("%d", &brettGroesse))!= 1) { //prueft ob Zahlen eingelesen wurden
                        fflush(stdin); // loescht Eingabepuffer, um die Variablen neue Werte zu zu weisen.
                        printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                    }
                    if(brettGroesse<5 || brettGroesse > 70) printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                }
                fflush(stdin); // loescht Eingabepuffer, um die Variablen neue Werte zu zu weisen.
                printf("%s", "Koordinaten der linken oberen Ecke sind: 1 1\nBitte Startfeld im Format: %d %d eingeben\n> ");

                while (x<1 || x>brettGroesse || y<1 || y>brettGroesse) { //prueft ob die eingebene Position moeglich ist

                    while ((scanf("%d %d", &x, &y)) != 2) {//prueft ob Zahlen eingelesen wurden
                        fflush(stdin); // loescht Eingabepuffer, um die Variablen neue Werte zu zu weisen.
                        printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                    }
                    if((x<1 || x>brettGroesse || y<1 || y>brettGroesse)) printf("Falsche Eingabe. Bitte korrigieren Sie ihre Eingabe.\n> ");
                }
                springen(brettGroesse, --x, --y, geschlossen);
                break;
        case 3:
        case 4:
                if (wahl == 4) geschlossen = true;
                else geschlossen = false;
                srand(time (NULL)); // wird benoetigt, um abhaengig von der Zeit eine Zufallszahl zu erstellen, ohne das => immer die gleiche Zufallszahl
                x = rand() % 8 +1; //erzeugt Zufalszahl
                y = rand() % 8 +1;
                printf("%s %s (%d|%d)\n", geschlossen ? "Geschlossener" : "Offener", "Weg", x, y);
                springen(8, --x, --y, geschlossen);
                break;

        default: printf("Falsche Eingabe.");
                    break;
    }
}

int main() {
    start();
    return 0;
}
