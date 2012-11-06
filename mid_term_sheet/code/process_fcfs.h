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
    process();
};

process::process()
{
    wait_time=0;
    last_executed=-1;
    next=previous=NULL;
}

queue<process> job,ready,finished;

void create()
{
    process * newp = new process;
    cout<<"Process_id Burst_time Arrival_time : "; 
    cin>>newp->process_id; cin>>newp->burst_time; cin>>newp->arrival_time;
    job.enqueue(newp);
}

int clockt=0;

void fcfs()
{
  process* currentprocess=NULL;
  
  while(!job.isempty() || !ready.isempty() || currentprocess!=NULL)
  {
    gantt* entry = new gantt;
    process* nextinline = job.getfront();

    while(!job.isempty() && (nextinline->arrival_time <= clockt))
    {
        ready.enqueue(job.dequeue());
        nextinline = job.getfront();
    }

    if(currentprocess != NULL) 
        ready.enqueue(currentprocess);
    
    currentprocess = ready.dequeue();
    
    if(currentprocess != NULL)
    {
      entry->id = currentprocess->process_id;
      entry->start = clockt;

      if(currentprocess->last_executed == -1)
        currentprocess->wait_time = (clockt - currentprocess->arrival_time);
      else
        currentprocess->wait_time += (clockt - currentprocess->last_executed);

      clockt += currentprocess->burst_time;
      currentprocess->burst_time = 0;
      finished.enqueue(currentprocess);
      currentprocess->last_executed = clockt;
      currentprocess = NULL;
    }
    else
    {
      entry->id = 0;
      entry->start = clockt;
      int forward = nextinline->arrival_time - clockt;
      clockt += forward;
    }

    entry->end = clockt;
    if(currentprocess!=NULL)
        currentprocess->last_executed = clockt;
    gchart.enqueue(entry);
  }
}
