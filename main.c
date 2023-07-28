#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include "snake.h"
#include "stack.h"

Game *myGame;

// ------------------------------------------------------------------------------------------------ //

void debugPosition(char *name, Point2D pos) {
    printf("\n%s: %d row %d col", name, pos.yRow, pos.xCol);
}

void changePosition(Point2D *old, Point2D new) {
    old->xCol = new.xCol;
    old->yRow = new.yRow;
}

Point2D sumPoint2D(Point2D a, Point2D b) {
    Point2D res;
    res.xCol = a.xCol + b.xCol;
    res.yRow = a.yRow + b.yRow;
    return res;
}

/// must be called once per frame. Moves the snake in the current direction
void moveSnake(Game *game) {
    for (int i = stack.topElem; i > 0; --i) {
        changePosition(&stack.stack[i].position, stack.stack[i - 1].position);
        debugPosition("e", stack.stack[i].position);
    }
    //move head
    Point2D newHeadPos = sumPoint2D(stack.stack[0].position, currentDirection);
    changePosition(&stack.stack[0].position, newHeadPos);
    debugPosition("Head", stack.stack[0].position);
}

void moveSnakeRec(int index, Point2D newHeadPos){
    if(index == stack.topElem + 1)
        return;
    moveSnakeRec(index+1,stack.stack[index].position);
    changePosition(&stack.stack[index].position,newHeadPos);
}


int main() {
    stackInit(5);
    gameInit(&myGame);

    Tile tile1;
    tile1.position.yRow = 1, tile1.position.xCol = 1;
    for (int i = 0; i < 5; ++i) {
        push(tile1, myGame);
        tile1.position.xCol++;
    }
    generateFruit(myGame);
    refresh(*myGame);
    eatFruit(myGame);
    getch();
    //moveSnake(myGame);
    Point2D newHeadPos = sumPoint2D(stack.stack[0].position, currentDirection);
    moveSnakeRec(0,newHeadPos);
    exit(1);
    refresh(*myGame);
    int input = getch();
    int dir = -1;
    if (input == 'w') dir = UP;
    if (input == 'a') dir = LEFT;
    if (input == 's') dir = DOWN;
    if (input == 'd') dir = RIGHT;
    //if (dir != -1) changeDirection(dir,myGame);
}
