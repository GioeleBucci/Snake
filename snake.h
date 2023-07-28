#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include "points2D.h"
#include "stack.h"

#define WIDTH 40
#define HEIGHT 20

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
} Game;

extern struct Point2D currentDirection; // where the snake is currently going
extern Stack stack;
extern Game *myGame;
extern Tile *fruit;
extern int score;

void printScore();

void moveSnakeRec(int index, struct Point2D newHeadPos);

void changeTilePosition(Tile *tile, int yRow, int xCol);

void changeTileType(Tile *tile, int newType);

void refresh(Game game);

void gameInit(Game **gamePtr);

void generateFruit(Game *game);

bool isEatingFruit();

/// Deletes the fruit and increases the snake lenght by 1.
void eatFruit(Game *game);

#endif //SNAKEGAME_SNAKE_H
