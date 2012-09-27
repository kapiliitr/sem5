template <class node>
class queue
{
private:
	node * front;
	node * rear;
    int length;
public:
	queue();
	~queue();
	void enqueue(node * input);
    node* dequeue();
    bool isempty();
    node* getfront();
    node* extractminpriority();
    int getlength();
};

template <class node>
queue<node>::queue()
{
	front=NULL;
	rear=NULL;
    length=0;
}

template <class node>
queue<node>::~queue()
{
	while(front!=NULL)
	{
		node * temp=front;
		front=front->next;
		delete temp;
	}
	rear=front;
    length=0;
}

template <class node>
void queue<node>::enqueue(node * input)
{
    if(rear!=NULL)
	{
		rear->next=input;
		input->next=NULL;
        input->previous=rear;
		rear=input;
	}
	else
	{
		input->next=NULL;
        input->previous=NULL;
		rear=input;
		front=input;
	}
    length++;
}

template <class node>
node* queue<node>::dequeue()
{
	if(front!=NULL)
	{
		node * temp=front;
		front=front->next;
		if(front==NULL)
		{
			rear=NULL;
		}
        else
        {
            front->previous=NULL;
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

template <class node>
bool queue<node>::isempty()
{
	return (front==NULL);
}

template <class node>
node* queue<node>::getfront()
{
    return front;
}

template <class node>
int queue<node>::getlength()
{
    return length;
}

template <class node>
node* queue<node>::extractminpriority()
{
    node * temp = front;
    node * ret = temp;
    while(temp!=NULL)
    {
        if(temp->priority < ret->priority)
            ret = temp;
        temp=temp->next;
    }
   
    if(ret)
    {
        if(ret->previous!=NULL)
            ret->previous->next=ret->next;
        else
        {
            front=ret->next;
        }

        if(ret->next!=NULL)
        {
            ret->next->previous=ret->previous;
        }
        else
        {
            rear = ret->previous;
        }
    }
    return ret;
}
