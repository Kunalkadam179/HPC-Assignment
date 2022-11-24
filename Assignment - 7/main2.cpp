#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

// Size of the matrix (NxN)
#define N 512

MPI_Status status;

// Define matrices
int matrix1[N][N];
int matrix2[N][N];
int productMatrix[N][N];

// Counter variables
int i, j, k;

int main(int argc, char **argv)
{
	int numberOfProcessors;
	int processorRank;
	int numberOfWorkers;
	
	// Processor sending data
	int sourceProcessor;
	
	// Processor to receive data
	int destinationProcessor;
	
	// The number of rows for a worker processor to process
	int rows;
	
	// The subset of a matrix to be processed by workers
	int matrixSubset;
	
	// Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	// Determine number of processors available
	MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcessors);
	
	// Determine rank of calling process
	MPI_Comm_rank(MPI_COMM_WORLD, &processorRank);
	
	numberOfWorkers = numberOfProcessors - 1;
	
	double stime,etime;
	
	/* ---------- Manager Processor Code ---------- */
	
	if (processorRank == 0)
	{
		// Initialize a timer
		stime = MPI_Wtime();
		
		printf("\nMultiplying a %dx%d matrix using %d processor(s).\n\n", N, N, numberOfProcessors);
		
		// Populate the matrices with values
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				matrix1[i][j] = (rand() % 6) + 1;
				matrix2[i][j] = (rand() % 6) + 1;
			}
		}
		
		/* Send the matrix to the worker processes */
		rows = N / numberOfWorkers;
		matrixSubset = 0;
		
		// Iterate through all of the workers and assign work
		for (destinationProcessor = 1; destinationProcessor <= numberOfWorkers; destinationProcessor++)
		{
			// Determine the subset of the matrix to send to the destination processor
			MPI_Send(&matrixSubset, 1, MPI_INT, destinationProcessor, 1, MPI_COMM_WORLD);
			
			// Send the number of rows to process to the destination worker processor
			MPI_Send(&rows, 1, MPI_INT, destinationProcessor, 1, MPI_COMM_WORLD);
			
			// Send rows from matrix 1 to destination worker processor
			MPI_Send(&matrix1[matrixSubset][0], rows * N, MPI_INT, destinationProcessor, 1, MPI_COMM_WORLD);
			
			// Send entire matrix 2 to destination worker processor
			MPI_Send(&matrix2, N * N, MPI_INT, destinationProcessor, 1, MPI_COMM_WORLD);
			
			// Determine the next chunk of data to send to the next processor
			matrixSubset = matrixSubset + rows;
		}
		
		// Retrieve results from all workers processors
		for (i = 1; i <= numberOfWorkers; i++)
		{
			sourceProcessor = i;
			MPI_Recv(&matrixSubset, 1, MPI_INT, sourceProcessor, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&rows, 1, MPI_INT, sourceProcessor, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&productMatrix[matrixSubset][0], rows * N, MPI_INT, sourceProcessor, 2, MPI_COMM_WORLD, &status);
		}
		
		// Stop the timer
		etime = MPI_Wtime();
		
		// Determine and print the total run time
		printf("Runtime:  %f seconds\n",etime-stime);
	}
	
	/* ---------- Worker Processor Code ---------- */
	
	if (processorRank > 0)
	{
		sourceProcessor = 0;
		MPI_Recv(&matrixSubset, 1, MPI_INT, sourceProcessor, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&rows, 1, MPI_INT, sourceProcessor, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&matrix1, rows * N, MPI_INT, sourceProcessor, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&matrix2, N * N, MPI_INT, sourceProcessor, 1, MPI_COMM_WORLD, &status);
		
		/* Perform matrix multiplication */
		for (k = 0; k < N; k++)
		{
			for (i = 0; i < rows; i++)
			{
				productMatrix[i][k] = 0.0;
				for (j = 0; j < N; j++)
				{
					productMatrix[i][k] = productMatrix[i][k] + matrix1[i][j] * matrix2[j][k];
				}
			}
		}
		
		MPI_Send(&matrixSubset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&productMatrix, rows * N, MPI_INT, 0, 2, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
}