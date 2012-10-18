#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<string>
#include<map>
#include<vector>
#include<list>
#include<limits.h>

using namespace std;

int main()
{
    int num_of_pages, num_of_frames, next_page, remove_page, num_page_faults=0;
    vector<int> pages;
    vector<int>::iterator it;
    list<int> lfu_l;
    list<int>::iterator jt;
    map<int,bool> pages_queue_map;
    map<int,int> pages_count;
    int i,min;

    cout<<"Least Frequently Used(LFU) page replacement\nNote: Pages are 1-indexed"<<endl;
    cout<<"Enter total number of pages : "; cin>>num_of_pages;
    cout<<"Enter number of frames : "; cin>>num_of_frames;
    cout<<"Enter the reference string :"<<endl;
    while(cin>>next_page, next_page!=0)
    {
         pages.push_back(next_page);
    }

    for(i=1;i<=num_of_pages;i++)
    {
        pages_queue_map[i]=false;
        pages_count[i]=0;
    }
    
    cout<<"Simulation : "<<endl;

    for(it=pages.begin();it<pages.end();it++)
    {
        pages_count[*it]++;
        if(pages_queue_map.find(*it)->second==true) //Page found in FIFO queue
        {
            continue;
        }
        else
        {
            num_page_faults++;
            if(((int)lfu_l.size())==num_of_frames) //Do page replacement
            {
                min=INT_MAX;
                for(jt=lfu_l.begin();jt!=lfu_l.end();jt++)
                {
                    if(pages_count[*jt]<min)
                    {
                        remove_page=*jt;
                        min=pages_count[*jt];
                    }
                }
                lfu_l.remove(remove_page);
                pages_queue_map[remove_page] = false;
            }
            //Insert page
            lfu_l.push_back(*it); 
            pages_queue_map[*it] = true;
        }
        for(jt=lfu_l.begin();jt!=lfu_l.end();jt++)
            cout<<*jt<<"  ";
        cout<<endl;
    }
    cout<<"Number of page faults = "<<num_page_faults<<endl;

    return 0;
}

