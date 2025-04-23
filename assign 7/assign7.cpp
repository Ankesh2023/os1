#include<iostream>
#include<algorithm>
#include<cmath>
#include<climits>
#include<vector>

//or use 
#include<bits/stdc++.h>
using namespace std;


//lru and optimal is left -> 
void printFrames(int frameArr[], int frames){
    cout<<"[";
    for(int i=0; i<frames; i++){
        if(frameArr[i]==-1){
            //no page present
            cout<<" ,";
        }
        else{
            // cout<<frameArr[i]<<",";
            cout<<frameArr[i]<<(i==frames-1? "": ",");
        }

    }
    cout<<"]";
    cout<<"\n";
}


int fcfs(int frames, int pages[], int n){
    int ind=0;
    int faults=0;
    unordered_set<int>st; //can use set<int>st;
    int framesArr[frames];
    // Initialize frame array
    for (int i = 0; i < frames; i++)
        framesArr[i] = -1;
cout<<"FCFS algorithm is: \n";

    for(int i=0; i<n; i++){
        //if page value present in set -> it is a hit
        if(st.find(pages[i]) != st.end()){
            printFrames(framesArr, frames);
        }
        //if not present then it is a fault and we need to see if 
        else{
            faults++;
            //if frame is full then replace
            if(st.size()==frames){
                st.erase(framesArr[ind]);
            }
            st.insert(pages[i]);
            framesArr[ind] = pages[i];
            ind= (ind+1)%frames; //% so that it traces back to first index after reaching last
            printFrames(framesArr, frames);
        }
    }

    return faults;

}

int lru(int frames, int pages[], int n){
    int faults=0;
    int ind=0;
    int framesArr[frames];
    for(int i=0; i<frames; i++) framesArr[i]= -1;

    unordered_map<int, int>mpp; //page, last used ind
    cout<<"LRU algorithm is: \n";
    for(int i=0; i<n; i++){
        if(mpp.find(framesArr[i])!=mpp.end()){
            printFrames(framesArr, frames);
        }

        else{
            faults++;
            
        }
    }
}
int main(){
    int frames;
    cout<<"Enter the no of frames: ";
    cin>>frames;

    int n;
    cout<<"Enter the no of page references: ";
    cin>>n;
    int pages[n];
    cout<<"Enter the page references: \n";
    for(int i=0; i<n; i++){
        cin>>pages[i];
    }

    unordered_map<string, int>mpp;
    mpp["FCFS"] = fcfs(frames,pages, n);
    mpp["LRU"] = lru(frames, pages, n);
    vector<pair<string, int>> vec(mpp.begin(), mpp.end());

    // Sort by increasing values
    sort(vec.begin(), vec.end(),
     [](const pair<string, int>&a, const pair<string, int>& b){
        return a.second<b.second;
     });

    // Print the sorted pairs
    for (const auto& entry : vec) {
        cout << entry.first << "has -> " << entry.second << " page faults" << endl;
    }

    return 0;
}