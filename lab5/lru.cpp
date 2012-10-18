/*
 * 1st line has two ints N:no of processes M:no of frames
 * 2nd line has N ints : no of pages of each process
 * Every line will have two ints : proc no and page no which is to be requested by the user
 * Last line will end with 0
 */

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<string>
#include<map>
#include<vector>
#include<deque>

using namespace std;

#define THRESHOLD 0.9

struct process
{
    int num_of_pages;
};

int main()
{
    int num_of_procs, num_of_frames, next_page, next_proc, num_page_faults=0, length_of_string=0;
    double page_fault_rate;
    vector<pair<int,int> > pages;
    vector<pair<int,int> >::iterator it;
    deque<pair<int,int> > lru_q;
    map<pair<int,int>,bool> pages_queue_map;
    pair<int,int> remove_proc_page;
    pair<int,bool> temp_page_entry (0,false);
    int i,j,iter;

    cout<<"Least Recently Used(LRU) page replacement\n"
        <<"Note: Pages are 1-indexed\n"
        <<"N F N:no of procs F:no of frames\n"
        <<"P1 P2 P3 ... PN Pi:no of pages in process i\n"
        <<"ProcNo PageNo in every line for each page request\n"
        <<"0 end with zero\n"
        <<endl;
    
    //Enter number of processes
    cin>>num_of_procs;
    //Enter number of page frames
    cin>>num_of_frames;

    //Allocate memory for each process
    process *Proc = new process[num_of_procs];

    //Enter number of pages for each process
    for(i=0;i<num_of_procs;i++)
    {
        cin>>Proc[i].num_of_pages;
    }

    //Enter the reference string
    cout<<"Enter the reference string :"<<endl;
    while(cin>>next_proc,next_proc!=0)
    {
        cin>>next_page;
        pages.push_back(make_pair(next_proc,next_page));
    }

    for(i=0;i<num_of_procs;i++)
    {
        for(j=1;j<=Proc[i].num_of_pages;j++)
        {
            pages_queue_map[make_pair(i+1,j)]=false;
        }
    }
    
    cout<<"Simulation : "<<endl;

    for(it=pages.begin();it<pages.end();it++)
    {
        length_of_string++;
        map<pair<int,int>,bool>::const_iterator res = pages_queue_map.find(*it);
        if(res->second==true) //Page found
        {
            for(iter=0;iter<lru_q.size();iter++)
                if(lru_q[iter]==(*it))
                {
                    lru_q.erase(lru_q.begin()+iter);
                    lru_q.push_back(*it);
                    break;
                }
            //continue;
        }
        else
        {
            num_page_faults++;
            page_fault_rate = (double)num_page_faults/length_of_string;
            if(((int)lru_q.size())==num_of_frames) //Do page replacement
            {  
                for(iter=0;iter<lru_q.size();iter++)
                    if(lru_q[iter].first==(*it).first)
                    {
                        break;
                    }

                if(page_fault_rate<=THRESHOLD || iter==lru_q.size()) //Do Global LRU
                {
                    cout<<"Global"<<endl;
                    remove_proc_page = lru_q.front();
                    lru_q.pop_front();
                    pages_queue_map[remove_proc_page] = false;
                }
                else //Do Local LRU
                {
                    cout<<"Local"<<endl;
                    remove_proc_page = lru_q[iter];
                    lru_q.erase(lru_q.begin()+iter);
                    pages_queue_map[remove_proc_page] = false;
                }
            }
            //Insert page
            lru_q.push_back(*it); 
            pages_queue_map[*it] = true;
        }
        for(iter=0;iter<lru_q.size();iter++)
            cout<<"("<<lru_q[iter].first<<","<<lru_q[iter].second<<") ";
        cout<<endl;
    }
    cout<<"Number of page faults = "<<num_page_faults<<endl;
    
    //Free memory
    delete [] Proc;

    return 0;
}

