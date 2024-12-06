#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *buffer;
    int head;
    int tail;
    int max;
    int full;
} CircularBuffer;

CircularBuffer* createBuffer(int size) {
    CircularBuffer *cb = (CircularBuffer *)malloc(sizeof(CircularBuffer));
    cb->buffer = (int *)malloc(size * sizeof(int));
    cb->max = size;
    cb->head = 0;
    cb->tail = 0;
    cb->full = 0;
    return cb;
}

void freeBuffer(CircularBuffer *cb) {
    free(cb->buffer);
    free(cb);
}

int isFull(CircularBuffer *cb) {
    return cb->full;
}

int isEmpty(CircularBuffer *cb) {
    return (!cb->full && (cb->head == cb->tail));
}

void advancePointer(CircularBuffer *cb) {
    if (cb->full) {
        cb->tail = (cb->tail + 1) % cb->max;
    }
    cb->head = (cb->head + 1) % cb->max;
    cb->full = (cb->head == cb->tail);
}

void retreatPointer(CircularBuffer *cb) {
    cb->full = 0;
    cb->tail = (cb->tail + 1) % cb->max;
}

void addItem(CircularBuffer *cb, int item) {
    cb->buffer[cb->head] = item;
    advancePointer(cb);
}

int getItem(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        return -1; // Buffer is empty
    }
    int item = cb->buffer[cb->tail];
    retreatPointer(cb);
    return item;
}

int main() {
    CircularBuffer *cb = createBuffer(5);

    addItem(cb, 1);
    addItem(cb, 2);
    addItem(cb, 3);
    addItem(cb, 4);
    addItem(cb, 5);

    printf("Removed: %d\n", getItem(cb));
    printf("Removed: %d\n", getItem(cb));

    addItem(cb, 6);
    addItem(cb, 7);

    while (!isEmpty(cb)) {
        printf("Removed: %d\n", getItem(cb));
    }

    freeBuffer(cb);
    return 0;
}