#include "genome.h"
#include <stdio.h>
#include <stdlib.h>

//----------------------HELPER FUNCTION DECLARATIONS----------------------------------

int ** copyDatatoMatrix(int numberofElements, int numberofArrays, FILE* readptr);
void freeMatrix(int** geneSequence,int numberofArrays);
void createSignificantPowesets(int** geneSequence, int numberofElements, int numberofArrays, Graph* subsetGraph);

// DECLARATIONS FOR GRAPH FUNCTIONS
AdjListNode* newAdjListNode(int dest);
Graph* createGraph(int V);
void insertEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void freeGraph(Graph* freeGraph);
void longestchaininGraph(Graph* subsetGraph);

// STACK FUNCTIONS
void push(Stack *s, int vertex);
void pop(Stack *s);

//------------------------------------------------------------------------------------

//----------------------START OF GENOME.C----------------------------
int *Longest_conserved_gene_sequence(char* filename, int *size_of_seq)
{
    // READING THE FIRST N AND M VALUES FROM THE GIVEN FILE
    int numberofElements;
    int numberofArrays;
    FILE *readptr = fopen(filename,"rb");
    if(readptr == NULL)
    {
        fprintf(stderr,"Failed to open input file");
        return 0;
    }
    int value1 = fread(&numberofElements, sizeof(int), 1, readptr);
    int value2 = fread(&numberofArrays, sizeof(int), 1, readptr);
    if(value1 + value2 != 2)
    {
        return 0;
    }
    
    // COPYING THE ARRAY INTO THE A 2D ARRAY
    int** geneSequence = copyDatatoMatrix(numberofElements, numberofArrays, readptr);
    
    //-----------------WRITE CODE FOR LONGEST COMMON INCREASING POWERSET------------------------
    
    //Creating a graph of the common subsets of length 2
    int vertex = numberofElements;
    struct Graph* subsetGraph = createGraph(vertex);
    createSignificantPowesets(geneSequence, numberofElements, numberofArrays, subsetGraph);
    longestchaininGraph(subsetGraph);
    //printGraph(subsetGraph); // UNCOMMENT TO TEST THE GRAPH CREATION
    //-----------------------------------END OF MAIN MODULE CODE--------------------------------
    
    // FREEING A 2D ARRAY
    freeMatrix(geneSequence, numberofArrays);
    // FREEING THE GRAPH
    freeGraph(subsetGraph);
    // CLOSING THE OPENED FILE
    fclose(readptr); 
    return NULL;
}

//------------------END OF GENOME.C---------------------------------

//------------------START OF HELPER FUCNTIONS------------------------

//------------------BASIC GRAPH OPERATIONS-------------------------------------

// Creating a new Adjecent List node
AdjListNode* newAdjListNode(int dest)
{
    AdjListNode* newNode = malloc(sizeof(AdjListNode));
    newNode->adjecent = dest;
    newNode->weight = 0;
    newNode->next = NULL;
    return newNode;
}

// Creating a new Graph
Graph* createGraph(int V)
{
    Graph* newGraph = malloc(sizeof(Graph));
    newGraph->vertex = V;

    newGraph->array = malloc(V * sizeof(AdjList));
    
    // Initializing each array element as NULL in the graph
    int AdjListCounter = 0;
    for(AdjListCounter = 0; AdjListCounter < V; AdjListCounter++)
    {
        newGraph->array[AdjListCounter].head = NULL;
        newGraph->array[AdjListCounter].maxWeight = 1;
    }
    return newGraph;
}

void insertEdge(Graph* graph, int src, int dest)
{
    // Add an edge that points from source to destination or <u,v>
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // UNCOMMENT IF YOU WANT THE GRAPH TO BE UNDIRECTIONAL
    /*newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;*/
}


void freeGraph(Graph* freeGraph)
{
    int vertex = 0;
    for(vertex = 0; vertex < freeGraph->vertex; vertex++)
    {
        while(freeGraph->array[vertex].head != NULL)
        {
            AdjListNode* temp = freeGraph->array[vertex].head;
            freeGraph->array[vertex].head = temp->next;
            free(temp);
        }
    }
    free(freeGraph->array);
    free(freeGraph);

}

