#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main()
{
    int n = rand()%100 + 1;
    int i;
    int *nut = (int *)malloc(n*sizeof(int));
    int *bolt = (int *)malloc(n*sizeof(int));

    for(i=0; i<n; i++)
    {
        nut[i] = rand()%1000 + 1;
        bolt[i] = nut[i];
    }

    for (i=0; i<(n-1); i++) 
    {
        int r = i + (rand() % (n-i));
        int temp = bolt[i]; bolt[i] = bolt[r]; bolt[r] = temp;
    }

    ofstream fill("prob1.txt");

    fill << n << endl;
    for(i=0; i<n; i++)
        fill << nut[i] << " " << bolt[i] << endl;
    
    return 0;
}
