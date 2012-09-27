/*
 * Design a merging algorithm such that each item is compared at most a logarithmic number of 
 *
 * times. (In the standard merging algorithm, an item can be compared N/2 times when merging 
 *
 * two subarrays of size N/2.)
 */
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

using namespace std;

int merge(int [], int [], int [], int, int);
int bsearch(int [], int, int, int);

int main()
{
	int n, m, k, i;
 	int *a,*b,*c;
	 	
	ifstream fil;
	fil.open("prob2.txt");
	
	fil >> m;
    fil >> n;
 	
 	a = (int *)malloc(m*sizeof(int));
 	b = (int *)malloc(n*sizeof(int)); 	
  	c = (int *)malloc((m+n)*sizeof(int)); 	
	
 	for(i=0; i<m; i++)
 	{
	    fil >> a[i];
    }
 
    for(i=0; i<n; i++)
 	{
	    fil >> b[i];
    }

    k = merge(a, b, c, m, n);
    
    for(i=0; i<k; i++)
	    printf("%d ",c[i]);
    printf("\n");
    
    fil.close();
    
    return 0;
}

int merge(int a[], int b[], int c[], int m, int n)
{
   int i=0,j=0,k=0,t; 
   
   while(i<m && j<n)
   {
       t=bsearch(b,a[i],j,n-1);
       while(j<t)
       {
           c[k++] = b[j++];
       }
       c[k++] = a[i++];
   }
   while(i<m)
       c[k++] = a[i++];
   while(j<n)
       c[k++] = b[j++];

   return k;
}

int bsearch(int a[], int d, int min, int max)
{
    while(max>=min)
    {
        int mid = (min+max)/2;
        if(a[mid]<d)
            min = mid+1;
        else if(a[mid]>d)
            max = mid-1;
        else
        {
            return mid;
        }
    }
    return max+1;
}
