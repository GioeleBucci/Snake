#ifndef SNAKEGAME_STACK_H
#define SNAKEGAME_STACK_H

#include "snake.h"

typedef struct Stack {
    struct Tile *stack;
    int topElem, size;
} Stack;

void stackInit(int size);

void push(struct Tile elem);

struct Tile *pop();

#endif //SNAKEGAME_STACK_H
