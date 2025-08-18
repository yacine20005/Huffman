#ifndef LOOP_H
#define LOOP_H

#include <stdio.h>
#include "huffman.h"
#include "print.h"

// Builds the Huffman structure from an input file
Huffman buildHuffman(FILE *in);

#endif // LOOP_H