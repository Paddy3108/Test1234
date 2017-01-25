#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include <stdbool.h>

/*
 * boardSize: Groesse des Boards
 * x : Start X - Koordinate
 * y : Start Y - Koordinate
 * closedTour: Geschlosser oder offener Weg
 * Versucht das Springerproblem mit den gegeben Variablen zu loesen
 */
void knightsTour(unsigned int boardSize, unsigned int x, unsigned int y, bool closedTour);

#endif // ALGORITHM_H_INCLUDED
