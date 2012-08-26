#include "common.h"
#include "process.h"
#include "queue.h"

int main() 
{
    queue ready, waiting, job, execution;
    char choice; 
    int pid=1;
    job.enqueue(pid++);
    job.enqueue(pid++);
    job.enqueue(pid++);
    job.enqueue(pid++);
    job.enqueue(pid++);
    job.enqueue(pid++); 
    do {
        job.enqueue(pid++);
        if(execution.isempty() && !ready.isempty()) {
            execution.enqueue(ready.dequeue());
        }
        else if(execution.isempty() && ready.isempty()) {
            execution.enqueue(job.dequeue());
        }

        cout<<"\nReady Queue: ";ready.display();
        cout<<"Execution: "; execution.display();
        cout<<"Job: ";  job.display();
        cout<<"Waiting: ";  waiting.display();
        cout<<"\n";

        cout<<"Scheduler: 1\tInterrupt: 2\tI/O: 3\tInterrupt-I/O Transmitted: 4\tTerminate: 5\nEnter: "; cin>>choice;
        if(choice=='1')
        {
            ready.enqueue(job.dequeue());
        }
        else if(choice=='2')
        { 
            if(!ready.isempty()) 
                execution.enqueue(ready.dequeue());
            else 
                execution.enqueue(job.dequeue());
            ready.enqueue(execution.dequeue());
        }
        else if(choice=='3')
        { 
            if(!ready.isempty()) 
                execution.enqueue(ready.dequeue());
            else 
                execution.enqueue(job.dequeue());
            waiting.enqueue(execution.dequeue());
        }
        else if(choice=='4')
        {
            ready.enqueue(waiting.dequeue());
        }
        else if(choice=='5')
        {
            if(!ready.isempty())
                execution.enqueue(ready.dequeue());
            else 
                execution.enqueue(job.dequeue());
            execution.dequeue();
        }
        else 
        {
            cout<<"Exit!";
        }	
    }while(choice=='1'||choice=='2'||choice=='3'||choice=='4'||choice=='5');

    return 0;
}
