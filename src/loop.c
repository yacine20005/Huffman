#include "loop.h"

Huffman buildHuffman(FILE *in)
{
    int *occurrenceArray = storeOccurrences(in);
    fclose(in);
    int numLetters = countLetters(occurrenceArray);
    Huffman huffman = initHuffman(occurrenceArray, numLetters);
    sortNodes(huffman.array, numLetters); // sort leaves once
    // Build until all internal nodes are created: total nodes become 2*L-1
    while (huffman.nbNodes < huffman.capacity)
    {
        growTree(&huffman);
    }
    return huffman;
}