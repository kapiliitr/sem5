class gantt
{
    public:
        gantt * next;
        gantt * previous;
        int start;
        int end;
        int id;
};

queue<gantt> gchart;

void displayGchart()
{
    gantt * temp = gchart.getfront();
    while(temp!=NULL)
    {
        cout<<"Start:"<<temp->start
            <<" Process:"<<temp->id
            <<" End:"<<temp->end<<endl;
        temp=temp->next;
    }
}
