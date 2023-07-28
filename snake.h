#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

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
    Tile *snakeHead;
} Game;

typedef struct Stack {
    struct Tile *stack;
    int topElem, size;
} Stack;

extern Point2D currentDirection; // where the snake is currently going

void changeTilePosition(Tile *tile, int yRow, int xCol);

void changeTileType(Tile *tile, int newType);

void refresh(const Game *game);

void gameInit(Game **game);

void generateFruit(Game *game);

void eatFruit(Game *game);

void changeDirection(Point2D newDir, Game *game);

#endif //SNAKEGAME_SNAKE_H
