/*
 * You have a mixed pile of N nuts and N bolts and need to quickly find the corresponding pairs 
 *
 * of nuts and bolts. Each nut matches exactly one bolt and each bolt matches exactly one nut. 
 *
 * By fitting a nut and bolt together, you can see which is bigger. But it is not possible to 
 *
 * directly compare two nuts or two bolts. Give an efficient method for solving the problem
 */
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

using namespace std;

void solve(int [], int [], int, int);
int partition(int [], int, int);
void swap(int *, int *);

int main()
{
	int n, i;
 	int *nut,*bolt;
	 	
	ifstream fil;
	fil.open("prob1.txt");
	
	fil >> n;
 	
 	nut = (int *)malloc(n*sizeof(int));
 	bolt = (int *)malloc(n*sizeof(int)); 	
 	
 	for(i=0; i<n; i++)
 	{
	    fil >> nut[i];
	    fil >> bolt[i];
    }
 
    solve(nut, bolt, 0, n-1);
    
    for(i=0; i<n; i++)
	    printf("%d : %d\n",nut[i],bolt[i]);
    
    fil.close();
    
    return 0;
}

void solve(int nut[], int bolt[], int p, int r)
{
    int qn,qb,q,i,j,t;
      
    if(p<r)
    {
        j=rand()%(r-p+1)+p; //random element to start with
        i=p;
        while(i<=r && nut[j]!=bolt[i])
        {
            i++;
        }
        if(nut[j]==bolt[i])
        {
            swap(&nut[j],&nut[r]);
            qn=partition(nut,p,r);
            swap(&bolt[i],&bolt[r]);
            qb=partition(bolt,p,r);
            if(qn==qb)
            {
                q=qn;
                solve(nut,bolt,p,q-1);
                solve(nut,bolt,q+1,r);
            }
        }
    }
}

int partition(int arr[], int p, int r)
{
    int x = arr[r];
    int i = p-1;
    int j,temp;

    for(j=p; j<r; j++)
    {
        if(arr[j]<=x)
        {
            i++;
            swap(&arr[i],&arr[j]);
        }
    }

    swap(&arr[i+1],&arr[r]);

    return i+1;
}

void swap(int *i, int *j)
{
    int t = *i;
    *i = *j;
    *j = t;
}
