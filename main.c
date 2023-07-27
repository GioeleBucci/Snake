#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

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

Stack stack;

int currentDirection = LEFT; // where the snake is currently going

// ------------------------------------------------------------------------------------------------ //

void changeTilePosition(Tile *tile, int yRow, int xCol);

void changeTileType(Tile *tile, int newType);

void stackInit(int size) {
    stack.stack = malloc(sizeof(struct Tile) * size);
    assert(stack.stack != NULL);
    stack.size = size;
    stack.topElem = -1;
}

/// Handles snake segments.
/// If the stack is empty the first segment pushed will become the head, tail otherwise
void push(struct Tile elem, Game *game) {

    if (stack.topElem == stack.size - 1) {
        stack.stack = realloc(stack.stack, sizeof(struct Tile) * stack.size + 10);
        assert(stack.stack != NULL);
        stack.size = stack.size + 1;
    }

    //assign correct body segment
    elem.type = stack.topElem == -1 ? HEAD : TAIL;
    elem.render = stack.topElem == -1 ? '@' : 'O';

    //add to game scene so it can be rendered
    game->tiles[elem.position.xCol][elem.position.yRow].render = elem.render;
    game->tiles[elem.position.xCol][elem.position.yRow].type = elem.type;

    //if head was generated add it to snakeHead field
    if (stack.topElem == -1) game->snakeHead = &elem;

    stack.topElem++;
    stack.stack[stack.topElem] = elem;
}

/// Returns top element or null if stack is empty
Tile *pop(Game *game) {

    if (stack.topElem == -1) return NULL;
    Tile *elem = &(stack.stack[stack.topElem]);

    //put air where the tile was
    changeTileType(&game->tiles[elem->position.xCol][elem->position.yRow],AIR);

    stack.topElem--;
    return elem;
}

void refresh(const Game *game) {
    system("cls");
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%c", game->tiles[i][j].render);
        }
        printf("\n");
    }
}

void gameInit(Game *game) {
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

void changeDirection(int newDir, Game *game) {
    if (newDir == currentDirection) return;
    else currentDirection = newDir;
}

void update(Game *game) {
    switch (currentDirection) {
        case UP:
            break;
        case DOWN:
            break;
        case LEFT:
            break;
        case RIGHT:
            break;
    }
}

int main() {
    stackInit(5);

    Game *myGame = malloc(sizeof(Game));
    gameInit(myGame);

    Tile tile1;
    tile1.position.yRow = 1, tile1.position.xCol = 1;
    for (int i = 0; i < 5; ++i) {
        push(tile1, myGame);
        tile1.position.yRow++;
    }
    generateFruit(myGame);
    refresh(myGame);
    //eatFruit(myGame);

    int input; //= getch();
    int dir = -1;
    if (input == 'w') dir = UP;
    if (input == 'a') dir = LEFT;
    if (input == 's') dir = DOWN;
    if (input == 'd') dir = RIGHT;
    if (dir != -1) changeDirection(dir,myGame);

    changeTilePosition(&myGame->tiles[1][1],1,2);
    refresh(myGame);
    refresh(myGame);
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

