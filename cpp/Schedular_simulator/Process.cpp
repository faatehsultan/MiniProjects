#include "Process.h"
Process::Process()
{
    pid = 0;
    burst_time = 0;
    arrival_time = 0;
}
Process::Process(int id, int burst, int arrival)
{
    setProcessID(id);
    setBurstTime(burst);
    setArrivalTime(arrival);
}

int Process::getArrivalTime()
{
    return arrival_time;
}

void Process::setArrivalTime(int arrival)
{
    if (arrival >= 0)
        arrival_time = arrival;
}
int Process::getProcessID()
{
    return pid;
}

void Process::setProcessID(int id)
{
    pid=id;
}
int Process::getBurstTime()
{
    return burst_time;
}

void Process::setBurstTime(int burst)
{
    if (burst > 0)
        burst_time = burst;
}

bool Process::isEqual(Process p)
{
    if (pid == p.pid && burst_time == p.burst_time && arrival_time == p.arrival_time)
        return true;
    return false;
}
