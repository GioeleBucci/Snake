#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include "snake.h"

Game *myGame;
Stack stack;

// ------------------------------------------------------------------------------------------------ //

void stackInit(int size);

void push(struct Tile elem, Game *game);

Tile *pop(Game *game);

int main() {
    stackInit(5);
    gameInit(&myGame);

    Tile tile1;
    tile1.position.yRow = 1, tile1.position.xCol = 1;
    for (int i = 0; i < 5; ++i) {
        push(tile1, myGame);
        tile1.position.yRow++;
    }
    generateFruit(myGame);
    refresh(myGame);
    //eatFruit(myGame);

    int input = getch();
    int dir = -1;
    if (input == 'w') dir = UP;
    if (input == 'a') dir = LEFT;
    if (input == 's') dir = DOWN;
    if (input == 'd') dir = RIGHT;
    if (dir != -1) changeDirection(dir,myGame);
}

void stackInit(int size) {
    stack.stack = malloc(sizeof(struct Tile) * size);
    assert(stack.stack != NULL);
    stack.size = size;
    stack.topElem = -1;
}

/// Handles snake segments.
/// If the stack is empty the first segment pushed will become the head, tail otherwise
void push(struct Tile elem, Game *game) {

    if (stack.topElem == stack.size - 1) {
        stack.stack = realloc(stack.stack, sizeof(struct Tile) * stack.size + 10);
        assert(stack.stack != NULL);
        stack.size = stack.size + 1;
    }

    //assign correct body segment
    elem.type = stack.topElem == -1 ? HEAD : TAIL;
    elem.render = stack.topElem == -1 ? '@' : 'O';

    //add to game scene so it can be rendered
    game->tiles[elem.position.xCol][elem.position.yRow].render = elem.render;
    game->tiles[elem.position.xCol][elem.position.yRow].type = elem.type;

    //if head was generated add it to snakeHead field
    if (stack.topElem == -1) game->snakeHead = &elem;

    stack.topElem++;
    stack.stack[stack.topElem] = elem;
}

/// Returns top element or null if stack is empty
Tile *pop(Game *game) {

    if (stack.topElem == -1) return NULL;
    Tile *elem = &(stack.stack[stack.topElem]);

    //put air where the tile was
    changeTileType(&game->tiles[elem->position.xCol][elem->position.yRow],AIR);

    stack.topElem--;
    return elem;
}