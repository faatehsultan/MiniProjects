#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string.h>
using namespace std;

class Process
{
    string processName;
    int burstTime;
    int arrivalTime;

public:
    Process()
    {
        processName = "";
        burstTime = 0;
        arrivalTime = 0;
    }

    Process(string name, int burst, int arrival)
    {
        setProcessName(name);
        setBurstTime(burst);
        setArrivalTime(arrival);
    }

    int getArrivalTime()
    {
        return arrivalTime;
    }

    void setArrivalTime(int arrivalTime)
    {
        if(arrivalTime >= 0)
            (*this).arrivalTime = arrivalTime;
    }

    string getProcessName()
    {
        return processName;
    }

    void setProcessName(string processName)
    {
        (*this).processName = processName;
    }

    int getBurstTime()
    {
        return burstTime;
    }

    void setBurstTime(int burstTime)
    {
        if(burstTime > 0)
            (*this).burstTime = burstTime;
    }

    bool operator==(Process p)
    {
        if (processName == p.processName &&
            burstTime == p.burstTime &&
            arrivalTime == p.arrivalTime)
        {
            return true;
        }
        return false;
    }

};

#endif