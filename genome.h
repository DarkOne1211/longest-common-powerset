#ifndef GENOME_H
#define GENOME_H

//GRAPH DATA STRUCTURES
typedef struct AdjListNode
{
    int adjecent;
    int weight;
    struct AdjListNode* next;
}AdjListNode;

typedef struct AdjList
{
    int maxWeight;
    struct AdjListNode* head; 
}AdjList;

typedef struct Graph
{
    int vertex;
    struct AdjList* array;
}Graph;

typedef struct _Stack
{
    int *stk;
    int top;
    int MAXSIZE;
}Stack;

// FUNCTION TO FIND THE LONGEST CONSERVERED NUMERICAL GENE SEQUENCE
int *Longest_conserved_gene_sequence(char *filename, int *size_of_seq);

#endif