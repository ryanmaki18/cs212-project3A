#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project3A_queue.h"

void IssueBadInputError(){
    printf("Please provide a file name and a delimiter\n");
    exit(EXIT_FAILURE);
}

void IssueBadFileError(char *fileName){
    printf("Could not open file %s\n", fileName);
    exit(EXIT_FAILURE);
}

void IssueMemoryError(){
    printf("Failed to allocate memory\n");
    exit(EXIT_FAILURE);
}

void IssueStrLengthError(int wordIndex){
    printf("Length of string #%d is too long\n", wordIndex);
    exit(EXIT_FAILURE);
}

void initialize(Queue* q){
    q->array = malloc(initialSize * sizeof(char *));
    if (q->array == NULL) { IssueMemoryError(); }
    q->front = 0;
    q->rear = 0;
    q->capacity = initialSize; 
    q->size = 0;

    // Allocate memory for each word in array
    for(int i = 0; i < q->capacity; i++){
        q->array[i] = malloc((maxStrLen + 1) * sizeof(char)); 
        if (q->array[i] == NULL) { IssueMemoryError(); }
    }
}

void cleanup(Queue* q){
    printf("Cleaning up queue\n");
    for(int i = 0; i < q->capacity; i++){
        free(q->array[i]);
    }
    free(q->array);
}

int isFull(Queue* q){
    return q->size >= q->capacity;
}

int isEmpty(Queue* q){
    return q->front == q->rear;
}

void resize(Queue* q){
    q->capacity *= 2;
    printf("Resizing queue to %d\n", q->capacity);

    // Store data in tmpArray 
    char **tmpArray = malloc(initialSize * sizeof(char *));
    if (tmpArray == NULL) { IssueMemoryError(); }
    for(int i = q->front; i < q->rear; i++){
        strncpy(tmpArray[i], q->array[i], my_strlen(q->array[i]));
    }

    //Reallocate Array
    q->array = realloc(q->array, q->capacity * sizeof(char *));

    // Allocate memory for each word in array (Again)
    for(int i = (0 + initialSize); i < q->capacity; i++){
        q->array[i] = malloc((maxStrLen + 1) * sizeof(char));  
        if (q->array[i] == NULL) { IssueMemoryError(); }
    }

    // Copy data back to reallocated array
    for(int i = q->front; i < q->rear; i++){
        strncpy(q->array[i], tmpArray[i], my_strlen(tmpArray[i]));
    }

    // Fix indexes
    if (q->rear <= q->front){
        for(int i = 0; i < q->rear; i++){
            q->array[i + q->capacity / 2] = q->array[i];
        }
        q->rear += q->capacity / 2;
    }
    free(tmpArray);
}

void enqueue(Queue* q, char* value){
    if (isFull(q)){ resize(q); }
    // Copy word to the array
    strncpy(q->array[q->rear], value, (my_strlen(value) + 1)); 
    //q->array[q->rear][my_strlen(value)] = '\0';
    printf("Enqueued (%d): %s\n", q->rear, value);  
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

char* dequeue(Queue* q){
    char *value = q->array[q->front];
    printf("Dequeued (%d): %s\n", q->front, value);
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return value;
}

void printQueue(Queue* q){
    if (isEmpty(q)){ printf("The Queue is Empty!\n"); }
    int tmpFront = q->front;
    while(tmpFront != q->rear){
        // if (q->array[tmpFront] == NULL){
        //     tmpFront = (tmpFront + 1) % q->capacity;
        //     continue;
        // }
        printf("%d: %s\n", tmpFront, q->array[tmpFront]);
        tmpFront = (tmpFront + 1) % q->capacity;
    }
}

int my_strlen(char *src){
    int totalLength = 0;
    if (src == NULL){ return 0; }
    while(*src != '\0'){
        totalLength++;
        src++;
    }
    return totalLength;
}
