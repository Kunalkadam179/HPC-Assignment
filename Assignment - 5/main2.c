#include <mpi.h>
#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv)
{
	
	//Initialize the MPI environment
	MPI_Init(NULL,NULL);
	
	//Get the rank of process
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Group group;
	MPI_Comm_group(MPI_COMM_WORLD, &group);
	
	printf("Rank: %d, Group: %d \n", rank, group);
	
	//Finalize the MPI environment
	MPI_Finalize();
	return 0;
}

