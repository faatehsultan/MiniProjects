#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
using namespace std;
class Process
{
public:
    int pid, arrival_time, burst_time;
public:
    Process();
    Process(int id, int burst, int arrival);
    int getArrivalTime();
    void setArrivalTime(int arrival);
    int getProcessID();
    void setProcessID(int pid);
    int getBurstTime();
    void setBurstTime(int burst);
    bool isEqual(Process p);
};
#endif