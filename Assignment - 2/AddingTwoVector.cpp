#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main()
{
	int n,i;
	cout<<"Enter the size of Vector: ";
	cin>>n;
	vector<int> a(n),b(n),c(n);
	
	cout<<"Enter Elements of first Array\n";
	for(i=0;i<n;i++)
		cin>>a[i];
	
	cout<<"Enter Elements of Second Array\n";
	for(i=0;i<n;i++)
		cin>>b[i];
	
	double getInTime = omp_get_wtime();
	
	#pragma omp parallel for shared(a, b, c) private(i) schedule(static)
	
	for(i=0;i<n;i++)
	{
		c[i] = a[i] + b[i];
		printf("Thread %d works on elemet %d \n", omp_get_thread_num(), i);
	}
	
	double getOutTime = omp_get_wtime();
	
	double exptTime= getOutTime - getInTime;
	
	printf("Time required for Execution in Parallel: %f\n", exptTime);
	
	cout<<"Addition of Two Array\n";
	for(i=0;i<n;i++)
	{
		printf("%d ", c[i]);
	}
	
	return 0;
}
