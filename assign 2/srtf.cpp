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

void printsrtf(int n, vector<process> p)
{
    cout << "Output table\n";

    cout << "Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time | Response Time\n";

    for (int i = 0; i < n; i++)
    {
        cout << " " << p[i].processNo << "\t\t" << p[i].arrivalTime << "\t\t"
             << p[i].burstTime << "\t\t"
             << p[i].completionTime << "\t\t"
             << p[i].turnaroundTime << "\t\t"
             << p[i].waitingTime << "\t\t"
             << p[i].responseTime << "\n";
    }
}

void srtf(int n, vector<process> p)
{

    vector<int> remainingBt(n), firstResp(n, -1);
    for (int i = 0; i < n; i++)
        remainingBt[i] = p[i].burstTime;

    // premptive is literally just the same we have same code its just that we check after every sec if process needs to be changed rather than keep it goingh

    int currTime = 0;
    // just changes is keeping track of curr time and how much bt is remaining and how many processes are done
    int count = 0;
    float totalwt = 0;
    float totaltat = 0;
    while (count < n)
    {
        // same as sjf find min burst time index
        int ind = -1;
        int minbt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (remainingBt[i] > 0 && p[i].arrivalTime <= currTime)
            {
                // it is eligible
                if (p[i].burstTime < minbt)
                {
                    minbt = p[i].burstTime;
                    ind = i;
                }
                else if (p[i].burstTime == minbt && p[i].arrivalTime < p[ind].arrivalTime)
                {
                    ind = i;
                }
            }
        }

        // this above for loop almost remains same in every code just minor changes like using remainingbt instead of checking if completed directly

        // we got the index to execute now lets execute
        if (ind != -1)
        {
            if (firstResp[ind] == -1)
            {
                firstResp[ind] = currTime;
            }

            remainingBt[ind]--;
            if (remainingBt[ind] == 0)
            {
                // if process completed then
                p[ind].completionTime = currTime + 1;
                p[ind].turnaroundTime = p[ind].completionTime - p[ind].arrivalTime;
                p[ind].waitingTime = p[ind].turnaroundTime - p[ind].burstTime;
                p[ind].responseTime = firstResp[ind] - p[ind].arrivalTime;
                totalwt += p[ind].waitingTime;
                totaltat += p[ind].turnaroundTime;
                count++;
            }
        }
        // if idle state or process not completed still increase time just by one -> maybe next step it will prempt
        currTime++;
    }

    printsrtf(n, p);
    cout << "\nAverage Waiting Time: " << totalwt / n << endl;
    cout << "Average Turnaround Time: " << totaltat / n << endl;
}

int main()
{
    int n;
    cout << "Enter no of processes: ";
    cin >> n;

    vector<process> p(n);
    for (int i = 0; i < n; i++)
    {

        p[i].processNo = i;
        cout << "Enter the arrival time of process" << (i + 1) << ": ";
        cin >> p[i].arrivalTime;

        cout << "Enter the burst time of process" << (i + 1) << ": ";
        cin >> p[i].burstTime;
    }

    // sjf is same
    srtf(n, p);
    return 0;
}