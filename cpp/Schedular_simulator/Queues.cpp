#include"Queues.h"
void Queue::resize()
{
    size = size * 2;
    Process* newArr = new Process[size];
    for (int i = 0; i < noOfProcesses; i++) {
        newArr[i] = processes[i];
    }
    processes = newArr;
}
Queue::Queue()
{
    noOfProcesses = 0;
    size = SIZE;
    processes = new Process[size];
}
Queue::Queue(const Queue& ref)
{
    size = ref.size;
    noOfProcesses = ref.noOfProcesses;
    processes = new Process[ref.size];
    for (int i = 0; i < noOfProcesses; i++)
    {
       processes[i] = ref.processes[i];
    }
}
Queue Queue::operator=(const Queue& ref)
{
   if (this == &ref)
        return *this;
  if (processes==nullptr)
          this->~Queue();
     size = ref.size;
     noOfProcesses = ref.noOfProcesses;
     processes = new Process[ref.size];
     for (int i = 0; i < noOfProcesses; i++)
     {
         processes[i] = ref.processes[i];
     }
     return *this;
}
void Queue::addProcess(Process p)
{
   if (noOfProcesses >= size)
        resize();
   processes[noOfProcesses] = p;
   noOfProcesses++;
}
bool Queue::removeProcess(Process p)
{
    int index = -1;
    bool flag = false;
    for (int i = 0; i < noOfProcesses && !flag; i++)
    {
        if (processes[i].isEqual(p))
           index = i;
    }
    if (!flag)
        return flag;
   else
   {
      for (int i = index + 1; i < noOfProcesses; i++)
      {
          processes[i - 1] = processes[i];
      }
      noOfProcesses--;
      return flag;
   }
}
bool Queue::removeProcessAtIndex(int index)
{
   if (!(index >= 0 && index < noOfProcesses))
        return false;
   for (int i = index + 1; i < noOfProcesses; i++)
        processes[i - 1] = processes[i];
   noOfProcesses--;
   return true;
}

void Queue::sortProcessArrival()
{
   int numberOfProcesses = noOfProcesses;
   for (int i = 0; i < numberOfProcesses; i++)
   {
      int smallest = processes[i].getArrivalTime();
      int index = i;
      for (int j = i; j < numberOfProcesses; j++)
      {
         if (smallest > processes[j].getArrivalTime())
         {
            smallest = processes[j].getArrivalTime();
            index = j;
         }
      }
      Process temp = processes[index];
      processes[index] = processes[i];
      processes[i] = temp;
   }
}
void Queue::addWaitingTime()
 {
   sortProcessArrival();
   int waitTime = 0;
   int proCount = noOfProcesses;
   int count = proCount;
   for (int i = 0; i < proCount; i++)
   {
      Process pro = processes[i];
      if (pro.getArrivalTime() > waitTime)
      {
          //-1 shows here idle process
          addProcess(Process(-1, pro.getArrivalTime() - waitTime, waitTime));
          waitTime += pro.getBurstTime();
          waitTime += processes[count].getBurstTime();
          count++;
      }
      else
         waitTime += pro.getBurstTime();
   }
}
void Queue::sortByBurstTime(int initialIndex, int finalIndex, Queue& q)
{
   for (int i = initialIndex; i <= finalIndex; i++)
   {
      int smallest = q[i].getBurstTime();
      int index = i;
      for (int j = i; j <= finalIndex; j++)
      {
         if (smallest > q[j].getBurstTime())
         {
                    smallest = q[j].getBurstTime();
                    index = j;
         }
      }
      Process temp = q[index];
      q[index] = q[i];
      q[i] = temp;
     }
}
void Queue::sortProcessByBurstTime()
{
   int proCount = noOfProcesses;
   int time = 0;
   for (int k = 0; k < proCount; k++)
   {
      for (int i = k; i < proCount && processes[i].getArrivalTime() <= time; i++)
      {
        int smallest = processes[i].getBurstTime();
        int index = i;
        for (int j = i; j < proCount && processes[j].getArrivalTime() <= time; j++)
        {
          if (smallest > processes[j].getBurstTime())
          {
              smallest = processes[j].getBurstTime();
              index = j;
          }
        }
      Process temp = processes[index];
      processes[index] = processes[i];
      processes[i] = temp;
      }
            time += processes[k].getBurstTime();
   }
}
bool Queue::isEmpty()
{
   if (noOfProcesses == 0)
       return true;
   return false;
}
void Queue::displayProcesses()
{
    for (int i = 0; i < noOfProcesses; i++)
    {
       cout << "PID: " << "P" << processes[i].getProcessID() << "Burst Time: " << processes[i].getBurstTime()
        << "Arrival Time: " << processes[i].getArrivalTime() << "\n";
    }
    cout << "\n";
}
int Queue::getNoOfProcesses()
{
     return noOfProcesses;
}
bool Queue::isProcessed(int n)
{
    if (n == noOfProcesses)
        return true;
    return false;
}
Process& Queue::operator[] (int i)
{
   if (i >= 0 && i < noOfProcesses)
       return processes[i];
   exit(0);
}
Queue::~Queue()
{
    noOfProcesses = 0;
    size = 0;
    if (processes != nullptr)
        delete[] processes;
}