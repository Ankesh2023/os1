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
    int priority;
};


void printps(int n, vector<process>p){
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

void ps(int n, vector<process> p)
{
    // lower priority number -> higher priority
    // if same priority then fcfs will be applied
    int curTime = 0;

    int cnt = 0;
    float twt = 0;
    float ttat =0;
    vector<bool> completed(n, false);

    while (cnt < n)
    {
        // find the process not completed and with the lowest priority number
        int idx = -1;
        int pr = INT_MAX;
        int lowestTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && p[i].arrivalTime <= curTime) {
                if (p[i].priority < pr) {
                    pr = p[i].priority;
                    idx = i;
                }
                else if (p[i].priority == pr) {
                    if (p[i].arrivalTime < p[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }
        

        // if(exist such process)
        if (idx != -1)
        {
            p[idx].completionTime = curTime + p[idx].burstTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            p[idx].responseTime = curTime - p[idx].arrivalTime;
            completed[idx] = true;
            cnt++;
            
            curTime+=p[idx].burstTime;
            ttat+=p[idx].turnaroundTime;
            twt+=p[idx].waitingTime;
            
        }

        // else if not exist
        else
        {
            curTime++;
        }
    }

    printps(n, p);
    cout << "\nAverage Waiting Time: " << twt / n << "\n";
    cout << "Average Turnaround Time: " << ttat / n << "\n";
}

int main()
{
    int n;
    cout << "Enter the no of processes: ";
    cin >> n;

    vector<process> p(n);
    for (int i = 0; i < n; i++)
    {
        // take inputs as ->at, bt for now;
        p[i].processNo = i + 1;
        cout << "Enter the arrival time of process" << (i + 1) << ": ";
        cin >> p[i].arrivalTime;

        cout << "Enter the burst time of process" << (i + 1) << ": ";
        cin >> p[i].burstTime;

        cout << "Enter the priority of process" << (i + 1) << ": ";
        cin >> p[i].priority;
    }

    ps(n, p);
    return 0;

    return 0;
}