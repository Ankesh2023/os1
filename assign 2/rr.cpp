#include <bits/stdc++.h>
using namespace std;
 
struct process
{
    int processNo;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};



void printRR(int n, vector<process>p){
    cout<<"Output table\n";

    cout<<"Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time | Response Time\n";

    for(int i=0; i<n; i++){
        cout<<" "<<p[i].processNo <<"\t\t"<< p[i].arrivalTime << "\t\t"
            <<p[i].burstTime<<"\t\t"
            <<p[i].completionTime<<"\t\t"
            <<p[i].turnaroundTime<<"\t\t"
            <<p[i].waitingTime<<"\t\t"
            <<p[i].responseTime<<"\n";
            
    }
 }
 void rr(int n, int q, vector<process> p){
    vector<int>remainingBurst(n);
    vector<bool>firstResp(n, true);

    for (int i = 0; i < n; i++) {
        remainingBurst[i] = p[i].burstTime;
    }

    int cnt=0, curTime =0;

    while(cnt<n){
        bool noProcess=true;
        for(int i=0; i<n; i++){
            if(remainingBurst[i]>0 && p[i].arrivalTime<=curTime){
                noProcess=false;
                if(firstResp[i]){
                    p[i].responseTime = curTime - p[i].arrivalTime;
                    firstResp[i] = false;
                }

                if(remainingBurst[i]>q){
                    remainingBurst[i]-=q;
                    curTime+=q;
                } else {
                    curTime+=remainingBurst[i];
                    p[i].completionTime = curTime;
                    cnt++;
                    remainingBurst[i]=0;
                }
            }
        }
        if(noProcess) curTime++;
    }

    for(int i=0; i<n; i++){
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
    }

    printRR(n, p);

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
    }
    cout << "\nAverage Waiting Time: " << totalWT / n << "\n";
    cout << "Average Turnaround Time: " << totalTAT / n << "\n";
}


int main(){

    int n;
    cout<<"Enter the no of processes: ";
    cin>>n;


vector<process>p(n);
for(int i=0; i<n; i++){
    //take inputs as ->at, bt for now;
    p[i].processNo = i+1;
    cout<<"Enter the arrival time of process"<<(i+1)<<": ";
    cin>>p[i].arrivalTime;

    cout<<"Enter the burst time of process"<<(i+1)<<": ";
    cin>>p[i].burstTime;
}
    
int q;
cout<<"Enter the time quantum: ";
cin>>q;

rr(n,q,  p);
return 0;
}