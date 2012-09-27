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

queue<process> job,ready1,ready2,ready3,finished;

void create()
{
    process * newp = new process;
    cout<<"Process_id Burst_time Arrival_time : ";
    cin>>newp->process_id; cin>>newp->burst_time; cin>>newp->arrival_time;
    job.enqueue(newp);
}

int clockt = 0;
int timequanta1 = 10;
int timequanta2 = 30;
int forward;

void multilevel()
{
  process * currentprocess = NULL;
  while(!job.isempty() || !ready1.isempty() || currentprocess!=NULL )
  {
    gantt* entry = new gantt;
    process* nextinline = job.getfront();
   
    if(nextinline)
        forward = nextinline->arrival_time - clockt;
    else
        forward = 10000;

    while(!job.isempty() && nextinline->arrival_time <= clockt)
    {
        ready1.enqueue(job.dequeue());
        nextinline = job.getfront();
    }
    
    if(!ready1.isempty())
    {
      currentprocess = ready1.dequeue();
      entry->id = currentprocess->process_id;
      entry->start = clockt;

      if(currentprocess->last_executed == -1)
        currentprocess->wait_time = (clockt - currentprocess->arrival_time);
      else
        currentprocess->wait_time += (clockt - currentprocess->last_executed);
      
      if(currentprocess->burst_time > timequanta1)
      {
        clockt += timequanta1; 
        currentprocess->burst_time -= timequanta1;
        ready2.enqueue(currentprocess);
      }
      else
      {
        clockt += currentprocess->burst_time;
        currentprocess->burst_time = 0;
        finished.enqueue(currentprocess);
        currentprocess = 0;
      }
    }
    else if(!ready2.isempty())
    {
      currentprocess = ready2.dequeue();
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
        ready2.enqueue(currentprocess);
      }
      else if(currentprocess->burst_time > timequanta2)
      {
        clockt += timequanta2; 
        currentprocess->burst_time -= timequanta2;
        ready3.enqueue(currentprocess);
      }
      else
      {
        clockt += currentprocess->burst_time;
        currentprocess->burst_time = 0;
        finished.enqueue(currentprocess);
        currentprocess = 0;
      }
    }
    else if(!ready3.isempty())
    {
      currentprocess = ready3.dequeue();
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
       ready3.enqueue(currentprocess);
      }
      else
      {
        clockt += currentprocess->burst_time;
        currentprocess->burst_time = 0;
        finished.enqueue(currentprocess);
        currentprocess->last_executed = clockt;
        currentprocess = 0;
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
