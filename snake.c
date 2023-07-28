#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

#include "snake.h"
#include "points2D.h"
#include "stack.h"

struct Point2D currentDirection = {0, -1}; // where the snake is currently going
Stack stack;
Game *myGame;
Tile *fruit;

void moveSnakeRec(int index, Point2D newHeadPos) {
    if (index == stack.topElem + 1) {
        return;
    }
    moveSnakeRec(index + 1, stack.stack[index].position);
    changePoint2D(&stack.stack[index].position, newHeadPos);
}

bool isGameOver(Game *game) {

    //check if the head went into a wall
    Point2D snakeHead = stack.stack[0].position;
    if (game->tiles[snakeHead.yRow][snakeHead.xCol].type == WALL)
        return true;

    //check if the head went into a tail segment
    for (int i = 1; i < stack.topElem + 1; ++i) {
        if (isSamePoint2D(snakeHead, stack.stack[i].position))
            return true;
    }
    return false;
}


void refresh(Game game) {
    system("cls");

    if(isGameOver(&game)){
        puts("Game Over");
        exit(EXIT_SUCCESS);
    }

    //check fruit
    if(isEatingFruit())
        eatFruit(myGame);

    //move the snake in the current direction
    Point2D newHeadPos = sumPoint2D(stack.stack[0].position, currentDirection);
    moveSnakeRec(0, newHeadPos);

    for (int i = 0; i < stack.topElem + 1; ++i) {
        int y = stack.stack[i].position.yRow;
        int x = stack.stack[i].position.xCol;
        changeTileType(&game.tiles[y][x], stack.stack[i].type);
    }

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%c", game.tiles[i][j].render);
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
            changeTileType(&game->tiles[i][j], WALL);
            changeTilePosition(&game->tiles[i][j], i, j);
        }
    }
    for (int i = 1; i < HEIGHT - 1; ++i)
        for (int j = 1; j < WIDTH - 1; ++j)
            changeTileType(&game->tiles[i][j], AIR);
    fruit = malloc(sizeof(Tile));
    assert(fruit != NULL);
    generateFruit(game);
}

void generateFruit(Game *game) {
    // Get the current time
    time_t currentTime;
    time(&currentTime);

    // Seed the random number generator with the current time
    srand((unsigned int)currentTime);

    int xGen, yGen;
    do {
        xGen = rand() % WIDTH;
        yGen = rand() % HEIGHT;
    } while (game->tiles[yGen][xGen].type != AIR);

    changeTilePosition(fruit, yGen, xGen);
    changeTileType(fruit, FRUIT);

    changeTileType(&game->tiles[yGen][xGen],FRUIT);
}

void eatFruit(Game *game) {

    int y = fruit->position.yRow, x = fruit->position.xCol;
    changeTileType(&game->tiles[y][x], AIR);

    generateFruit(game);

    // Create a new snake segment to increase its lenght
    Tile *newSnakeSegment = malloc(sizeof(Tile));
    assert(newSnakeSegment != NULL);
    newSnakeSegment->position = stack.stack[stack.topElem].position;
    newSnakeSegment->position.xCol -= currentDirection.xCol;
    newSnakeSegment->position.yRow -= currentDirection.yRow;
    push(*newSnakeSegment);
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

bool isEatingFruit() {
    if(isSamePoint2D(fruit->position,stack.stack[0].position))
        return true;
    return false;
}
