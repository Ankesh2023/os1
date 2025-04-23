#include<iostream>
#include<algorithm>
#include<cmath>
#include<climits>
#include<vector>
#include<cstdlib>
using namespace std;


int max_range;

void fifo(int requests[], int head, int n){
    // Algorithm: 

    //     Let Request array represents an array storing indexes of tracks that have been requested in ascending order of their time of arrival. ‘head’ is the position of disk head.
    //     Let us one by one take the tracks in default order and calculate the absolute distance of the track from the head.
    //     Increment the total seek count with this distance.
    //     Currently serviced track position now becomes the new head position.
    //     Go to step 2 until all tracks in request array have not been serviced.

    int seek_time=0;
    cout<<"fifo order: "<<head;
    for(int i=0; i<n;i++){
        seek_time+=abs(requests[i] - head);
        head= requests[i]; //update the head
        cout<<" "<<head;
    }
    cout<<"\nTotal seek time is: "<<seek_time<<endl<<endl;
}


//the tracks that are closer to the current disk head position should be serviced first in order to minimize the seek operations
//https://www.geeksforgeeks.org/program-for-sstf-disk-scheduling-algorithm/?ref=ml_lbp
void sstf(int requests[], int head, int n){
    int seek_time=0;
    bool visited[n]={false};
    cout<<"sstf order: "<<head;

    for(int i=0; i<n;i++){
        //first find the next minimum seek time possible
        int min_dis=INT_MAX;
        int index = -1;
        for(int j=0; j<n; j++){
            if(!visited[j] && abs(requests[j]- head)<min_dis){
                min_dis = abs(requests[j]- head);
                index = j;

            }
        }

        //we got the index of min distance value now do the next steps
        seek_time+= abs(requests[index] - head);
        head= requests[index];//update the head
        visited[index]= true;
        cout<<" "<<head;
    }
    cout<<"\nTotal seek time is: "<<seek_time<<endl<<endl;
}






//the head starts from one end of the disk and moves towards the other end, 
//servicing requests in between one by one and reaching the other end. Then the direction
// of the head is reversed and the process continues as the head continuously scans back and forth to access the disk.
void scan(int requests[], int head, int n){
   //store all the smaller values than head in let array and all the bigg values in right array
    vector<int>left, right;
    int seek_time=0;
    cout<<"scan order: "<<head;

    for(int i=0; i<n; i++){
        if(requests[i]<head){
            left.push_back(requests[i]);
        }
        else{
            right.push_back(requests[i]);
        }
    }
//sort both the vectors so it follows proper direction while going
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    //in this code i go right first
    for(int i=0; i<right.size(); i++){
        seek_time+=abs(right[i] - head);
        head= right[i]; //update the head
        cout<<" "<<head;
    }
    //at end go to extreme value to start iterating to left
    seek_time+=abs(max_range-head);
    head= max_range;
    //while going left we traverse from right ot left so left array will be iterated in reverse order
    for(int i=left.size()-1; i>=0; i--){
        seek_time+=abs(left[i] - head);
        head= left[i]; //update the head
        cout<<" "<<head;
    }

    cout<<"\nTotal seek time is: "<<seek_time<<endl<<endl;
}









//cscan like maam did
//https://www.geeksforgeeks.org/difference-between-scan-and-cscan-disk-scheduling-algorithms/
void cscan(int requests[], int head, int n){
    vector<int>left, right;
    int seek_time=0;
    cout<<"scan order: "<<head;

    for(int i=0; i<n; i++){
        if(requests[i]<head){
            left.push_back(requests[i]);
        }
        else{
            right.push_back(requests[i]);
        }
    }
//sort both the vectors so it follows proper direction while going
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int r = right.size();
    int l = left.size();
    if(r>=l){
        //go to right first
        for(int i=0; i<r; i++){
            seek_time+=abs(right[i] - head);
            head= right[i]; //update the head
            cout<<" "<<head;
        }
        seek_time+=abs(max_range-head);//go to end
        seek_time+=max_range; //go to start
        head= 0;

        //starting from start so left to right
        for(int i=0; i<l; i++) {
            seek_time+=abs(left[i] - head);
            head= left[i]; //update the head
            cout<<" "<<head;
        }
    }
    else{

        //go left first .. we go towards 0 from head so in reverse order 
        for(int i=l-1; i>=0; i--){
            seek_time+=abs(left[i] - head);
            head= left[i]; //update the head
            cout<<" "<<head;
        }
        seek_time+=abs(head-0);
        seek_time+=max_range;
        head = max_range;

        //now we at right most end so to go back we travel right to left again so reverse traversal in right array
        for(int i=r-1; i>=0; i--){
            seek_time+=abs(head- right[i]);
            head= right[i];
            cout<<" "<<head;
        }
    }

    
    cout<<"\nTotal seek time is: "<<seek_time<<endl<<endl;

}

int main(){

    int n, head;
     max_range = 59;
    cout<<"Enter no of disk requests: ";
    cin>>n;

    int requests[n];
    cout<<"Enter the disk requests in range (0 to "<<max_range<<"): "<<endl;
    for(int i=0; i<n; i++){
        cin>>requests[i];
    }
    cout<<"Enter the initial head position: ";
    cin>>head;

    fifo(requests, head, n);
    sstf(requests, head, n);
    scan(requests, head, n);
    cscan(requests, head, n);
    
    

    return 0;

}