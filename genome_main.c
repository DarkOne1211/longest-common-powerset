#include "genome.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if((argc > 2)||(argc < 2))
    {
        fprintf(stderr,"Insufficient input commands\n");
        return EXIT_FAILURE;
    }
    int sizeofseq = 0;
    Longest_conserved_gene_sequence(argv[1],&sizeofseq);
    return EXIT_SUCCESS;
}