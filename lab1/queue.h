class queue
{
private:
	process * front;
	process * rear;
    int length;
public:
	queue();
	~queue();
	void enqueue(int n);
    int dequeue();
    void display();
    bool isempty();
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

void queue::enqueue(int n)
{
	process * temp=new process;
    temp->process_id=n;
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
    this->length++;
}

int queue::dequeue()
{
	if(front!=NULL)
	{
		process * temp=front;
        int id = temp->process_id;
		front=front->next;
		delete temp;
		if(front==NULL)
		{
			rear=NULL;
		}
        this->length--;
        return id;
	}
	else
	{
		cout<<"Queue empty."<<endl;
	}	
    return -1;
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

