#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project3A_queue.h"
#define UNUSED __attribute__((unused))

/* C program that creates an implementation of a queue. The queue must use a dynamic array, 
and utilize the concept of a circular array queue. ONLY WORKS WITH STRINGS (char arrays). */

int main(int argc, char *argv[]){
    if (argc != 3){ IssueBadInputError(); }

    // Opening file
    FILE *input_file = fopen(argv[1], "r");
    //printf("This is the file: \n%s", input_file);
    if (input_file == NULL) { IssueBadFileError(argv[1]); }
    // printf("File Name: %s\n", argv[1]);   // Uncomment to print out file name

    // Getting size of file 
    fseek(input_file, 0, SEEK_END);
    int file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    // printf("%d\n", file_size);   //Uncomment to print out file_size

    // Make buffer from file
    char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, input_file);
    if (buffer == NULL) { IssueMemoryError(); }
    // printf("%s\n", buffer);   //Uncomment to print out buffer

    // Initializing the Queue
    Queue *q = malloc(sizeof(Queue));
    initialize(q);
    
    // Reading Buffer into Array
    char *wordArray[1000];
    int wordCount = 0;
    char *delimiter = argv[2];
    char *currWord = strtok(buffer, delimiter);
    
    for(int i = 0; i < 1000 ; i++){
        wordArray[i] = NULL;
    }
    
    while (currWord != NULL){
        // printf("%s\n", currWord);   // Uncomment to print out each word
        wordArray[wordCount] = malloc((maxStrLen + 1) * sizeof(char));
        if (my_strlen(currWord) >= maxStrLen){ IssueStrLengthError(wordCount); } 
        strncpy(wordArray[wordCount], currWord, my_strlen(currWord));

        wordCount++;
        currWord = strtok(NULL, argv[2]);
    }

    // // Printing wordArray
    // printf("\n=> Looping through wordArray\n");   // Uncomment to print out wordArray
    // for (int i = 0; i < wordCount; i++) {
    //     printf("%d: %s\n", i, wordArray[i]);
    // }

    // First enqueuing pass
    printf("\n=> First enqueuing pass\n");
    for (int i = 0; i < wordCount; i++){
        enqueue(q, wordArray[i]);
    }

    // Dequeuing all elements
    printf("\n=> Dequeuing all elements\n");
    for (int i = 0; i < wordCount; i++){
        UNUSED char *word = dequeue(q);
    }

    // Second enqueuing pass
    printf("\n=> Second enqueuing pass\n");
    for (int i = 0; i < wordCount; i++){
        enqueue(q, wordArray[i]);
    }

    // Printing Queue
    printf("\n=> Printing queue\n");
    printQueue(q);
    printf("Capacity: %d, used: %d\n", q->capacity, q->size);
    
    // Cleanup
    printf("\n=> Calling Queue cleanup\n");
    for (int i = 0; i < wordCount; i++) {
        //printf("%d: %s\n", i, wordArray[i]);
        free(wordArray[i]);
    }
    cleanup(q);
    free(q);
    free(buffer);
    fclose(input_file);
    return EXIT_SUCCESS;
}
