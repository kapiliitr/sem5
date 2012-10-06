#include<iostream>
#include<cstdlib>

using namespace std;

#define N 10 //maximum number of processes and resources 

int available[N];
int allocation[N][N];
int need[N][N];
int maximum[N][N];
bool finish[N];
int sequence[N];

bool checkfinish(int n)
{
	int i;
	for(i=0;i<n;i++)
		if(!finish[i])
			return false;
	return true;
}

int findindex(int np, int nr)
{
    int i,j;
    bool found;
    for(i=0;i<np;i++)
    {
        if(!finish[i])
        {
            found=true;
            for(j=0;j<nr;j++)
                if(need[i][j]>available[j])
                {
                    found=false;
                    break;
                }
            if(found)
                return i;
        }
    }
    return -1;
}

int main()
{
	int numproc, numres;
	cout<<"Number of processes (<10) : "; cin >> numproc;
	cout<<"Number of resources (<10) : "; cin>>numres;

	int i,j,k;

	for(i=0;i<numproc;i++)
		finish[i] = false;

	cout<<"Available resources"<<endl;
	for(i=0;i<numres;i++)
		cin>>available[i];

	cout<<"Maximum resources"<<endl;
	for(i=0;i<numproc;i++)
		for(j=0;j<numres;j++)
			cin>>maximum[i][j];

	cout<<"Currently allocated resources"<<endl;
	for(i=0;i<numproc;i++)
    for(j=0;j<numres;j++)
		{
			cin>>allocation[i][j];
			if(allocation[i][j]>maximum[i][j])
			{
				cout << "Exceed maximumimum limit" << endl;
				exit(1);
			}
		}

	for(i=0;i<numproc;i++)
		for(j=0;j<numres;j++)
			need[i][j]=maximum[i][j]-allocation[i][j];
	
    k=0;

    while(j=findindex(numproc,numres),j!=-1)
    {
        for(i=0;i<numres;i++)
            available[i]+=allocation[j][i];
        finish[j]=true;
        sequence[k++]=j;
    }

    if(checkfinish(numproc))
    {
        cout<<"Sequence of processes"<<endl;
        for(i=0;i<numproc;i++)
            cout<<sequence[i]<<", ";
        cout<<endl;
        cout<<"Successful simulation of Banker's algorithm"<<endl;
    }
    else
        cout << "Unsafe state reached...Aborting" << endl;

	return 0;
}
