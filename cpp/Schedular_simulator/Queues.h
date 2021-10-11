#ifndef QUEUES_H
#define QUEUES_H
#include "Process.h"
#define SIZE 2
class Queue{
    Process* processes;
    int noOfProcesses;
    int size;
    void resize();
public:
    Queue();
    Queue(const Queue& ref);
    Queue operator=(const Queue& ref);
    void addProcess(Process p);
    bool removeProcess(Process p);
    bool removeProcessAtIndex(int index);
    void sortProcessArrival();
    void addWaitingTime();
    static void sortByBurstTime(int initialIndex, int finalIndex, Queue& q);
    void sortProcessByBurstTime();
    bool isEmpty();
    void displayProcesses();
    int getNoOfProcesses();
    bool isProcessed(int n);
    Process& operator[] (int i);
    ~Queue();
};
#endif //QUEUES