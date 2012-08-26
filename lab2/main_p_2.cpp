#include "common.h"
#include "process.h"
#include "queue.h"

int main() 
{
    queue ready;
    process *execution = NULL, *temp;
    int time=0, no_proc, i, burst;
    static int pid = 1;
    char choice;
    
    do
    {
        if(execution!=NULL)
        {
            execution->time_rem--;
            if(execution->time_rem==0)
                execution=NULL;
        }

        cout<<"New Process: 1\tNo Action: 2\tExit: 3\nEnter: "; cin>>choice;
        
        switch(choice)
        {
            case '1':cout<<"Enter number of processes : "; cin>>no_proc;
                     i=1;
                     while(i<=no_proc)
                     {
                         cout<<"Enter burst time for process "<<i<<": "; cin>>burst;
                         ready.enqueue(pid,burst,burst);
                         pid++;
                         i++;
                     }
                     break;
            default:break;
        };
    
        ready.bsort();    
        if(!ready.isempty())
        {
            temp = ready.getfront();
            if(execution == NULL)
            {
                execution = temp;
                ready.dequeue();
            }
            else if(execution->time_rem > temp->time_rem)
            {
                ready.enqueue(execution->process_id, execution->burst_time,execution->time_rem);
                execution = temp;
                ready.dequeue();
            }
        }
        
        cout<<"\nTime: "<<time<<endl;
        cout<<"Ready Queue: "; ready.display();
        if(execution==NULL)
            cout<<"Execution: NULL"<<endl;
        else
             cout<<"Execution: "<<execution->process_id<<endl;
        cout<<"\n";

        time++;
    }while(choice!='3');

    return 0;
}
