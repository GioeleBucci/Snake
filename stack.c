#include <assert.h>
#include <stdlib.h>
#include "stack.h"
#include "snake.h"

void stackInit(int size) {
    stack.stack = malloc(sizeof(struct Tile) * size);
    assert(stack.stack != NULL);
    stack.size = size;
    stack.topElem = -1;
}

/// Handles snake segments.
/// If the stack is empty the first segment pushed will become the head, tail otherwise
void push(struct Tile elem) {

    if (stack.topElem == stack.size - 1) {
        stack.stack = realloc(stack.stack, sizeof(struct Tile) * stack.size + 10);
        assert(stack.stack != NULL);
        stack.size = stack.size + 1;
    }

    //assign correct body segment
    elem.type = stack.topElem == -1 ? HEAD : TAIL;
    elem.render = stack.topElem == -1 ? '@' : 'O';

    stack.topElem++;
    stack.stack[stack.topElem] = elem;
}

/// Returns top element or null if stack is empty
struct Tile *pop() {
    if (stack.topElem == -1) return NULL;
    Tile *elem = &(stack.stack[stack.topElem]);

    stack.topElem--;
    return elem;
}
