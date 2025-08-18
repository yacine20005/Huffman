#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "huffman.h"
#include "loop.h"
#include "file.h"
#include "print.h"
#include "dot.h"

int main()
{
    FILE *in = openFile("data/data.txt");
    Huffman huffman = buildHuffman(in);

    // Ensure output directory exists (POSIX). If it exists, ignore error.
    (void)mkdir("out", 0777);

    // Generate DOT and PDF directly when running the executable
    int rc_dot = huffman_write_dot(&huffman, "out/huffman.dot");
    if (rc_dot == 0)
    {
        printf("DOT generated: out/huffman.dot\n");
    }
    else
    {
        fprintf(stderr, "Failed to generate DOT (code %d)\n", rc_dot);
    }

    int rc_pdf = huffman_write_pdf(&huffman, "out/huffman.dot", "out/huffman.pdf");
    if (rc_pdf == 0)
    {
        printf("PDF generated: out/huffman.pdf\n");
    }
    else if (rc_pdf == 3)
    {
        fprintf(stderr, "Graphviz 'dot' not found or failed; skipping PDF.\n");
    }
    else
    {
        fprintf(stderr, "Failed to generate PDF (code %d)\n", rc_pdf);
    }

    return 0;
}