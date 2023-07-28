#include "points2D.h"

Point2D sumPoint2D(Point2D a, Point2D b) {
    Point2D res;
    res.xCol = a.xCol + b.xCol;
    res.yRow = a.yRow + b.yRow;
    return res;
}

Point2D newPoint2D(int y, int x) {
    Point2D new;
    new.xCol = x, new.yRow = y;
    return new;
}

void changePoint2D(Point2D *old, Point2D new) {
    old->xCol = new.xCol;
    old->yRow = new.yRow;
}
