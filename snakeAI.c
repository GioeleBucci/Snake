#include <stdlib.h>
#include <fvec.h>
#include "snakeAI.h"
#include "points2D.h"
#include "snake.h"

/// Manhattan distance between head and fruit
int manhattanDistance(Point2D head) {
    int y = abs(head.yRow - fruit->position.yRow);
    int x = abs(head.xCol - fruit->position.xCol);
    return x + y;
}

int evalPosition(Game game, Point2D dir){
    Point2D head = stack.stack[0].position;
    Point2D newHeadPos = sumPoint2D(head,dir);

    //check if the head went into a wall
    if(game.tiles[newHeadPos.yRow][newHeadPos.xCol].type == WALL)
        return 30000;

    //check if the head went into a tail segment
    for (int i = 1; i < stack.topElem + 1; ++i) {
        if (isSamePoint2D(newHeadPos, stack.stack[i].position))
            return 30000;
    }
    return manhattanDistance(head);
}

enum {
    UP, DOWN, LEFT, RIGHT
};

Point2D directions[4] = {{-1, 0},
                         {1,  0},
                         {0,  -1},
                         {0,  1}};

Point2D bestMove;

int Search(int depth, Game game, Point2D dir) {
    if (depth == 0)
        return evalPosition(game,dir);
    int best = 30000;
    for (int i = 0; i < 4; ++i) {
        dir = directions[i];
        //make move
        int current = Search(depth - 1, game, dir);
        if (current < best){
            best = current;
            bestMove = dir;
        }
    }
    return best;
}

