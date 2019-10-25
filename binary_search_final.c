#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>

#define block 10

void pbs(int *a,int key,int start,int end);

int bs(int *a,int key,int start,int end)
{
    int res=-1;
    if(start<=end)
    {
        int mid=(start+end)/2;

        if(a[mid]==key)
        {
            res=mid;
        }
        else if(a[mid]<key)
        {
            res=bs(a,key,mid+1,end);
        }
        else
        {
            res=bs(a,key,start,mid-1);
        }
    }
    return res;
}

void pbs(int *a,int key,int start,int end)
{
    int res[4];
    omp_set_num_threads(4);
    #pragma omp parallel for shared(res,a,key)
    for(int i=0;i<4;i++)
    {
        res[i]=bs(a,key,i*block,(i+1)*block-1);
    }
    /*for(int i=0;i<4;i++)
    {
        printf("%d\t",res[i]);
    }*/
}

int main()
{
  int *a;
  int n=40;
  a=(int *)malloc(sizeof(int)*n);

  for(int i=0;i<n;i++)
    a[i]=i;

  double start,end;

  start=omp_get_wtime();
  int res=bs(a,39000,0,n-1);
  printf("%d\t",res);
  end=omp_get_wtime();

  printf("%f\t",end-start);

  start=omp_get_wtime();
  pbs(a,39000,0,n-1);
  end=omp_get_wtime();

  printf("%f\t",end-start);
}
