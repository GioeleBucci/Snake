#ifndef SNAKEGAME_POINTS2D_H
#define SNAKEGAME_POINTS2D_H

typedef struct Point2D {
    int yRow, xCol;
} Point2D;

Point2D sumPoint2D(Point2D a, Point2D b);

Point2D newPoint2D(int y, int x);

void changePoint2D(Point2D *old, Point2D new);

#endif
