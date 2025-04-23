#include<bits/stdc++.h>
using namespace std;


void bankers(vector<vector<int>>max, vector<vector<int>>alloc, int n, int m, vector<vector<int>>available){
    vector<vector<int>>need(n, vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    vector<int>safeSeq(n);
    vector<int>work(n);
    for(int i=0; i<m; i++){
        work[i] = available[0][i];
    }
    vector<bool>finish(n,false);

    int cnt=0;
    // int k=1;
    while(cnt<n){
        bool found = false;
        for(int i=0; i<n; i++){
           
            if(!finish[i]){
                bool canAllocate = true;
                for(int j=0; j<m; j++){
                    if(need[i][j] >work[j]){
                        canAllocate=false;
                        break;
                    }
                }

                if(canAllocate){
                    found=true;
                    for(int j=0; j<m; j++){
                        work[j]+=alloc[i][j];
                        available[cnt+1][j]= work[j];
                    }
                    safeSeq[cnt++]= i;
                    finish[i]=true;
                }
            }

        }
        if(!found)break;
    }
    if(cnt<n){
        cout<<"Safe state not found\n";
    }
    else{
        cout<<"ALLOCATION\tMAX\t\tAvailable\t\tNEED\n";

        for(int i=0; i<=n; i++){
            if(i<n){
                for(int j=0; j<m; j++){
                    cout<<alloc[i][j]<<" ";
                }

            }
            cout<<"\t\t";
            if(i<n){
                for(int j=0; j<m; j++){
                    cout<<max[i][j]<<" ";
                }

            }
            cout<<"\t\t";

            for(int j=0; j<m; j++){
                cout<<available[i][j]<<" ";
            }
            cout<<"\t\t";
            if(i<n){
                for(int j=0; j<m; j++){
                    cout<<need[i][j]<<" ";
                }

            }
            cout<<"\n";
        }
        cout<<"The safe sequence is: ";
        for(int i=0; i<n; i++){
            cout<<safeSeq[i]<<"->";
        }
    }


}
int main(){
    int n;
    cout<<"Enter the no of process: ";

    cin>>n;

    int r;
    cout<<"Enter the no of resources: ";
    cin>>r;

    vector<vector<int>>max(n, vector<int>(r));
    cout<<"Enter the max matrix: ";
    for(int i=0; i<n; i++){
        for(int j=0; j<r; j++){
            cin>>max[i][j];
        }
    }
vector<vector<int>>alloc(n, vector<int>(r));
    cout<<"Enter the allocation matrix: ";
    for(int i=0; i<n; i++){
        for(int j=0; j<r; j++){
            cin>>alloc[i][j];

        }
    }

    vector<vector<int>>available(n+1, vector<int>(r));
    cout<<"Enter the available resources: ";
    for(int i=0; i<r;i++)cin>>available[0][i];

   

bankers(max, alloc, n, r, available);


    return 0;
}