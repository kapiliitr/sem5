#include "common.h"
#include "process.h"
#include "queue.h"

int main() 
{
    queue ready, waiting;
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

        cout<<"New Process: 1\tInterrupt: 2\tI/O: 3\tI/O Completed: 4\tNo Action: 5\tExit: 6\nEnter: "; cin>>choice;
        
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
            case '2':if(execution!=NULL)
                         ready.enqueue(execution->process_id,execution->burst_time,execution->time_rem);
                     execution = ready.dequeue();
                     break;
            case '3':if(execution!=NULL)
                         waiting.enqueue(execution->process_id,execution->burst_time,execution->time_rem);
                     execution = ready.dequeue();
                     break;
            case '4':if(!waiting.isempty())
                     {
                         temp = waiting.dequeue();
                         if(temp!=NULL)
                            ready.enqueue(temp->process_id,temp->burst_time,execution->time_rem);
                     }
                     break;
            default:break;
        };
         
        ready.bsort();     
        if(execution==NULL && !ready.isempty())
            execution = ready.dequeue();
       
        cout<<"\nTime: "<<time<<endl;
        cout<<"Ready Queue: "; ready.display();
        if(execution==NULL)
            cout<<"Execution: NULL"<<endl;
        else
             cout<<"Execution: "<<execution->process_id<<endl;
        cout<<"Waiting: ";  waiting.display();
        cout<<"\n";

        time++;
    }while(choice!='6');

    return 0;
}
