#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>

#include "snake.h"
#include "stack.h"
#include "points2D.h"

#define SNAKE_STARTING_SIZE 3
#define FPS 30
// ------------------------------------------------------------------------------------------------ //

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the current cursor info and save it
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    // Hide the cursor by setting its size to zero
    cursorInfo.dwSize = 100; // Set a large value to hide the cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Scroll the console buffer up to clear the screen.
    if (!ScrollConsoleScreenBuffer(hConsole, &csbi.srWindow, NULL, coordScreen, &csbi.srWindow)) {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);

    // Show the cursor again by restoring its original size
    cursorInfo.dwSize = 1; // Set the cursor size to its original value
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void debugPosition(char *name, Point2D pos) {
    printf("\n%s: %d row %d col", name, pos.yRow, pos.xCol);
}

/// must be called once per frame. Moves the snake in the current direction
void moveSnake(Game *game) {
    for (int i = stack.topElem; i > 0; --i) {
        changePoint2D(&stack.stack[i].position, stack.stack[i - 1].position);
        debugPosition("e", stack.stack[i].position);
    }
    //move head
    Point2D newHeadPos = sumPoint2D(stack.stack[0].position, currentDirection);
    changePoint2D(&stack.stack[0].position, newHeadPos);
    debugPosition("Head", stack.stack[0].position);
}

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

int main() {
    stackInit(100);
    gameInit(&myGame);

    //generates the snake (put into gameInit maybe?)
    Tile segment;
    segment.position.yRow = HEIGHT / 2, segment.position.xCol = WIDTH / 2;
    for (int i = 0; i < SNAKE_STARTING_SIZE; ++i) {
        push(segment);
        segment.position.xCol++;
    }
    system("cls");
    while (1) {
        getInputs();
        Sleep(1000 / FPS);
        clearScreen();
        refresh(*myGame);
        printf("%03d",manhattanDistance());
    }
    refresh(*myGame);
    eatFruit(myGame);
    refresh(*myGame);
    getch();
    //moveSnake(myGame);
    Point2D newHeadPos = sumPoint2D(stack.stack[0].position, currentDirection);
    moveSnakeRec(0, newHeadPos);
    refresh(*myGame);

}
