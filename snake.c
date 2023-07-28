#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "snake.h"

Point2D currentDirection = {-1,0}; // where the snake is currently going

void refresh(const Game *game) {
    system("cls");
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%c", game->tiles[i][j].render);
        }
        printf("\n");
    }
}

void gameInit(Game **gamePtr) {
    *gamePtr = malloc(sizeof(Game));
    Game *game = *gamePtr; //just renaming it for code clarity
    assert(game != NULL);
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            changeTileType(&game->tiles[i][j],WALL);
            changeTilePosition(&game->tiles[i][j],i,j);
        }
    }
    for (int i = 1; i < HEIGHT - 1; ++i)
        for (int j = 1; j < WIDTH - 1; ++j)
            changeTileType(&game->tiles[i][j],AIR);
}

void generateFruit(Game *game) {

    if (game->fruit != NULL) return;

    Tile *fruit = malloc(sizeof(Tile));
    assert(fruit != NULL);

    game->fruit = fruit;
    srand(time(NULL));

    int xGen, yGen;
    do {
        xGen = rand() % WIDTH;
        yGen = rand() % HEIGHT;
    } while (game->tiles[yGen][xGen].type != AIR);

    changeTilePosition(fruit,yGen,xGen);
    changeTileType(fruit,FRUIT);

    int x = fruit->position.xCol, y = fruit->position.yRow;
    changeTileType(&game->tiles[y][x],FRUIT);
}

void eatFruit(Game *game) {

    Tile *fruit = game->fruit;
    assert(fruit != NULL);

    int y = fruit->position.yRow, x = fruit->position.xCol;
    changeTileType(&game->tiles[y][x],AIR);

    game->fruit = NULL;
    free(fruit);
}

void changeDirection(Point2D newDir, Game *game) {
    if (newDir.xCol == currentDirection.xCol && newDir.yRow == currentDirection.yRow) return;
    else currentDirection = newDir;
}

void changeTilePosition(Tile *tile, int yRow, int xCol) {
    tile->position.yRow = yRow;
    tile->position.xCol = xCol;
}

void changeTileType(Tile *tile, int newType) {
    tile->type = newType;
    if (newType == AIR) tile->render = ' ';
    if (newType == WALL) tile->render = 219;
    if (newType == HEAD) tile->render = '@';
    if (newType == TAIL) tile->render = 'O';
    if (newType == FRUIT) tile->render = 'F';
}
