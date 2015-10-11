/***************************************/
  /* AUHTOR: Brandon Johnson */
   /* PROFESSOR: M. Zahran */
          /* LAB 02 */
/***************************************/


#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
int * array;
size_t used;
size_t size;
} Cities;

/* */
Cities a;

/**********************************/
/* 	      Global Variables 	      */
/**********************************/


/* Unassigned integer variables */
int rows = 1;		
int columns = 1;
int distance = 0;
int invariant = 0;
int leastArrayElement = 0;

/**********************************/
/* 	    Function declarations 	  */
/**********************************/

int recursion ();
void initArray ();
void freeArray ();
void insertArray ();
int isvalueinarray();

/**********************************/
/* 			Main Function 		  */
/**********************************/

int main(int argc, char * argv[])
{
/* Assigned variables */
int entry = -1;	


/* Unassigned FILE variable */
FILE * file;



/* */
int DIM;

// In this block of code, we test to see if we only have 3 arguments;
// if not, we print out what the command line arguments should be.
if (argc != 3)
{
	printf("usage: tsm num file\n");
	printf("tsm = program command");
	printf("num = total number of cities\n");
	printf("file = the file (name) containing (distance) matrix\n");
	exit(1);
}

// Attempts to open file from commandline argument 3
file = fopen(argv[2],"r");

// If file could not be open, print message, exit program.
if (!file)
{
	printf("Cannot open file %s\n",argv[2]);
	exit(1);
}


// Dimensions of the matrix
DIM = atoi(argv[1]);

// Matrix declaration
int MATRIX[DIM][DIM];

for (rows = 0; rows < DIM; rows++)
	for (columns = 0; columns < DIM; columns++)
	{
		entry = -1;

		if (fscanf(file,"%d", &entry) != 1)
		{
			printf("Error reading cell at (%d,%d)\n", rows, columns);
			exit(1);
		}

		MATRIX[rows][columns] = entry;
	}

	insertArray(&a, 0); // STAYS OUTSIDE

	distance = recursion(DIM, MATRIX, 0);

	printf("Shortest Path: ");

	int i;
	for (i = 0; i < a.used; i++)
		printf("%d ", a.array[i]);

	printf("\n");

	printf ("Total weight: %d\n", distance);
}

int recursion (int dim, int matrix[dim][dim], int index)
{
	int row;
	int column = index;
	int minValue = matrix[column][1];
	int minIndex = 1;
	for(row = 1; row < dim; row++) {
		if (minValue > matrix[column][row] && matrix[index][row] != 0) {
			if (!isvalueinarray(row, &a.array, dim)) {}
				minValue = matrix[column][row];
				minIndex = row;
			}
		}
	}
	printf("%d\t", minIndex);
	printf("%d\n", minValue);

	insertArray(&a, minIndex);
	distance += minValue;
	invariant++;
	if (invariant + 1 < dim ) {
		return recursion (dim, matrix, minIndex);
	}
	else {
		return distance;
	}
}
void initArray(Cities *a, size_t initialSize) 
{
	a->array = (int *)malloc(initialSize * sizeof(int));
	a->used = 0;
	a->size = initialSize;
}

void insertArray(Cities *a, int element) 
{
	if (a->used == a->size) {
		a->size *= 2;
		a->array = (int *)realloc(a->array, a->size * sizeof(int));
	}
	a->array[a->used++] = element;
}

void freeArray(Cities *a) 
{
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}
int isvalueinarray(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}