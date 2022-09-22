#include<omp.h>
#include<bits/stdc++.h>

int main(int argc, char* argv[])
{
	#pragma omp parallel
	{
		printf("Thread No. %d Hello World\n", omp_get_thread_num());
	}
	return 0;
}
