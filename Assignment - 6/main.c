#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	//Initialize the MPI environment
	MPI_Init(NULL,NULL);
	//Get the rank of process
	int rank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int a[10] = {5, 6, 4, 6, 7, 4, 3, 2, 7, 10};
	int b[10] = {8, 5, 9, 2, 10, 7, 3, 5, 9, 1};
	
	MPI_Status status;
	
	if(rank == 0)
	{
		MPI_Send(a, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(b, 10, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
	}
	else if(rank == 1)
	{
		MPI_Send(a, 10, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Recv(b, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	}
	printf("I am %d: Recieved %d\n", rank, b[0]);
	
	//Finalize the MPI environment
	MPI_Finalize();
	return 0;
}
