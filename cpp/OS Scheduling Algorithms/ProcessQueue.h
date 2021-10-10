#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Process.h"

class ProcessQueue {
    Process* processes;
    int processesNum;
    int processesSize;

    void resize()
    {
        Process* newArr = new Process[processesSize * 2];
        for (int i = 0; i < processesNum; i++) {
            newArr[i] = processes[i];
        }
        processes = newArr;
        processesSize = processesSize * 2;
    }

public:

    ProcessQueue()
    {
        processesNum = 0;
        processesSize = 5;
        processes = new Process[5];
    }

    ProcessQueue(const ProcessQueue& ref)
    {
        processesSize = ref.processesSize;
        processesNum = ref.processesNum;
        processes = new Process[processesSize];
        for (int i = 0; i < processesNum; i++)
        {
            processes[i] = ref.processes[i];
        }
    }

    ProcessQueue operator=(const ProcessQueue& ref)
    {
        if (this == &ref)
        {
            return *this;
        }
        if (processes)
        {
            this->~ProcessQueue();
        }
        processesSize = ref.processesSize;
        processesNum = ref.processesNum;
        processes = new Process[processesSize];
        for (int i = 0; i < processesNum; i++)
        {
            processes[i] = ref.processes[i];
        }
        return *this;
    }

    void add(Process p)
    {
        if (processesNum >= processesSize) {
            resize();
        }
            processes[processesNum] = p;
            processesNum++;
    }

    bool remove(Process p)
    {
        int index = -1;
        for (int i = 0; i < processesNum; i++)
        {
            if (processes[i] == p)
            {
                index = i;
            }
        }
        if (index == -1)
            return false;
        else
        {
            for (int i = index + 1; i < processesNum; i++)
            {
                processes[i - 1] = processes[i];
            }
            processesNum--;
            return true;
        }
    }

    bool remove(int index)
    {
        if (!(index >= 0 && index < processesNum))
            return false;
        else
        {
            for (int i = index + 1; i < processesNum; i++)
            {
                processes[i - 1] = processes[i];
            }
            processesNum--;
            return true;
        }
    }

    void sortProcessByArrivalTime()
    {
        int processCount = getProcessesCount();
        for (int i = 0; i < processCount; i++) {
            int smallest = (*this).operator[](i).getArrivalTime();
            int index = i;
            for (int j = i; j < processCount; j++) {
                if (smallest > (*this).operator[](j).getArrivalTime()) {
                    smallest = (*this).operator[](j).getArrivalTime();
                    index = j;
                }
            }
            Process temp = (*this).operator[](index);
            (*this).operator[](index) = (*this).operator[](i);
            (*this).operator[](i) = temp;
        }
    }

    void addIdleTime()
    {
        sortProcessByArrivalTime();
        int time = 0;
        int processCount = getProcessesCount();
        int newPCount = processCount;
        for (int i = 0; i < processCount; i++)
        {
            Process p = (*this).operator[](i);
            if (p.getArrivalTime() > time)
            {
                add(Process("IDLE", p.getArrivalTime() - time, time));
                time += p.getBurstTime();
                time += (*this).operator[](newPCount).getBurstTime();
                newPCount++;
            }
            else
                time += p.getBurstTime();
        }
    }

    static void sortByBurstTimeFromIndex(int start, int last, ProcessQueue& arr)
    {
        for (int i = start; i <= last; i++)
        {
            int smallest = arr[i].getBurstTime();
            int index = i;
            for (int j = i; j <= last; j++)
            {
                if (smallest > arr[j].getBurstTime())
                {
                    smallest = arr[j].getBurstTime();
                    index = j;
                }
            }
            Process temp = arr[index];
            arr[index] = arr[i];
            arr[i] = temp;
        }
    }

    void sortProcessByBurstTime()
    {
        int processCount = getProcessesCount();
        int time = 0;
        for (int k = 0; k < processCount; k++)
        {
            for (int i = k; i < processCount && (*this).operator[](i).getArrivalTime() <= time; i++) {
                int smallest = (*this).operator[](i).getBurstTime();
                int index = i;
                for (int j = i; j < processCount && (*this).operator[](j).getArrivalTime() <= time; j++) {
                    if (smallest > (*this).operator[](j).getBurstTime()) {
                        smallest = (*this).operator[](j).getBurstTime();
                        index = j;
                    }
                }
                Process temp = (*this).operator[](index);
                (*this).operator[](index) = (*this).operator[](i);
                (*this).operator[](i) = temp;
            }
            time += (*this).operator[](k).getBurstTime();
        }
    }

    bool isEmpty()
    {
        return !(processesNum);
    }

    void displayProcesses()
    {
        for (int i = 0; i < processesNum; i++) {
            cout << "Process Name: " << processes[i].getProcessName() << " Process Burst Time: " << 
            processes[i].getBurstTime() << " Process Arrival Time: " << processes[i].getArrivalTime() << "\n";
        }
        cout << "\n";
    }

    int getProcessesCount()
    {
        return processesNum;
    }

    bool isProcessed(int n)
    {
        if (n == processesNum)
            return true;
        return false;
    }

    Process& operator[] (int i)
    {
        if(i >= 0 && i < processesNum)
            return processes[i];
        else
            throw exception();
    }

    ~ProcessQueue()
    {
        if (processes)
        {
            delete[] processes;
        }
        processesNum = 0;
        processesSize = 0;
    }

};

#endif