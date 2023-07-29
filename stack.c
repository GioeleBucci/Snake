#include <assert.h>
#include <stdlib.h>
#include "stack.h"
#include "snake.h"

void stackInit(int size, Stack *stackPtr) {
    stackPtr->stack = malloc(sizeof(struct Tile) * size);
    assert(stackPtr->stack != NULL);
    stackPtr->size = size;
    stackPtr->topElem = -1;
}

/// Handles snake segments.
/// If the stack is empty the first segment pushed will become the head, tail otherwise
void push(struct Tile elem, Stack *stackPtr) {

    if (stackPtr->topElem == stackPtr->size - 1) {
        stackPtr->stack = realloc(stackPtr->stack, sizeof(struct Tile) * stackPtr->size + 10);
        assert(stackPtr->stack != NULL);
        stackPtr->size = stackPtr->size + 1;
    }

    //assign correct body segment
    elem.type = stackPtr->topElem == -1 ? HEAD : TAIL;
    elem.render = stackPtr->topElem == -1 ? '@' : 'O';

    stackPtr->topElem++;
    stackPtr->stack[stackPtr->topElem] = elem;
}

/// Returns top element or null if stack is empty
struct Tile *pop() {
    if (stack.topElem == -1) return NULL;
    Tile *elem = &(stack.stack[stack.topElem]);

    stack.topElem--;
    return elem;
}
