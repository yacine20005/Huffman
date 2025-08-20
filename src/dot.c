#include "dot.h"
#include <stdlib.h>
#include <string.h>

// Print a character safely in DOT label context (escape special/non-printables)
void fprint_safe_label(FILE *f, unsigned char c)
{
    switch (c)
    {
    case '\\':
        fprintf(f, "\\\\");
        break;
    case '"':
        fprintf(f, "\\\"");
        break;
    case '\n':
        fprintf(f, "\\n");
        break;
    case '\r':
        fprintf(f, "\\r");
        break;
    case '\t':
        fprintf(f, "\\t");
        break;
    default:
        if (c < 32 || c > 126)
        {
            // Show non-printable/extended characters in hex
            fprintf(f, "0x%02X", c);
        }
        else
        {
            fputc(c, f);
        }
    }
}

void emit_node(FILE *f, int id, const Node *n)
{
    if (n->left == -1 && n->right == -1)
    {
        // Leaf: show character and frequency
        fprintf(f, "  n%d [shape=box, label=\"'", id);
        fprint_safe_label(f, n->letter);
        fprintf(f, "'\\n%d\"];\n", n->occur);
    }
    else
    {
        // Internal: show cumulative frequency
        fprintf(f, "  n%d [shape=circle, label=\"%d\"];\n", id, n->occur);
    }
}

int huffman_write_dot(const Huffman *h, const char *filepath)
{
    if (!h || !h->array || h->nbNodes <= 0 || !filepath)
        return 1;

    FILE *f = fopen(filepath, "w");
    if (!f)
        return 2;

    fprintf(f, "digraph huffman {\n");
    fprintf(f, "  rankdir=TB;\n");
    fprintf(f, "  node [fontname=Helvetica];\n");

    // Emit all known nodes (0..nbNodes-1).
    for (int i = 0; i < h->nbNodes; ++i)
    {
        emit_node(f, i, &h->array[i]);
    }

    // Internal nodes seem to be appended starting at initial nextInternal = nbLeaves.
    // The last internal node (root) should be h->nbNodes - 1 in this model.
    int root = h->nbNodes - 1;

    // Emit edges from all nodes that have children.
    for (int i = 0; i < h->nbNodes; ++i)
    {
        const Node *n = &h->array[i];
        if (n->left != -1)
        {
            fprintf(f, "  n%d -> n%d [label=\"0\"];\n", i, n->left);
        }
        if (n->right != -1)
        {
            fprintf(f, "  n%d -> n%d [label=\"1\"];\n", i, n->right);
        }
    }

    // Highlight the root
    if (root >= 0)
    {
        fprintf(f, "  n%d [style=bold];\n", root);
    }

    fprintf(f, "}\n");
    fclose(f);
    return 0;
}

int huffman_write_pdf(const Huffman *h, const char *dotPath, const char *pdfPath)
{
    if (!h || !dotPath || !pdfPath)
        return 1;
    int rc = huffman_write_dot(h, dotPath);
    if (rc != 0)
        return 2; // dot writing failed

    // Build a command to render PDF using Graphviz 'dot'.
    // Use -Tpdf DOT -o PDF
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "dot -Tpdf '%s' -o '%s'", dotPath, pdfPath);

    int sysrc = system(cmd);
    if (sysrc != 0)
    {
        return 3; // dot not installed or failed
    }
    return 0;
}
