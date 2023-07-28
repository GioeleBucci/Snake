#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "snake.h"

#define WIDTH 30
#define HEIGHT 5

enum type {
    AIR, WALL, HEAD, TAIL, FRUIT
};

enum direction {
    UP, DOWN, LEFT, RIGHT
};

typedef struct Point2D {
    int yRow, xCol;
} Point2D;

typedef struct Tile {
    Point2D position;
    unsigned char render;
    int type;
} Tile;

typedef struct Game {
    Tile tiles[HEIGHT][WIDTH];
    Tile *fruit;
} Game;

typedef struct Stack {
    struct Tile *stack;
    int topElem, size;
} Stack;

extern Point2D currentDirection; // where the snake is currently going
extern Stack stack;

void changeTilePosition(Tile *tile, int yRow, int xCol);

void changeTileType(Tile *tile, int newType);

void refresh(Game game);

void gameInit(Game **game);

void generateFruit(Game *game);

/// Deletes the fruit and increases the snake lenght by 1.
void eatFruit(Game *game);

void changeDirection(Point2D newDir, Game *game);

#endif //SNAKEGAME_SNAKE_H
