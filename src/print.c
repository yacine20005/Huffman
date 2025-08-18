#include "print.h"

void displayOccurrences(int *occurrenceArray)
{
    for (int i = 0; i < CHARACTER_COUNT; i++)
    {
        if (occurrenceArray[i] != 0)
        {
            if (i == 10)
            {
                printf("'\\n' : %d\n", occurrenceArray[i]);
            }
            else
            {
                printf("'%c' : %d\n", i, occurrenceArray[i]);
            }
        }
    }
}

void displayHuffman(Huffman huffman, int numLetters)
{
    for (int i = 0; i < numLetters; i++)
    {
        printf("'%c' : %d | %d | %d\n", huffman.array[i].letter, huffman.array[i].occur, huffman.array[i].left, huffman.array[i].right);
    }
    printf("Number of leaves: %d\n", huffman.nbLeaves);
    printf("Number of nodes: %d\n", huffman.nbNodes);
    printf("Next leaf: %d\n", huffman.nextLeaf);
    printf("Next internal node: %d\n", huffman.nextInternal);
}