#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "huffman.h"

// Displays the occurrences of characters
void displayOccurrences(int *occurrenceArray);

// Displays the Huffman tree information
void displayHuffman(Huffman huffman, int numLetters);

#endif // PRINT_H