class process
{
public:
	process * next;
    process * previous;
    int process_id;
    int burst_time;
    int arrival_time;
    int wait_time;
    int last_executed;
    int priority;
    process();
};

process::process()
{
    wait_time=0;
    last_executed=-1;
    next=previous=NULL;
    priority=1;
}

queue<process> job,ready,finished;

void create()
{
    process * newp = new process;
    cout<<"Process_id Burst_time Arrival_time Priority : "; 
    cin>>newp->process_id; cin>>newp->burst_time; cin>>newp->arrival_time;cin>>newp->priority;
    job.enqueue(newp);
}

int clockt = 0;
int forward;

void priority()
{
    process* currentprocess = NULL;
    
    while(!job.isempty() || !ready.isempty() || currentprocess!=NULL)
    {
        gantt* entry = new gantt;       
        process * nextinline = job.getfront();

        while(!job.isempty() && nextinline->arrival_time <= clockt)
        {       
            ready.enqueue(job.dequeue());       
            nextinline = job.getfront();       
        }        
      
        if(nextinline)
            forward = nextinline->arrival_time - clockt;
        else
            forward = 10000;

        if(currentprocess) 
            ready.enqueue(currentprocess); 
    
        currentprocess = ready.extractminpriority();

        if(currentprocess)
        {
            entry->id = currentprocess->process_id;
            entry->start = clockt;

            if(currentprocess->last_executed == -1)
                currentprocess->wait_time = (clockt - currentprocess->arrival_time);
            else
                currentprocess->wait_time += (clockt - currentprocess->last_executed);

            if(currentprocess->burst_time > forward)
            {
                clockt += forward; 
                currentprocess->burst_time -= forward;
            }
            else
            {
                clockt += currentprocess->burst_time;
                currentprocess->burst_time = 0;
                finished.enqueue(currentprocess);
                currentprocess->last_executed = clockt;
                currentprocess=NULL;
            }
        }
        else
        {
            entry->id = 0;
            entry->start = clockt;
            clockt += forward;
        }

        entry->end = clockt;
        if(currentprocess) 
            currentprocess->last_executed = clockt;
        gchart.enqueue(entry);
    }
}
