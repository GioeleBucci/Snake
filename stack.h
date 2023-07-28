#ifndef SNAKEGAME_STACK_H
#define SNAKEGAME_STACK_H

#include "snake.h"

void stackInit(int size);

void push(struct Tile elem, Game *game);

Tile *pop(Game *game);

#endif //SNAKEGAME_STACK_H
