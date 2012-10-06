#include<iostream>
#include<cstdlib>

using namespace std;

#define N 10 //max number of processes and resources 

int available[N];
int allocation[N][N];
int request[N][N];
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
                if(request[i][j]>available[j])
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
	cout<<"Number of processes : ";	cin >> numproc;
	cout<<"Number of resources : "; cin>>numres;

	int i,j,k;

	cout<<"Available resources"<<endl;
	for(i=0;i<numres;i++)
		cin>>available[i];

	cout<<"Currently allocated resources"<<endl;
	for(i=0;i<numproc;i++)
		for(j=0;j<numres;j++)
			cin>>allocation[i][j];

    cout<<"Request resources"<<endl;
	for(i=0;i<numproc;i++)
		for(j=0;j<numres;j++)
			cin>>request[i][j];

    for(i=0;i<numproc;i++)
    {
        finish[i]=true;
        for(j=0;j<numres;j++)
            if(allocation[i][j])
            {
                finish[i]=false;
                break;
            }
    }

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
        cout<<"Deadlock not found"<<endl;
    }
    else
    {
       cout<<"Deadlocked processes are"<<endl;
       for(i=0;i<numproc;i++)
       {
           if(!finish[i])
               cout<<i+1<<", ";
       }
       cout<<endl;
    }
	return 0;
}
