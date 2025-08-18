#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// Opens a file and returns the file pointer
FILE *openFile(char *fileName);

// Stores the occurrences of characters in the file
int *storeOccurrences(FILE *file);

#endif // FICHIER_H