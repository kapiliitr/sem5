#include <iostream>

using namespace std;

#include "queue.h"
#include "gantt.h"
#include "process_fcfs.h"
#include "finishedprocess.h"

void controls()
{
    cout<<"New Process: 1\tEvaluate: 2\tShow Gantt Chart: 3\tExit: 4"<<endl;
}

int main()
{
    int choice;
    controls();
    do
    {
        cout<<"Enter choice : "; cin>>choice;

        switch(choice)
        {
            case 1:create();
                   break;
            case 2:fcfs();
                   break;
            case 3:displayGchart();
                   break;
            default:break;
        }
    }while(choice!=4);
    waitingtime();
    turnaroundtime();
    return 0;
}
