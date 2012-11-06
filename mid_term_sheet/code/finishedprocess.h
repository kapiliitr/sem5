void waitingtime()
{
    float wtime = 0.0;
    if(!finished.isempty())
    {
        process* temp = finished.getfront();
        while(temp!=NULL)
        {
            wtime += (float)temp->wait_time;
            temp=temp->next;
        }
        wtime/=finished.getlength();
    }
    cout<<"Waiting time:"<<wtime<<endl;
}

void turnaroundtime()
{
    float tatime = 0.0;
    if(!finished.isempty())
    {
        process* temp = finished.getfront();
        while(temp!=NULL)
        {
            tatime += ((float)temp->last_executed-(float)temp->arrival_time);
            temp=temp->next;
        }
        tatime/=finished.getlength();
    }
    cout<<"Turn around time:"<<tatime<<endl;
}
