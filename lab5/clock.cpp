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
    int num_of_pages, num_of_frames, next_page, pop_page, num_page_faults=0, modify;
    vector<pair<int,int> > pages;
    vector<pair<int,int> >::iterator it;
    deque<pair<int,pair<int,int> > > clock_q;
    deque<pair<int,pair<int,int> > >::iterator jt;
    map<int,bool> pages_queue_map;
    pair<int,pair<int,int> > temp;
    int i,bitval,iter;
    bool found;

    cout<<"Clock page replacement\nNote: Pages are 1-indexed"<<endl;
    cout<<"Enter total number of pages : "; cin>>num_of_pages;
    cout<<"Enter number of frames : "; cin>>num_of_frames;
    cout<<"Enter the reference string :"<<endl;
    while(cin>>next_page, next_page!=0)
    {
        cin>>modify;
        pages.push_back(make_pair(next_page,modify));
    }

    for(i=1;i<=num_of_pages;i++)
        pages_queue_map[i]=false;
    
    cout<<"Simulation : "<<endl;

    for(it=pages.begin();it<pages.end();it++)
    {
        if(pages_queue_map.find((*it).first)->second==true) //Page found in Circular queue
            continue;
        else
        {
            num_page_faults++;
            if(((int)clock_q.size())==num_of_frames) //Do page replacement
            {  
                found=false;
                bitval=1;
                while(!found)
                {
                    for(i=0;i<clock_q.size();i++)
                        bitval&=(clock_q[i].second).second;
                    for(i=0;i<clock_q.size();i++)
                    {
                        temp = clock_q[i]; 
                        if((temp.second).first==0)//Remove page
                        {
                            if((temp.second).second==bitval)
                            {
                                pop_page = temp.first;
                                iter=i;
                                found=true;
                                break;
                            }
                        }
                        else 
                            (clock_q[i].second).first=0;
                    }
                }
                clock_q.erase(clock_q.begin()+iter);
                pages_queue_map[pop_page] = false;
            }
            //Insert page
            clock_q.push_back(make_pair((*it).first,make_pair(1,(*it).second))); 
            pages_queue_map[(*it).first] = true;
        }
        for(i=0;i<clock_q.size();i++)
            cout<<clock_q[i].first<<"  ";
        cout<<endl;
    }
    cout<<"Number of page faults = "<<num_page_faults<<endl;

    return 0;
}

