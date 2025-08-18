#ifndef HUFFMAN_H
#define HUFFMAN_H

#define CHARACTER_COUNT 256
#include <stdlib.h>
#include <stdio.h>
#include "file.h"

typedef struct
{
    unsigned char letter;
    int occur;
    int left;
    int right;
} Node;

typedef struct
{
    Node *array;
    int nbLeaves;
    int nbNodes;
    int nextLeaf;
    // Index of the first not-yet-consumed internal node (acts as a queue head)
    int firstInternal;
    int nextInternal;
    int capacity; // total allocated size for array (>= 2*nbLeaves-1)
} Huffman;

// Counts the number of letters in the array
int countLetters(int arr[]);

// Initializes the Huffman structure
Huffman initHuffman(int arr[], int len);

// Initializes the nodes of the array
Node *initNodes(Huffman *huff, int arr[], int len);

// Sorts the nodes
void sortNodes(Node *array, int len);

// Finds the minimum node
int minNode(Huffman *huff);

// Grows the Huffman tree
void growTree(Huffman *huff);

// Returns the total occurrence count across all leaf nodes
int getTotalOccurrence(Huffman huff);

// Stores the occurrences of characters in the file
int *storeOccurrences(FILE *file);

#endif // HUFFMAN_H