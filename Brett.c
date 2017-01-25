#include "Brett.h"

#include <stdlib.h>
#include <stdio.h>

// board: Pointer auf das Board
// boardSize: Boardgroesse
// Dem Board wird zu Beginn die Boardgroesse zugewiesen und es werden so viele Felder reserviert
// Alle Felder werden erstmal auf -1 gesetzt
void board_initialize(Board* board, unsigned int boardSize)
{
    (*board).boardSize = boardSize;
    (*board).data = (int*)malloc(((*board).boardSize * (*board).boardSize)*sizeof(int));

    int boardFields = ((*board).boardSize*(*board).boardSize);
    for(unsigned int i = 0; i < boardFields ; ++i)
    {
        (*board).data[i] = -1;
    }
}

//board: Pointer auf das Board
//Den reservierten Speicher wieder frei geben
void board_destruct(Board* board)
{
    free((*board).data);
}

//board: Pointer auf das Board
// x: X - Koordinate
// Y: Y - Koordinate
//Liefert den Wert an der jeweiligen Position zurueck
int board_getValue(Board* board, unsigned int x, unsigned int y)
{
    return (*board).data[y * (*board).boardSize + x];
}

//board: Pointer auf das Board
// x: X - Koordinate
// Y: Y - Koordinate
//value: Wert des Feldes
//Setzt den Wert an der jeweiligen Position
void board_setValue(Board* board, unsigned int x, unsigned int y, int value)
{
    (*board).data[y * (*board).boardSize + x] = value;
}

//board: Pointer auf das Board
//Gibt das Board aus
void board_print(Board* board)
{
    printf("%s", "|");
    for(unsigned int i = 0; i < (*board).boardSize; ++i)
    {
        printf("%s", "---");
    }
    puts("|");
    for(unsigned int y = 0; y < (*board).boardSize; ++y)
    {
        printf("%s", "|");
        for(unsigned int x = 0; x < (*board).boardSize; ++x)
        {
            int value = board_getValue(board, x, y);
            if(value == -1)
                printf("% 3c", 'x');
            else if(value == (*board).boardSize*(*board).boardSize)
                printf("% 3c", 'X');
            else
                printf("% 3d", value);
        }
        printf("%s", "|\n");
    }
    printf("%s", "|");
    for(unsigned int i = 0; i < (*board).boardSize; ++i)
    {
        printf("%s", "---");
    }
    puts("|");
}

//nimmt das gel�ste Brett mit dem Startwert 0|0 und verschiebt die ganze Werte um den Wert der auf der eigentlichen Startposition steht
void board_rewriteClosed(Board* board, unsigned int rx, unsigned int ry)
{
    // Calculate the new values by applying
    // value = value - offset MOD boardsize^2
    int relative = board_getValue(board, rx, ry); // bei 2|2 = 34
    if(relative == 0) return;
    unsigned int boardSize = (*board).boardSize*(*board).boardSize; // 64
    for(unsigned int x = 0; x < (*board).boardSize; ++x) //Zeile des Brettes
    {
        for(unsigned int y = 0; y < (*board).boardSize; ++y) //Spalte des Brettes
        {
            // C modulo returns negative values, but we want it to wrap around
            // We add boardSize again to make sure it will be positive after modulo
            int newVal = (((board_getValue(board, x, y) - relative) % boardSize) + boardSize) % boardSize; // 34 - 34 = 0 % 64 = 0 + 64 = 64 % 64 = 0
            board_setValue(board, x, y, newVal);
        }
    }
}
