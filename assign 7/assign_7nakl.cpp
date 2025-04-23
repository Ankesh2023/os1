
#include<iostream>
#include<algorithm>
#include<cmath>
#include<climits>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

//try to take set/map instead of unordered one.

void print(vector<int>& arr)
{
    cout<<"[ ";
    for(int i=0;i<arr.size()-1;i++)
    {
        cout<<arr[i]<<" , ";
    }
    cout<<arr[arr.size()-1];
    cout<<" ]\n";
}

int fcfs(int pages, vector<int>& vec, int frames)
{
    vector<int> arr;
    unordered_set<int> st;
    int faults = 0;
    int idx = 0;
    cout<<"\nFCFS algorithm is: "<<endl;
    for(int i=0;i<pages;i++)
    {
        if(st.find(vec[i]) == st.end())
        {
            faults++;
            if(arr.size() < frames)
            {
                st.insert(vec[i]);
                arr.push_back(vec[i]);
                print(arr);
            }
            else
            {
                st.erase(arr[idx]);
                arr[idx] = vec[i];
                st.insert(vec[i]);
                idx = (idx+1)%frames;
                print(arr);
            }
        }
        else
        {
            cout<<"\nHit";
            print(arr);
        }
    }
    cout<<"\nTotal Number of faults for FCFS is: "<<faults<<endl;
    return faults;
}

int lru(int pages, vector<int>& vec, int frames)
{
    unordered_map<int,int> mp;
    vector<int> arr;
    int faults = 0;
    int idx = 0;
    cout<<"\nLRU algorithm is: "<<endl;
    for(int i=0;i<pages;i++)
    {
        if(mp.find(vec[i]) == mp.end())
        {
            faults++;
            if(arr.size() < frames)
            {
                mp[vec[i]] = idx;
                idx++;
                arr.push_back(vec[i]);
                print(arr);
            }
            else
            {
                int minidx = i;
                unordered_set<int> st(arr.begin(),arr.end());
                for(int j = i-1;j>=0;j--)
                {
                    if(st.find(vec[j]) != st.end())
                    {
                        minidx = j;
                        st.erase(vec[j]);
                    }
                }
                if(minidx != i)
                {
                    int curr = mp[vec[minidx]];
                    arr[curr] = vec[i];
                    mp.erase(vec[minidx]);
                    mp[vec[i]] = curr;
                    print(arr);
                }
                else
                {
                    int val = arr[0];
                    arr[0] = vec[i];
                    mp[vec[i]] = 0;
                    mp.erase(val);
                    print(arr);
                }
            }
        }
        else
        {
            print(arr);
        }
    }
    cout<<"\nTotal Number of faults for LRU is: "<<faults<<endl;
    return faults;
}

int optimal(int pages, vector<int>& vec, int frames)
{
    vector<int> arr;
    unordered_map<int,int> mp;
    int faults = 0;
    int idx = 0;
    cout<<"\nOptimal algorithm is: "<<endl;
    for(int i=0;i<pages;i++)
    {
        if(mp.find(vec[i]) == mp.end())
        {
            faults++;
            if(arr.size() < frames)
            {
                mp[vec[i]] = idx;
                arr.push_back(vec[i]);
                idx++;
                print(arr);
            }
            else
            {
                int maxidx = i;
                unordered_set<int> st(arr.begin(),arr.end());
                for(int j=i+1;j<pages;j++)
                {
                    if(st.find(vec[j]) != st.end())
                    {
                        maxidx = j;
                        st.erase(vec[j]);
                    }
                }
                if(maxidx != i && st.size() == 0)
                {
                    int curr = mp[vec[maxidx]];
                    mp.erase(vec[maxidx]);
                    arr[curr] = vec[i];
                    mp[vec[i]] = curr;
                    print(arr);
                }
                else if(st.size() > 0)
                {
                    int ele = *st.begin();
                    int index = mp[ele];
                    mp.erase(ele);
                    arr[index] = vec[i];
                    mp[vec[i]] = index;
                    print(arr);
                }
                else
                {
                    mp.erase(arr[0]);
                    arr[0] = vec[i];
                    mp[vec[i]] = 0;
                    print(arr);
                }
            }
        }
        else
        {
            print(arr);
        }
    }
    cout<<"\nTotal Number of faults for Optimal is: "<<faults<<endl;
    return faults;
}

int main()
{
    int pages,frames;
    while(true)
    {
        cout<<"Enter number of pages: "<<endl;
        cin>>pages;
        if(cin.fail() || pages <= 0)
        {
            cout<<"Enter a valid input!"<<endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else
            break;
    }
    vector<int> vec(pages);
    cout<<"Enter sequence of pages: "<<endl;
    for(int i=0;i<pages;i++)
    {
        while(true)
        {
            cin>>vec[i];
            if(cin.fail() || vec[i] < 0)
            {
                cout<<"Enter a valid input!"<<endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else
                break;
        }
    }

    while(true)
    {
        cout<<"Enter number of frames: "<<endl;
        cin>>frames;
        if(cin.fail() || frames <= 0)
        {
            cout<<"Enter a valid input!"<<endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else
            break;
    }

    unordered_map<string,int> mp;

    mp["FCFS"] = fcfs(pages, vec, frames);
    mp["LRU"] = lru(pages, vec, frames);
    mp["Optimal"] = optimal(pages, vec, frames);

    auto min_page_faults = min_element(mp.begin(),mp.end(),[](auto& a,auto& b)
    {
        return a.second < b.second;
    });

    cout<<"\nMost Efficient Algorithm is: "<<min_page_faults->first<<" with "<<min_page_faults->second<<" faults."<<endl;

    return 0;

}