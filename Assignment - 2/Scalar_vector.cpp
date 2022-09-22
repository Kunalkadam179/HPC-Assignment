#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main()
{
	int n,i;
	cout<<"Enter the size of Vector: ";
	cin>>n;
	vector<int> a(n);
	
	cout<<"Enter Elements of Array\n";
	for(i=0;i<n;i++)
		cin>>a[i];
    int answer = 0;
	
	double getInTime = omp_get_wtime();
	
    #pragma omp parallel for
    for (i = 0; i < 5; i++)
    {
        answer += a[i];
    }
    
    double getOutTime = omp_get_wtime();
	
	double exptTime= getOutTime - getInTime;
	
	printf("Time required for Execution in Parallel: %f\n", exptTime);

   	printf("Answer %d ", answer);
	
	return 0;
}