// Printing the graph. CREATED FOR TESTING PURPOSES
//-------------------- TEST-------------------------
void printGraph(Graph* graph)
{
    int v;
    for (v = 0; v < graph->vertex; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d with maxWeight %d\n head ", v+1, graph->array[v].maxWeight);
        while (pCrawl)
        {
            printf("-> %d, %d", pCrawl->adjecent + 1, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}
//-----------------------TEST------------------------

//------------------------END OF BASIC GRAPH OPERATIONS------------------------

// FUNCTION THAT COPIES THE DATA FROM THE FILE INTO A MTRIX
int ** copyDatatoMatrix(int numberofElements, int numberofArrays, FILE* readptr)
{
    // MALLOC SPACE FOR THE 2D MATRIC
    int i = 0;
    int j = 0;
    int** geneSequence;  
    geneSequence = malloc(numberofArrays*sizeof(int*)); 
    for (i = 0; i < numberofArrays; i++)
    {
       geneSequence[i] =  malloc(numberofElements*sizeof(int));
    }
    // COPYING THE INNPUTS FROM THE FILE TO THE MATRIX
    for(i = 0; i < numberofArrays; i++)
    {
        for(j = 0; j < numberofElements; j++)
        {
            int val = fread(&geneSequence[i][j], sizeof(int), 1, readptr);
            if(val != 1)
            {
                fclose(readptr);
                return 0;
            }
            //printf("%d ",geneSequence[i][j]); //Uncomment to print the matrix (FOR TESTING)
        }
        //printf("\n"); //Uncomment to print the matrix (FOR TESTING)
    }
    return geneSequence;
}

// FUNCTION TO FREE MALLOCED SPACE
void freeMatrix(int** geneSequence, int numberofArrays)
{
    int i = 0;
    for (i = 0; i < numberofArrays; i++)
    {
        free(geneSequence[i]);
    }
    free(geneSequence);
}

int checkLocalPosition(int* geneSequence, int num1, int num2, int numberofElements)
{
    int i = 0;
    int posnum1 = 0;
    int posnum2 = 0;
    for(i = 0; i < numberofElements; i++)
    {
        if(geneSequence[i] == num1)
        {
            posnum1 = i;
        }
        if(geneSequence[i] == num2)
        {
            posnum2 = i;
        }
    }
    if(posnum1 < posnum2)
    {
        return 1;
    }
    return 0;
}

int checkRelativePosition(int** geneSequence, int num1, int num2, int numberofElements, int numberofArrays)
{
    int rowNumber = 1;
    int localpos = 0;
    for(rowNumber = 1; rowNumber < numberofArrays; rowNumber++)
    {
        localpos = checkLocalPosition(geneSequence[rowNumber],num1,num2,numberofElements);
        if (localpos == 0)
        {
            return 0;
        }
    }
    return 1;
}

void createSignificantPowesets(int** geneSequence, int numberofElements, int numberofArrays,Graph* subsetGraph)
{
    int start = 0;
    int secondaryCounter = 0;
    int end = numberofElements;
    int pos = 0;
    // THIS VARIABLE WAS CREATED FOR THE PURPOSE OF TIME ANALYSIS 
    //int numberofComparisions = 0;
    for(start = 0; start < end; start++)
    {
        for(secondaryCounter = start + 1; secondaryCounter < end; secondaryCounter++)
        {
            pos = checkRelativePosition(geneSequence, geneSequence[0][start],geneSequence[0][secondaryCounter], numberofElements, numberofArrays);
            if(pos == 1)
            {
                int src = geneSequence[0][start] - 1;
                int dest = geneSequence[0][secondaryCounter] - 1;
                insertEdge(subsetGraph, src, dest);
                //printf("%d comes before %d in all arrays\n",geneSequence[0][start],geneSequence[0][secondaryCounter]);
            }
            //numberofComparisions++;
        }
    }
    //printf("Number of comparisions: %d\n", numberofComparisions);
}

// FUNCTION TO RECURSIVELY FIND THE DISTANCE OF EACH NODE
int addMaxWeight(Graph* graph, int vertex)
{
    AdjListNode* temp = graph->array[vertex].head;
    int largestWeight = 0;
    if(temp == NULL)
    {
        return 0;
    }
    largestWeight = temp->weight;
    while(temp)
    {
        if(temp->weight > largestWeight)
        {
            largestWeight = temp->weight;
        }
        temp = temp->next;
    }
    return largestWeight;
}

int findNodeWeight(Graph *subsetGraph, char* visited, int number)
{
    if(visited[number] == 't')
    {
        return subsetGraph->array[number].maxWeight;
    }
    if(subsetGraph->array[number].head == NULL)
    {
        visited[number] = 't';
        return subsetGraph->array[number].maxWeight;
    }
    visited[number] = 't';
    AdjListNode *temp = subsetGraph->array[number].head;
    while(temp)
    {
        temp->weight += findNodeWeight(subsetGraph,visited,temp->adjecent);
        temp = temp->next;
    }
    subsetGraph->array[number].maxWeight += addMaxWeight(subsetGraph, number);
    return subsetGraph->array[number].maxWeight;
}

int findLargestWeightedNode(Graph* subsetGraph)
{
    int nodeCounter = 0;
    int largestWeight = 0;
    int position = 0;
    largestWeight = subsetGraph->array[0].maxWeight;
    for(nodeCounter = 0; nodeCounter < subsetGraph->vertex; nodeCounter++)
    {
        if(largestWeight < subsetGraph->array[nodeCounter].maxWeight)
        {
            largestWeight = subsetGraph->array[nodeCounter].maxWeight;
            position = nodeCounter;
        }
    }
    return position;
}

// FUNCTION TO FIND THE LONGEST CHAIN IN THE GRAPH

void longestchaininGraph(Graph* subsetGraph)
{
    Stack chain;
    chain.stk = malloc(sizeof(int)*subsetGraph->vertex);
    chain.top = -1;
    chain.MAXSIZE = subsetGraph->vertex;
    char* visited = malloc(sizeof(char)*subsetGraph->vertex);
    int counter = 0;
    for(counter = 0; counter < subsetGraph->vertex; counter++)
    {
        visited[counter] = 'f';
    }
    for(counter = 0; counter < subsetGraph->vertex; counter++)
    {
        findNodeWeight(subsetGraph, visited, counter);
    }
    int position = findLargestWeightedNode(subsetGraph);
    printf("Largest Node is at %d\n",position + 1);
    free(chain.stk);
    free(visited);
}

//--------------------END OF HELPER FUCNTIONS------------------------