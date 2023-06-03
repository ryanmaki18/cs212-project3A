#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNUSED __attribute__((unused))

#define initialSize 8
#define maxStrLen 256


typedef struct Queue {
    char** array;    // Queue array - pointer to a pointer to a char data type
    int front;       // Queue front index, initially 0
    int rear;        // Queue rear index, initially 0
    int capacity;    // Queue capacity, initially 8
    int size;        // Queue array populated count, initially 0
} Queue;

void initialize(Queue* q);
void cleanup(Queue* q);
int isFull(Queue* q);
int isEmpty(Queue* q);
void resize(Queue* q);
void enqueue(Queue* q, char* value);
char* dequeue(Queue* q);
void printQueue(Queue* q);

int my_strlen(char *src);
void IssueBadInputError();
void IssueBadFileError(char *fileName);
void IssueMemoryError();
void IssueStrLengthError(int wordIndex);


#endif // DYNAMIC_QUEUE_H