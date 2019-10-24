#include "omp.h"
#include<iostream>

using namespace std;


void gen(int* a, int* b ,int n)
{
for(int i=0;i<n;i++)
{
a[i] = n-i;
b[i] = n-i;
}

}


void bubblesort(int* a, int n)
{
for(int i=0;i<n-1;i++)
{
        for(int j=0;j<n-1;j++)
        {
                if(a[j] > a[j+1])
                {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                }
        }
}
}



void parallelbubblesort(int* b, int n)
{

int first;

omp_set_num_threads(2);

for(int i=0;i<n;i++)
{       
        first = i%2;
        
        #pragma omp parallel for default(none) , shared(b, first ,n)
        for(int j=first;j<n-1;j=j+2)
        {
        
                if(b[j]>b[j+1])
                {
                        int temp = b[j];
                        b[j] = b[j+1];
                        b[j+1] = temp;
                        
                }
        }



}



}



int main()
{

int n;
cout<<"Enter n";
cin>>n;

int* a = new int[n];
int* b = new int[n];

gen(a,b,n);


cout<<"Printing a\n";
for(int i=0;i<n;i++)
{

cout<<a[i]<<"\t";
}


cout<<"\n";


cout<<"Printing b\n";
for(int i=0;i<n;i++)
{
cout<<b[i]<<"\t";
}


cout<<"\nAfter Sorting\n";

double start = omp_get_wtime();
bubblesort(a,n);
double end = omp_get_wtime();
cout<<"\nSerial Time "<<(end-start);

double start1 = omp_get_wtime();
parallelbubblesort(b,n);
double end1 = omp_get_wtime();
cout<<"\nParallel Time \n"<<(end1-start1);





cout<<"Printing a\n";
for(int i=0;i<n;i++)
{

cout<<a[i]<<"\t";
}


cout<<"\n";


cout<<"Printing b\n";
for(int i=0;i<n;i++)
{
cout<<b[i]<<"\t";
}



}
