#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <ctype.h>

#include "snake.h"
#include "stack.h"
#include "points2D.h"

#define SNAKE_STARTING_SIZE 3

// ------------------------------------------------------------------------------------------------ //

void debugPosition(char *name, Point2D pos) {
    printf("\n%s: %d row %d col", name, pos.yRow, pos.xCol);
}

/// must be called once per frame. Moves the snake in the current direction
void moveSnake(Game *game) {
    for (int i = stack.topElem; i > 0; --i) {
        changePoint2D(&stack.stack[i].position, stack.stack[i - 1].position);
        debugPosition("e", stack.stack[i].position);
    }
    //move head
    Point2D newHeadPos = sumPoint2D(stack.stack[0].position, currentDirection);
    changePoint2D(&stack.stack[0].position, newHeadPos);
    debugPosition("Head", stack.stack[0].position);
}

Point2D getInputs() {
    //the program shouldn't wait for input instead it should continue
    int input = tolower(getch());
    Point2D dir = currentDirection;
    if (input == 'w') dir = newPoint2D(-1, 0);
    if (input == 'a') dir = newPoint2D(0, -1);
    if (input == 's') dir = newPoint2D(1, 0);
    if (input == 'd') dir = newPoint2D(0, 1);
    currentDirection = dir;
}

int main() {
    stackInit(5);
    gameInit(&myGame);

    //generates the snake (put into gameInit maybe?)
    Tile segment;
    segment.position.yRow = HEIGHT / 2, segment.position.xCol = WIDTH / 2;
    for (int i = 0; i < SNAKE_STARTING_SIZE; ++i) {
        push(segment);
        segment.position.xCol++;
    }

    while (1) {
        getInputs();
        refresh(*myGame);
    }
    refresh(*myGame);
    eatFruit(myGame);
    refresh(*myGame);
    getch();
    //moveSnake(myGame);
    Point2D newHeadPos = sumPoint2D(stack.stack[0].position, currentDirection);
    moveSnakeRec(0, newHeadPos);
    refresh(*myGame);

}
