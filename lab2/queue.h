class queue
{
private:
	process * front;
	process * rear;
    int length;
public:
	queue();
	~queue();
	void enqueue(int n, int t, int r);
    process* dequeue();
    void display();
    bool isempty();
    void bsort();
    process* getfront();
};

queue::queue()
{
	front=NULL;
	rear=NULL;
    length=0;
}

queue::~queue()
{
	while(front!=NULL)
	{
		process * temp=front;
		front=front->next;
		delete temp;
	}
	rear=front;
    length=0;
}

void queue::enqueue(int n, int t, int r)
{
	process * temp = new process;
    temp->process_id = n;
    temp->burst_time = t;
    temp->time_rem = r;
	if(rear!=NULL)
	{
		rear->next=temp;
		temp->next=NULL;
		rear=temp;
	}
	else
	{
		temp->next=NULL;
		rear=temp;
		front=temp;
	}
    length++;
}

process* queue::dequeue()
{
	if(front!=NULL)
	{
		process * temp=front;
		front=front->next;
		if(front==NULL)
		{
			rear=NULL;
		}
        length--;
        return temp;
	}
	else
	{
		cout<<"Queue empty."<<endl;
	}	
    return NULL;
}

void queue::display()
{
	process * temp=front;
	while(temp!=NULL)
	{
		cout<<temp->process_id<<"-->";
		temp=temp->next;
	}
	cout<<"NULL"<<endl;
}

bool queue::isempty()
{
	if(front==NULL) 
        return true;
	else 
        return false;
}

void queue::bsort()
{
    int i,j;
    for(i=0;i<length;i++)
    {
        process * temp = front;
        for(j=0;j<length-1-i;j++)
        {
            if(temp->time_rem > temp->next->time_rem)
            {   
                int process_id_temp = temp->process_id;
                int burst_time_temp = temp->burst_time;
                int time_rem_temp = temp->time_rem;
                temp->process_id = temp->next->process_id;
                temp->burst_time = temp->next->burst_time;
                temp->time_rem = temp->next->time_rem;
                temp->next->process_id = process_id_temp;
                temp->next->burst_time = burst_time_temp;
                temp->next->time_rem = time_rem_temp;
            }
            temp = temp->next;
        }
    }
}

process* queue::getfront()
{
    if(front!=NULL)
        return front;
    else
        return NULL;
}
