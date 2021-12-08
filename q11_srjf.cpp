//sjf algorithm(arrival time 0)

#include <iostream>
#include <algorithm>
using namespace std;

//class process;
class Process{
    
    public:
        int pid;
        int bt;
        int wt;
        int tat;
        int art;
        int rmbt;
        bool operator<(Process b);
};

//sort process in order of remaining burst time
bool Process::operator<(Process b){
    return (this->rmbt<b.rmbt);
}

//srjf()
void srjf(Process p[],int n){
    
    int completed = 0; //initial no process is completed
    int current_time = 0; //begin at time t = 0;
    int i;
    //while all process not get completed
    while(completed!=n){
        Process q[n];  //ready queue at current time
        int l=0;
        for(int i=0; i<n; i++){
            if(p[i].art<=current_time && p[i].rmbt!=0)
                q[l++] = p[i];
        }
        if(l){
            sort(q,q+l); //sort processes in ready queue in order , shortest remaining time at index 0
            for(i=0; i<n; i++){
                if(p[i].pid == q[0].pid){
                    p[i].rmbt--;
                    current_time++;
                    break;
                }
            }
        }

        //check if process completed
        if(p[i].rmbt==0){
            completed++;
            //turn around time
            p[i].tat = (current_time)-p[i].art;
        }
    }
    //waiting time
    for(i=0; i<n; i++){
        p[i].wt = p[i].tat-p[i].bt;
    }
}

//main function
int main(){
    int n;
    float avg_wt,avg_tat;
    cout<<"\nEnter number of Process: ";
    cin>>n;
    Process p[n];

    cout<<"\nEnter Burst time for each Process:\n";
    for(int i=0; i<n; i++){
        p[i].pid = (i+1);
        cout<<"Process P"<<(i+1)<<" : ";
        cin>>p[i].bt;
        p[i].rmbt = p[i].bt;
        p[i].tat = 0;
    }
    cout<<"\nEnter Arrival time for each Process:\n";
    for(int i=0; i<n; i++){
        cout<<"Process P"<<(i+1)<<" : ";
        cin>>p[i].art;
    }
    
    srjf(p,n);
    cout<<"\n\nProcess\tArrival time\tBurst time\tWaiting time\tTurn around time\n";
    for(int i=0; i<n; i++){
        cout<<p[i].pid<<"\t\t"<<p[i].art<<"\t\t"<<p[i].bt<<"\t\t"<<p[i].wt<<"\t\t"<<p[i].tat<<"\n";
        avg_wt+=p[i].wt;
        avg_tat+=p[i].tat;
    }

    avg_wt/=n;
    avg_tat/=n;

    cout<<"\n\nAverage waiting time:  "<<avg_wt;
    cout<<"\nAverage turn around time:  "<<avg_wt;

    return 0;
}