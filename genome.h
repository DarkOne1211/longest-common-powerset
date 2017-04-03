#ifndef GENOME_H
#define GENOME_H

//GRAPH DATA STRUCTURES
typedef struct AdjListNode
{
    int adjecent;
    struct AdjListNode* next;
}AdjListNode;

typedef struct AdjList
{
    struct AdjListNode* head; 
}AdjList;

typedef struct Graph
{
    int vertex;
    struct AdjList* array;
}Graph;

// FUNCTION TO FIND THE LONGEST CONSERVERED NUMERICAL GENE SEQUENCE
int *Longest_conserved_gene_sequence(char* filename, int *size_of_seq);

#endif