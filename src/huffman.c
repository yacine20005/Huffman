#include "huffman.h"

int countLetters(int arr[])
{
    int numLetters = 0;
    for (int i = 0; i < CHARACTER_COUNT; i++)
    {
        if (arr[i])
        {
            numLetters++;
        }
    }
    return numLetters;
}

Huffman initHuffman(int arr[], int len)
{
    Huffman huffman;
    huffman.nbLeaves = len;
    huffman.nbNodes = len;
    huffman.nextLeaf = 0;        // head index into the sorted leaves segment
    huffman.firstInternal = len; // first internal node index (queue head)
    huffman.nextInternal = len;  // next free slot to append a new internal node (queue tail)
    huffman.capacity = (len > 0) ? (2 * len - 1) : 0;
    huffman.array = initNodes(&huffman, arr, len);
    return huffman;
}

Node *initNodes(Huffman *huffman, int arr[], int len)
{
    // allocate enough space for all nodes (leaves + internal nodes)
    Node *node = (Node *)malloc((size_t)huffman->capacity * sizeof(Node));
    int idx = 0;
    for (int i = 0; i < CHARACTER_COUNT; i++)
    {
        if (arr[i])
        {
            node[idx].letter = i;
            node[idx].occur = arr[i];
            node[idx].left = -1;
            node[idx].right = -1;
            idx++;
        }
    }
    // Initialize the rest (future internal nodes)
    for (int i = len; i < huffman->capacity; ++i)
    {
        node[i].letter = 0;
        node[i].occur = 0;
        node[i].left = -1;
        node[i].right = -1;
    }
    return node;
}

void sortNodes(Node *array, int len)
{
    for (int i = 0; i < len; i++)
    {
        int min = i;
        while (min > 0 && array[min].occur <= array[min - 1].occur)
        {
            if (array[min].occur == array[min - 1].occur)
            {
                if (array[min].letter < array[min - 1].letter)
                {
                    Node tmp = array[min];
                    array[min] = array[min - 1];
                    array[min - 1] = tmp;
                }
                min--;
            }
            else
            {
                Node tmp = array[min];
                array[min] = array[min - 1];
                array[min - 1] = tmp;
                min--;
            }
        }
    }
}

void growTree(Huffman *huff)
{
    // Two-queue method:
    // - Leaves are in array[0 .. nbLeaves-1], sorted by occur ascending
    // - Internal nodes are appended at array[nbLeaves ..), also non-decreasing by construction
    // We'll select the minimum head among the two queues for left and right children.

    // Compute next candidate indices from both queues
    int leafHead = huff->nextLeaf;
    int leafEnd = huff->nbLeaves; // exclusive
    int intHead = huff->firstInternal;
    int intEnd = huff->nextInternal; // exclusive

    // Pick smallest for left child
    int leftIdx;
    if (leafHead < leafEnd && intHead < intEnd)
    {
        if (huff->array[leafHead].occur <= huff->array[intHead].occur)
        {
            leftIdx = leafHead++;
        }
        else
        {
            leftIdx = intHead++;
        }
    }
    else if (leafHead < leafEnd)
    {
        leftIdx = leafHead++;
    }
    else
    {
        leftIdx = intHead++;
    }

    // Pick smallest for right child
    int rightIdx;
    if (leafHead < leafEnd && intHead < intEnd)
    {
        if (huff->array[leafHead].occur <= huff->array[intHead].occur)
        {
            rightIdx = leafHead++;
        }
        else
        {
            rightIdx = intHead++;
        }
    }
    else if (leafHead < leafEnd)
    {
        rightIdx = leafHead++;
    }
    else
    {
        rightIdx = intHead++;
    }

    if (huff->nextInternal >= huff->capacity)
    {
        fprintf(stderr, "Error: Huffman capacity exceeded (%d/%d)\n", huff->nextInternal, huff->capacity);
        exit(2);
    }

    Node newNode;
    newNode.letter = 0;
    newNode.occur = huff->array[leftIdx].occur + huff->array[rightIdx].occur;
    newNode.left = leftIdx;
    newNode.right = rightIdx;

    huff->array[huff->nextInternal] = newNode;
    huff->nbNodes++;

    // Commit queue heads and append position
    huff->nextLeaf = leafHead;
    huff->firstInternal = intHead;
    huff->nextInternal++;
}

int getTotalOccurrence(Huffman huff)
{
    int total = 0;
    for (int i = 0; i < huff.nbLeaves; i++)
    {
        total += huff.array[i].occur;
    }
    return total;
}

int *storeOccurrences(FILE *file)
{
    char c;
    int *occurrenceArray = (int *)calloc(CHARACTER_COUNT, sizeof(int));
    while ((c = fgetc(file)) != EOF)
    {
        occurrenceArray[(int)c]++;
    }
    return occurrenceArray;
}