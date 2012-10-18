#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<string>
#include<map>
#include<vector>
#include<deque>

using namespace std;

int main()
{
    int num_of_pages, num_of_frames, next_page, pop_page, num_page_faults=0;
    vector<int> pages;
    vector<int>::iterator it;
    deque<int> fifo_q;
    deque<int>::iterator jt;
    map<int,bool> pages_queue_map;
    int i;

    cout<<"FIFO page replacement\nNote: Pages are 1-indexed"<<endl;
    cout<<"Enter total number of pages : "; cin>>num_of_pages;
    cout<<"Enter number of frames : "; cin>>num_of_frames;
    cout<<"Enter the reference string :"<<endl;
    while(cin>>next_page, next_page!=0)
    {
         pages.push_back(next_page);
    }

    for(i=1;i<=num_of_pages;i++)
        pages_queue_map[i]=false;
    
    cout<<"Simulation : "<<endl;

    for(it=pages.begin();it<pages.end();it++)
    {
        if(pages_queue_map.find(*it)->second==true) //Page found in FIFO queue
            continue;
        else
        {
            num_page_faults++;
            if(((int)fifo_q.size())==num_of_frames) //Do page replacement
            {   
                pop_page = fifo_q.front();
                fifo_q.pop_front();
                pages_queue_map[pop_page] = false;
            }
            //Insert page
            fifo_q.push_back(*it); 
            pages_queue_map[*it] = true;
        }
        for(jt=fifo_q.begin();jt<fifo_q.end();jt++)
            cout<<*jt<<"  ";
        cout<<endl;
    }
    cout<<"Number of page faults = "<<num_page_faults<<endl;

    return 0;
}

