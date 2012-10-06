#include<iostream>

using namespace std;

#define N 10

int req[N][N];
int all[N][N];
bool visproc[N]; 
bool visres[N];
bool stackproc[N];
bool stackres[N];

bool checkcycle(int , int );
bool dfsproc(int , int , int );
bool dfsres(int , int , int );

int main()
{
    int numproc, numres;
    cout<<"Number of processes (<10) : "; cin>>numproc;
    cout<<"Number of resources (<10) : "; cin>>numres;

    int i,j;

    for(i=0;i<numproc;i++)
        for(j=0;j<numres;j++)
            req[i][j]=0;

    for(i=0;i<numres;i++)
        for(j=0;j<numproc;j++)
            all[i][j]=0;

    cout<<"Enter Claim edges : "<<endl;
    for(i=0;i<numproc;i++)
    {
        cout<<"Process "<<i+1<<" : ";
        while(cin>>j,j!=0)
        {
            req[i][j-1]=1;
        }
    }

    cout<<"Enter Allocated edges : "<<endl;
    for(i=0;i<numres;i++)
    {
        cout<<"Resource "<<i+1<<" : ";
        while(cin>>j,j!=0)
        {
            all[i][j-1]=1;
        }
    }

    bool deadlock = checkcycle(numproc,numres);

    int proc,res;
    while(!deadlock)
    {
        cout<<"Process to make request : "; cin>>proc;
        cout<<"Resource to which request is made : "; cin>>res;
        if(req[proc-1][res-1]==1)
        {
            bool free = true;
            for(i=0;i<numproc;i++)
                if(all[res-1][i]==1)
                {
                    free = false;
                    cout<<"Resource "<<res<<" is already allocated to some other process. Wait."<<endl;
                    break;
                }
            if(free)
            {
                all[res-1][proc-1]=1; req[proc-1][res-1]=0;
                if(checkcycle(numproc,numres))
                    deadlock = true;
                else
                    cout << "Successfull allocation of resource " << res << " to process "<< proc << endl;
            }
        }
        else
        {
            cout<<"Process "<<proc<<" cannot request from resource "<<res<<endl;
        }
    };

    if(deadlock)
        cout << "Deadlock will occur. Wait." << endl;

    return 0;
}

bool checkcycle(int numproc, int numres)
{
    int i;
    for(i=0;i<numproc;i++)
    {
        visproc[i]=false;		 				     
        stackproc[i]=false;
    }
    for(i=0;i<numres;i++)
    {
        visres[i]=false;
        stackres[i]=false;
    }
    for(i=0;i<numproc;i++)
    {
        if(!visproc[i])
            if(dfsproc(i,numproc,numres))
                return true;
    }
    return false;
}

bool dfsproc(int i, int np, int nr)
{
    visproc[i]=true;
    stackproc[i]=true;
    int j;
    for(j=0;j<nr;j++)
    {
        if(req[i][j]==1)
        {
            if(!visres[j] && dfsres(j,np,nr))
                return true;
            else if (stackres[j])
                return true;
        }
    }
    stackproc[i]=false;
    return false;		 
}

bool dfsres(int i, int np, int nr)
{
    visres[i]=true;
    stackres[i]=true;
    int j;
    for(j=0;j<np;j++)
    {
        if(all[i][j]==1)
        {
            if(!visproc[j] && dfsproc(j,np,nr))
                return true;
            else if (stackproc[j]) 
                return true;
        }
    }
    stackres[i]=false;
    return false;
}
