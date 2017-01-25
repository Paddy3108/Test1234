#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

// Definiert ein Struct "Board" mit den Variablen boardSize und einem int Pointer
typedef struct Board
{
    unsigned int boardSize;
    int* data;
} Board;

/*
 * board: Pointer auf das Board
 * boardSize: Boardgroesse
 * Initialisiert das Board mit den zwei Variablen
 */
void board_initialize(Board* board, unsigned int boardSize);

/*
 * board: Pointer auf das Board
 * Gibt zuvor reservierten Speicher wieder frei
 */
void board_destruct(Board* board);

/*
 * board: Pointer auf das Board
 * X : X - Koordinate
 * Y : Y - Koordinate
 * Gibt den Wert von dem Board an der Stelle x und y zurück
 */
int board_getValue(Board* board, unsigned int x, unsigned int y);

/*
 * board: Pointer auf das Board
 * X : X - Koordinate
 * Y : Y - Koordinate
 * value: Wert des Feldes
 * Setzt den Wert von dem Board an der Stelle x und y zurück
 */
void board_setValue(Board* board, unsigned int x, unsigned int y, int value);

/*
 * board: Pointer auf das Board
 * Gibt das Board aus
 */
void board_print(Board* board);

/*
 * Rewrites a closed board at 0|0 to a board at x|y
 */
void board_rewriteClosed(Board* board, unsigned int x, unsigned int y);

#endif // BOARD_H_INCLUDED
