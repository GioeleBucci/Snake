#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#include "snake.h"
#include "stack.h"
#include "points2D.h"
#include "snakeAI.h"

#define FPS 30

// ------------------------------------------------------------------------------------------------ //

Point2D getInputs() {
    int input;
    if (kbhit())
        input = tolower(getch()); //kbhit() is a non-blocking input function
    Point2D dir = currentDirection;
    if (input == 'w') dir = newPoint2D(-1, 0);
    if (input == 'a') dir = newPoint2D(0, -1);
    if (input == 's') dir = newPoint2D(1, 0);
    if (input == 'd') dir = newPoint2D(0, 1);

    //avoid changing to opposite direction
    if (currentDirection.xCol == -dir.xCol && currentDirection.yRow == -dir.yRow)
        return currentDirection;

    currentDirection = dir;
}

/// returns 1 if the computer needs to play
int startingScreen() {
    unsigned char screen[HEIGHT][WIDTH] = {};
    for (int i = 0; i < HEIGHT; ++i)
        for (int j = 0; j < WIDTH; ++j)
            screen[i][j] = 219;
    for (int i = 1; i < HEIGHT - 1; ++i)
        for (int j = 1; j < WIDTH - 1; ++j)
            screen[i][j] = ' ';
    char *line1 = "Snake Game by Gioele Bucci";
    char *line2 = "Press any key to start";
    char *line3 = "or";
    char *line4 = "Press 1 to make the computer play";

    //write line 1
    for (int i = 0; i < strlen(line1); ++i)
        screen[HEIGHT / 3][(WIDTH - strlen(line1)) / 2 + i] = line1[i];

    //write line 2
    for (int i = 0; i < strlen(line2); ++i)
        screen[2 * HEIGHT / 3 - 1][(WIDTH - strlen(line2)) / 2 + i] = line2[i];

    //write line 3
    for (int i = 0; i < strlen(line3); ++i)
        screen[2 * HEIGHT / 3 ][(WIDTH - strlen(line3)) / 2 + i] = line3[i];

    //write line 4
    for (int i = 0; i < strlen(line4); ++i)
        screen[2 * HEIGHT / 3 + 1][(WIDTH - strlen(line4)) / 2 + i] = line4[i];

    //write the full screen
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%c",screen[i][j]);
        }
        printf("\n");
    }
    return getch();
}

int main() {

    system("cls");

    stackInit(100, &stack);
    gameInit(&myGame);

    clock_t t;

    // computer plays
    if(startingScreen() == '1'){
        while (1) {
            t = clock();
            search(1, *myGame, currentDirection);
            currentDirection = bestMove;
            clearScreen();
            refresh(*myGame);
            t = clock() - t;
            double elapsedTime = ((double)t)/CLOCKS_PER_SEC * 1000;
            Sleep((1000 - (int)elapsedTime) / FPS);
        }
    }

    // human plays
    while (1) {
        t = clock();
        getInputs();
        clearScreen();
        refresh(*myGame);
        t = clock() - t;
        double elapsedTime = ((double)t)/CLOCKS_PER_SEC * 1000;
        Sleep((1000 - (int)elapsedTime) / FPS);
    }
}