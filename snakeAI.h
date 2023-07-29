#ifndef SNAKEGAME_SNAKEAI_H
#define SNAKEGAME_SNAKEAI_H

#include "snake.h"

extern Point2D bestMove;

/// Manhattan distance between head and fruit
int manhattanDistance(struct Point2D head);

int evalPosition(Game game, Point2D dir);

int search(int depth, Game game, Point2D dir);

#endif //SNAKEGAME_SNAKEAI_H
