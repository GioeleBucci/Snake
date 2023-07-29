cmake_minimum_required(VERSION 3.23)
project(SnakeGame C)

set(CMAKE_C_STANDARD 17)

add_executable(SnakeGame main.c snake.c snake.h stack.c stack.h points2D.c points2D.h snakeAI.c snakeAI.h)
