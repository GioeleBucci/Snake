#ifndef SNAKEGAME_STACK_H
#define SNAKEGAME_STACK_H

typedef struct Stack {
    struct Tile *stack; //stack[0] is the snake's head
    int topElem, size;
} Stack;

void stackInit(int size);

void push(struct Tile elem);

struct Tile *pop();

#endif //SNAKEGAME_STACK_H
