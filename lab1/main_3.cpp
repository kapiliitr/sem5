#include "common.h"
#include "process.h"
#include "queue.h"

int main()
{
    queue job, ready, waiting;

    job.enqueue(1); job.enqueue(2); job.enqueue(3);
    cout<<"Job Queue  "; job.display();
    cout<<"\nDequeue  "; job.dequeue();
    cout<<"Job Queue  "; job.display();

    ready.enqueue(4); ready.enqueue(5); ready.enqueue(6);
    cout<<"\n\nReady Queue  "; ready.display();
    cout<<"\nDequeue  "; ready.dequeue();
    cout<<"Ready Queue  "; ready.display();

    waiting.enqueue(7); waiting.enqueue(8); waiting.enqueue(9);
    cout<<"\n\nWaiting Queue  "; waiting.display();
    cout<<"\nDequeue  "; waiting.dequeue();
    cout<<"Waiting Queue  "; waiting.display();

    return 0;
}
