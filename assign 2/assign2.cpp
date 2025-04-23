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

bool comp(process a, process b ){
    //process a as our variables are in struct and their dtatype is process
    return a.arrivalTime<b.arrivalTime; //return true else false;

}

 void printFcfs(int n, vector<process>p){
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
void fcfs(int n, vector<process>p){
    //we need to find average wt
    //wt = tat-bt
    //but tat = ct-at;

    // so we need to find ct first 
    //fifo the first process goes to complete its execution first so we need to sort all the process in order of thei arrival time

    sort(p.begin(), p.end(), comp); //comp is a comparator function here we used it to sort based on the arrival time
    //now the ct
    p[0].completionTime = p[0].arrivalTime + p[0].burstTime; //0th process it is straight forward it came and did
    for(int i=1; i<n; i++){
        p[i].completionTime =max(p[i-1].completionTime , p[i].arrivalTime) + p[i].burstTime;
        //take max in case if someone arrives too late and there is gap between processes
    }
//tat
float twt=0;
    for(int i=0; i<n; i++){
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
        p[i].responseTime = p[i].waitingTime;
        twt+=p[i].waitingTime;
    }

    //print
    printFcfs(n, p);
cout<<"\nAverage waiting time is: "<<(twt)/n<<"\n";


}


void sjf(int n, vector<process>p){
    vector<bool>completed(n, false);
   int cnt=0;
    int curTime= 0;
    float twt =0;
    //some process may not have arrived so we keep current time to keep the track of which process have arrived and which not
   while (cnt<n)
   {
        int minBurst = INT_MAX;
        int ind= -1;
        //we find the process with min burst time

        for (int i=0; i<n; i++){
            if(!completed[i] && p[i].arrivalTime<=curTime){
                if(p[i].burstTime< minBurst){
                    minBurst = p[i].burstTime;
                    ind = i;
                }
                else if(p[i].burstTime == minBurst && p[i].arrivalTime < p[ind].arrivalTime){
                    ind = i;
                    minBurst = p[i].burstTime;
                }
            }
        }

        if(ind==-1)//no process found 
        {
            curTime++;
        }
        else {
            completed[ind] = true;
            cnt++;

            p[ind].completionTime  = curTime + p[ind].burstTime;
            p[ind].turnaroundTime = p[ind].completionTime - p[ind].arrivalTime;
            p[ind].waitingTime = p[ind].turnaroundTime - p[ind].burstTime;
            p[ind].responseTime = p[ind].waitingTime;
            twt+=p[ind].waitingTime;


            curTime+=p[ind].burstTime;
        }

   }

   printFcfs(n, p);
   cout<<"\nAvg wt is: "<<twt/n;
   

}
int main(){

    int n;
    cout<<"Enter the no of processes: ";
    cin>>n;

vector<process>p(n);
for(int i=0; i<n; i++){
    //take inputs as ->at, bt for now;
    p[i].processNo = i;
    cout<<"Enter the arrival time of process"<<(i+1)<<": ";
    cin>>p[i].arrivalTime;

    cout<<"Enter the burst time of process"<<(i+1)<<": ";
    cin>>p[i].burstTime;
}

fcfs(n, p);


//sjf is same
sjf(n, p);

return 0;
}