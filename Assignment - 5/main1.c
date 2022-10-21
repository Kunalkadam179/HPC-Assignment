#include <mpi.h>
#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv)
{
	
	//Initialize the MPI environment
	MPI_Init(NULL,NULL);
	
	printf("Hello World\n");
	
	//Finalize the MPI environment
	MPI_Finalize();
	return 0;
}
