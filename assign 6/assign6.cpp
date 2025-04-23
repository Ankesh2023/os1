#include<bits/stdc++.h>
using namespace std;

void displayAllocation(vector<int>&process, vector<int>&allocation, int np){
    cout<<"\nProcess No. \tProcessSize \tBlockSize\n";
    for(int i=0; i<np; i++){
        cout<<(i+1)<<"\t\t"<<process[i]<<"\t\t";
        (allocation[i]==-1?cout<<"No Allocation": cout<<allocation[i]+1);
        cout<<"\n";
    }
    cout<<"\n\n";
}

void firstFit(vector<int>block, vector<int>process, int nb, int np){
    vector<int>allocation(np, -1);
    cout<<"FirstFit\n";
    for(int i=0; i<np; i++){
        //for each process check if it can be allocated to 
        for(int j=0; j<nb; j++){
            if(block[j]>=process[i]){
                block[j]-=process[i];
                allocation[i] = j;
                break;
            }
        }
    }

    displayAllocation(process, allocation, np);
}

void nextFit(vector<int>block, vector<int>process, int nb, int np){
    vector<int>allocation(np, -1);
    int j=0;
    cout<<"NextFit\n";
    for(int i=0; i<np; i++){
        //for each process check if it can be allocated to 
        int cnt=0;
        while(cnt<nb){ //at max we scan all the blocks for checking if available space for the process ~ to for loop
            if(block[j]>=process[i]){
                allocation[i] = j;
                block[j] = block[j] - process[i];
                j=(j+1)%nb;
                break;
            }
            cnt++;
            j= (j+1)%nb;
        }
    }

    displayAllocation(process, allocation, np);
}


void bestFit(vector<int>block, vector<int>process, int nb, int np){
    vector<int>allocaton(np, -1);
    cout<<"Best Fit\n";
    for(int i=0; i<np; i++){
        int ind = -1;
        //find the best fit for process[i]
        for(int j=0; j<nb; j++){
            if(block[j]>=process[i]){
                if(ind==-1 || block[j]<block[ind]){
                    ind= j;
                }
            }
        }
        if(ind!=-1){
            block[ind] = block[ind]-process[i];
            allocaton[i] = ind;
        }
    }

    displayAllocation(process, allocaton, np);
}

void worstFit(vector<int>block, vector<int>process, int nb, int np){
    vector<int>allocation(np, -1);
    cout<<"Worst Fit"<<endl;
    for(int i=0; i<np; i++){
        int ind=-1;
        for(int j=0; j<nb; j++){
            if(block[j]>=process[i]){
                if(ind==-1 || block[ind]<block[j]){
                    ind = j;
                }
            }
        }
        if(ind!=-1){
            allocation[i]= ind;
            block[ind] -=process[i];
        }
    }
    displayAllocation(process,allocation, np);
}

int main(){
    int nb, np;
    cout<<"Enter no of memory blocks: ";
    cin>>nb;
    vector<int>blockSize(nb);
    cout<<"Enter the block sizes: \n";
    for(int i=0; i<nb; i++){
        cin>>blockSize[i];
    }
    cout<<"Enter no of processes: ";
    cin>>np;
    cout<<"Enter the process sizes: \n";
    vector<int>processSize(np);
    for(int i=0; i<np; i++){
        cin>>processSize[i];
    }

    firstFit(blockSize, processSize, nb, np);
    nextFit(blockSize, processSize, nb, np);
    bestFit(blockSize, processSize, nb, np);
    worstFit(blockSize, processSize, nb, np);


    return 0;
}