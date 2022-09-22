#include<bits/stdc++.h>
#include<omp.h>

int main()
{
	long long sum = 0;
	
	double getInTime = omp_get_wtime();
	
	#pragma omp parallel for reduction(+ : sum)
	
	for (int i=1;i <= 100000000; i++)
		sum += i*i;
	
	double getOutTime = omp_get_wtime();
	
	double exptTime= getOutTime - getInTime;
	
	printf("Time required for Execution in Parallel: %f\n", exptTime);
	
	printf("Answer is: %lld", sum);
	
	return 0;
}
