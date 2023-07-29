#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "snakeAI.h"
#include "points2D.h"
#include "snake.h"

Point2D bestMove;

Point2D directions[4] = {{-1, 0},  //up
                         {1,  0},  //down
                         {0,  -1}, //left
                         {0,  1}}; //right

/// Manhattan distance between head and fruit
int manhattanDistance(Point2D head) {
    int y = abs(head.yRow - fruit->position.yRow);
    int x = abs(head.xCol - fruit->position.xCol);
    return x + y;
}

void moveSnakeAI(int index, Point2D newHeadPos, Stack *newStack) {
    if (index == newStack->topElem + 1) {
        return;
    }
    moveSnakeAI(index + 1, newStack->stack[index].position, newStack);
    changePoint2D(&newStack->stack[index].position, newHeadPos);
}

int evalPosition(Game game, Point2D dir) {

    int returnValue = 0;

    Stack newStack;
    stackInit(100, &newStack);
    for (int i = 0; i <= stack.topElem; ++i) {
        push(stack.stack[i],&newStack);
    }

    //printf("\nDebug: old snake head: %d %d", stack.stack[0].position.yRow, stack.stack[0].position.xCol);
    Point2D newHeadPos = sumPoint2D(newStack.stack[0].position, dir);
    //printf("\nDebug: new snake head: %d %d\n", newHeadPos.yRow, newHeadPos.xCol);
    moveSnakeAI(0, newHeadPos, &newStack);
    //check if the head went into a wall
    if (game.tiles[newHeadPos.yRow][newHeadPos.xCol].type == WALL)
        returnValue = 30000;

    //check if the head went into a tail segment
    for (int i = 1; i < newStack.topElem + 1; ++i) {
        if (isSamePoint2D(newHeadPos, newStack.stack[i].position))
            returnValue = 30000;
    }

    free(newStack.stack);
    return returnValue + manhattanDistance(newHeadPos);
}

int search(int depth, Game game, Point2D dir) {
    if (depth == 0) {
        //printf("%d\n", evalPosition(game, dir));
        return evalPosition(game, dir);
    }
    int best = 30000;
    for (int i = 0; i < 4; ++i) {
        //printf("\n%d %d",dir.yRow,dir.xCol);

        //make move
        int current = search(depth - 1, game, directions[i]);
        if (current < best) {
            best = current;
            bestMove = directions[i];
            //printf("\nBest move is %d %d (score %d)\n", bestMove.yRow, bestMove.xCol, current);
        }
    }
    return best;
}

