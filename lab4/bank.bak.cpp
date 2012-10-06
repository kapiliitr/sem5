#include<iostream>
#include<cstdlib>

using namespace std;

bool checkfinish(bool finish[], int n)
{
	int i;
	for(i=0;i<n;i++)
		if(!finish[i])
			return false;
	return true;
}

int main()
{
	int numproc, numres;
	cout<<"Number of processes : ";	cin >> numproc;
	cout<<"Number of resources : "; cin>>numres;

	int available[numres];
	int allocation[numproc][numres];
	int need[numproc][numres];
	int max[numproc][numres];
	bool finish[numproc];
	int sequence[numproc];
	int i,j,k;

	for(i=0;i<numproc;i++)
		finish[i] = false;

	cout<<"Available resources"<<endl;
	for(i=0;i<numres;i++)
		cin>>available[i];

	cout<<"Maximum resources"<<endl;
	for(i=0;i<numproc;i++)
		for(j=0;j<numres;j++)
			cin>>max[i][j];

	cout<<"Currently allocated resources"<<endl;
	for(i=0;i<numproc;i++)
		for(j=0;j<numres;j++)
		{
			cin>>allocation[i][j];
			if(allocation[i][j]>max[i][j])
			{
				cout << "Exceed maximum limit" << endl;
				exit(1);
			}
		}

	for(i=0;i<numproc;i++)
		for(j=0;j<numres;j++)
			need[i][j]=max[i][j]-allocation[i][j];

	bool found;
	
	i=0;
	k=0;
	while(!checkfinish(finish,numproc))
	{
		if(i==numproc)
		{
			cout << "Unsafe state reached...Aborting" << endl;
			exit(1);
		}
		for(i=0;i<numproc;i++)
		{
			if(!finish[i])
			{
				found = true;
				for(j=0;j<numres;j++)
				{
					if(need[i][j]>available[j])
					{
						found = false;
						break;
					}
				}
				if(found)
				{
					sequence[k++] = i;
					for(j=0;j<numres;j++)
					{
						available[j] += allocation[i][j];
					}
					finish[i] = true;
				}
			}
		}
	}

	cout<<"Sequence of processes"<<endl;
	for(i=0;i<numproc;i++)
		cout<<sequence[i]<<", ";
	cout<<endl;
	cout<<"Successful simulation of Banker's algorithm"<<endl;

	return 0;
}
