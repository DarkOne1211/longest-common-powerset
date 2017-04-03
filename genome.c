#include "genome.h"
#include <stdio.h>
#include <stdlib.h>

// HELPER FUNCTION DECLARATIONS
int ** copyDatatoMatrix(int numberofElements, int numberofArrays, FILE* readptr);
void freeMatrix(int** geneSequence,int numberofArrays);
void createSignificantPowesets(int** geneSequence, int numberofElements, int numberofArrays);

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
    
    createSignificantPowesets(geneSequence, numberofElements, numberofArrays);
    
    //-----------------------------------END OF MAIN MODULE CODE--------------------------------
    
    // FREEING A 2D ARRAY
    freeMatrix(geneSequence, numberofArrays);
    fclose(readptr);
    return NULL;
}

//------------------END OF GENOME.C---------------------------------

//------------------START OF HELPER FUCNTIONS------------------------

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

void createSignificantPowesets(int** geneSequence, int numberofElements, int numberofArrays)
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
                //printf("%d comes before %d in all arrays\n",geneSequence[0][start],geneSequence[0][secondaryCounter]);
            }
            else
            {
                //printf("Nothing happened\n");
            }
            //numberofComparisions++;
        }
    }
    //printf("Number of comparisions: %d\n", numberofComparisions);
}
//--------------------END OF HELPER FUCNTIONS------------------------