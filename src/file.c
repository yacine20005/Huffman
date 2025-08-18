#include "file.h"

FILE *openFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", fileName);
        exit(1);
    }
    return file;
}