#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<memory.h>
void sort(int a[],int n,int thread_count);
int main(int argc,char* argv[]) {
	int n,k,i;
	int thread_count = atoi(argv[1]);
	scanf("%d",&n);							//how many number to run
	srand(time(NULL));
	int *a = (int *)malloc(n*sizeof(int));
	for(k=0;k<n;k++)
	{
		a[k] = rand()%n;					//rand number
	}
	double startwtime = omp_get_wtime();	//starttime
	
	sort(a,n,thread_count);					//counting sort

	double endwtime = omp_get_wtime();		//overtime
	for(i = 0;i<n;i++)
	{
		printf("%d ",a[i]);					//print result
	}
	printf("\n");
	printf("%lf\n",endwtime-startwtime);
	return 0;
}
void sort(int a[],int n,int thread_count) {
	int i,j,count;
	int *temp = (int *)malloc(n*sizeof(int));			//parellel
	#pragma omp parallel for num_threads(thread_count)\
	        default(none) private(i, j, count) shared(a, n, temp)
        for(i = 0;i<n;i++)
		{
			count = 0;
			for(j = 0;j<n;j++)
				if(a[j]<a[i])
        	        count++;
   	 		    else if(a[j] == a[i] && j<i)		//sort
                	count++;
	        temp[count] = a[i];
		}
	memcpy(a,temp,n*sizeof(int));					//exchange a temp
	free(temp);										//free temp

}
