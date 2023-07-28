#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include "points2D.h"
#include "stack.h"

#define WIDTH 30
#define HEIGHT 5

enum type {
    AIR, WALL, HEAD, TAIL, FRUIT
};

typedef struct Tile {
    struct Point2D position;
    unsigned char render;
    int type;
} Tile;

typedef struct Game {
    Tile tiles[HEIGHT][WIDTH];
    Tile *fruit;
} Game;

extern struct Point2D currentDirection; // where the snake is currently going
extern Stack stack;
extern Game *myGame;

void moveSnakeRec(int index, struct Point2D newHeadPos);

void changeTilePosition(Tile *tile, int yRow, int xCol);

void changeTileType(Tile *tile, int newType);

void refresh(Game game);

void gameInit(Game **game);

void generateFruit(Game *game);

/// Deletes the fruit and increases the snake lenght by 1.
void eatFruit(Game *game);

#endif //SNAKEGAME_SNAKE_H
