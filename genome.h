#ifndef GENOME_H
#define GENOME_H

// DATA STRUCTURES USED

typedef struct _Subset
{
    int *LastNumber;
    struct _Subset *next;
}subset;

int *Longest_conserved_gene_sequence(char* filename, int *size_of_seq);

#endif