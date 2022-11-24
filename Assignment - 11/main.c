#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

void RowMatrixVectorMultiply(int n, double *a, double *b, double *x, MPI_Comm comm) 
   { 
     int i, j; 
     int nlocal;        /* Number of locally stored rows of A */ 
     double *fb;        /* Will point to a buffer that stores the entire vector b */ 
     int npes, myrank; 
     MPI_Status status; 
 
     /* Get information about the communicator */ 
     MPI_Comm_size(comm, &npes); 
     MPI_Comm_rank(comm, &myrank); 
 
     /* Allocate the memory that will store the entire vector b */ 
     fb = (double *)malloc(n*sizeof(double)); 
 
     nlocal = n/npes; 
 
     /* Gather the entire vector b on each processor using MPI's ALLGATHER operation */ 
     MPI_Allgather(b, nlocal, MPI_DOUBLE, fb, nlocal, MPI_DOUBLE, 
         comm); 
 
     /* Perform the matrix-vector multiplication involving the locally stored submatrix */ 
     for (i=0; i<nlocal; i++) { 
       x[i] = 0.0; 
       for (j=0; j<n; j++) 
         x[i] += a[i*n+j]*fb[j]; 
     } 
 
     free(fb); 
   }
   
int main()
{
	double* local_A;
	double* local_x;
	double* local_y;
	int n;
	int my_rank, comm_sz;
	MPI_Comm comm;
	
	MPI_Init(NULL, NULL);
	comm = MPI_COMM_WORLD;
	MPI_Comm_size(comm, &comm_sz);
	MPI_Comm_rank(comm, &my_rank);
	
	printf("Enter Size of Square matrix or length of Vector: ");
	scanf("%d", &n);
	
	local_A = (double*) malloc(n*n*sizeof(double));
	local_x = (double*) malloc(n*sizeof(double));
	local_y = (double*) malloc(n*sizeof(double));
	
	printf("Enter elements of Vector x: \n");
	for(int i=0;i<n;i++)
	{
		scanf("%lf",&local_x[i]);
	}
	
	printf("Enter elements of %d x %d Matrix A:\n", n,n);
	for(int i=0 ; i<n ; i++)
	{
		for(int j=0 ; j<n ; j++)
		{
			scanf("%lf", &local_A[i*n+j]);
		}
	}
	
	printf("\nMatrix A \n");
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%lf\t",local_A[i*n+j]);
		}
		printf("\n");
	}
	
	printf("\nVector X\n");
	
	for(int i=0;i<n;i++)
	{
		printf("%lf\t",local_x[i]);
	}
	RowMatrixVectorMultiply(n, local_A, local_x , local_y, comm);
	
	printf("\nResult\n");
	
	for(int i=0;i<n;i++)
	{
		printf("%lf\t",local_y[i]);
	}
	
	free(local_A);
	free(local_x);
	free(local_y);
	MPI_Finalize();
	return 0;

}