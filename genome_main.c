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
    int* longestConservedGene = Longest_conserved_gene_sequence(argv[1],&sizeofseq);
    // PRINTS THE LONGEST SEQUENCE FOR TESTING PURPOSES
    //----------------------------------------------------------------------------
    /*int stackCounter = 0;
    for(stackCounter = 0; stackCounter < sizeofseq; stackCounter++)
    {
        printf("%d ",longestConservedGene[stackCounter]);
    }
    printf("\n");*/
    //----------------------------------------------------------------------------
    printf("Length: %d\n",sizeofseq);
    free(longestConservedGene);
    return EXIT_SUCCESS;
}