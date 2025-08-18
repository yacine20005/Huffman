#ifndef DOT_H
#define DOT_H

#include <stdio.h>
#include "huffman.h"

// Export the Huffman structure to a Graphviz DOT file.
// Returns 0 on success, non-zero on failure.
int huffman_write_dot(const Huffman *h, const char *filepath);

// Write the DOT file, then invoke Graphviz (dot) to render a PDF.
// - dotPath: path to the output DOT file (will be overwritten).
// - pdfPath: path to the output PDF file (will be overwritten).
// Returns:
//   0  -> success (both DOT and PDF created)
//   1  -> invalid args / invalid Huffman structure
//   2  -> failed to write DOT file
//   3  -> Graphviz 'dot' not found or failed to run
int huffman_write_pdf(const Huffman *h, const char *dotPath, const char *pdfPath);

#endif // DOT_H
