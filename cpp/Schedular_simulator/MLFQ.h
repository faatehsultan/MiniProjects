#ifndef MLFQ_H
#define MLFQ_H
#include <Windows.h>
#include<iomanip>
#include "Queues.h"
#include "RoundRobin.h"
#include "SRTF.h"

class MLFQueue : public Queue
{
	//Three Queues to manage the processes 
	RoundRobin queue0;
	RoundRobin queue1;
	SRTF queue2;

	int displayChart(Queue& Q, int start, int end, int t)
	{
		int proCount = Q.getNoOfProcesses();
		int tempTime = t;
		for (int i = start; i <= end; i++)
		{
			Process p = Q[i];
			int time = tempTime;
			if (i == 0)
				cout << " ";
			for (int j = 0; time != 0; j++)
			{
				cout << " ";
				time /= 10;
			}
			if (p.getBurstTime() % 2 != 0)
				cout << " ";
			cout << setw((p.getBurstTime() / 2)) << p.getProcessID();
			cout << setw(p.getBurstTime() / 2) << "";
			if (p.getBurstTime() % 2 != 0)
				cout << " ";
			tempTime += p.getBurstTime();
			time = t;
		}
		cout << "\n";
		cout.fill('-');
		tempTime = t;
		if (tempTime != 0)
		{
			int time = tempTime;
			for (int i = 0; i < time; i++)
			{
				cout << "|";
				time = time/10;
			}
		}
		for (int i = start; i <= end; i++)
		{
			Process p = Q[i];
			if (i == 0)
				cout << "|";
			if (p.getBurstTime() % 2 != 0)
				cout << "-";
			cout << setw(p.getBurstTime()) << "";
			tempTime += p.getBurstTime();
			int time = tempTime;
			for (int j = 0; time != 0; j++)
			{
				cout << "|";
				time =time/10;
			}
		}
		cout << "\n";
		tempTime = t;
		if (tempTime != 0)
		{
			cout << tempTime;
		}
		for (int i = start; i <= end; i++)
		{
			Process p = Q[i];
			cout.fill(' ');
			if (i == 0)
				cout << tempTime;
			if (p.getBurstTime() % 2 != 0)
			{
				cout << " ";
			}
			cout << setw((p.getBurstTime())) << "";
			tempTime += p.getBurstTime();
			cout << tempTime;
		}
		return tempTime;
	}
	void displayQueues()
	{
		cout << "Process ID\tArrival Time\tBurst Time\n";
		for (int i = 0; i < getNoOfProcesses(); i++)
		{
			cout << "    P" <<this->operator[](i).getProcessID()<< "\t\t     " << this->operator[](i).getArrivalTime()
				<< "\t\t    " << (*this)[i].getBurstTime() << "\n";
		}
		cout << "\n";
		cout << " Q0 (50 ms): ";
		for (int i = 0; i < queue0.getNoOfProcesses(); i++)
		{
			if (queue0[i].getProcessID() == -1)
				cout << "i";//idle time
			else
			  cout << queue0[i].getProcessID();
			cout<< ":" << queue0[i].getArrivalTime() << ":" << queue0[i].getBurstTime();
			cout << "  ";
		}
		cout << "\n";
		cout << "Q1(100 ms): ";
		for (int i = 0; i < queue1.getNoOfProcesses(); i++)
		{
			cout <<'P'<< queue1[i].getProcessID() << ":" << queue1[i].getArrivalTime() << ":" << queue1[i].getBurstTime();
			cout << "  ";
		}
		cout << "\n";
		cout << "Q2(SRTF): ";
		for (int i = 0; i < queue2.getNoOfProcesses(); i++)
		{
			cout <<'P'<< queue2[i].getProcessID() << ":" << queue2[i].getArrivalTime() << ":" << queue2[i].getBurstTime();
			cout << "  ";
		}
	}
	void selectMinimumBurstProcess(int& itr)
	{
		//iterate Queue 2 to run the minimum remaining time process 
		int smallest = queue2[itr].getBurstTime();
		int index = itr;
		for (int i = itr; i < queue2.getNoOfProcesses(); i++)
		{
			if (smallest > queue2[i].getBurstTime())
			{
				smallest = queue2[i].getBurstTime();
				index = i;
			}
		}
		Process temp = queue2[index];
		queue2[index] = queue2[itr];
		queue2[itr] = temp;
	}
	void promoteToQueue0(int& itr, int& time)
	{
		while (itr < queue1.getNoOfProcesses() && queue1[itr].getArrivalTime() + 20 <= time)
		{
			Process p = queue1[itr];
			p.setArrivalTime(queue1[itr].getArrivalTime() + 20);
			queue0.addProcess(p);
			displayQueues();
			Sleep(2000);
			system("CLS");
			queue1.removeProcessAtIndex(itr);
			displayQueues();
			Sleep(2000);
			system("CLS");
		}
	}
	void promoteToQueue1(int& ind1, int& ind2, int& time)
	{
		while (ind2 < queue2.getNoOfProcesses() && queue2[ind2].getArrivalTime() + 30 <= time)
		{
			Process p = queue2[ind2];
			p.setArrivalTime(queue2[ind2].getArrivalTime() + 30);
			queue1.addProcess(p);
			displayQueues();
			Sleep(2000);
			system("CLS");
			queue2.removeProcessAtIndex(ind2);
			displayQueues();
			Sleep(2000);
			system("CLS");
		}
		promoteToQueue0(ind1, time);
	}
	
	void runProcessesOfQ0(int& index, Queue& q, int& ganttIterator, int& time)
	{
		if (index < queue0.getNoOfProcesses())
		{
			Process p = queue0[index];
			p.setArrivalTime(time);
			q.addProcess(p);
			int currProBurstleft = queue0[index].getBurstTime();
			int currProBurst = 0;
			time += queue0[index].getBurstTime();
			currProBurst += currProBurstleft;
			if (currProBurst > queue0.getTimeQuantum())
			{
				currProBurst = queue0.getTimeQuantum();
				currProBurstleft -= queue0.getTimeQuantum();
				time -= currProBurstleft;
				Process p = queue0[index];
				p.setBurstTime(currProBurstleft);
				p.setArrivalTime(time);
				queue1.addProcess(p);
				displayQueues();
				Sleep(1000);
				system("CLS");
				q[ganttIterator].setBurstTime(currProBurstleft);
				queue0[index].setBurstTime(currProBurstleft);
			}
			index++;
			ganttIterator++;
		}
	}
	void runProcessesOfQ1(int& index, Queue& q, int& ganttIterator,int& time)
	{
		if (index < queue1.getNoOfProcesses())
		{
			Process p = queue1[index];
			p.setArrivalTime(time);
			q.addProcess(p);
			int currProcessLeftBurst = queue1[index].getBurstTime();
			int currProcessDoneBurst = 0;
			time += queue1[index].getBurstTime();
			currProcessDoneBurst += currProcessLeftBurst;
			if (currProcessDoneBurst > queue1.getTimeQuantum())
			{
				currProcessDoneBurst = queue1.getTimeQuantum();
				currProcessLeftBurst -= queue1.getTimeQuantum();
				time -= currProcessLeftBurst;
				Process p = queue1[index];
				p.setBurstTime(currProcessLeftBurst);
				p.setArrivalTime(time);
				queue2.addProcess(p);
				displayQueues();
				Sleep(1000);
				system("CLS");
				q[ganttIterator].setBurstTime(currProcessDoneBurst);
				queue1[index].setBurstTime(currProcessDoneBurst);
			}
			index++;
			ganttIterator++;
		}
	}

	void runProcessesOfQ2(int& index, Queue& Q, int& ganttIterator, int& time)
	{
		if (index < queue2.getNoOfProcesses())
		{
			selectMinimumBurstProcess(index);
			Process pro = queue2[index];
			pro.setArrivalTime(time);
			Q.addProcess(pro);
			time += queue2[index].getBurstTime();
			index++;
			ganttIterator++;
		}
	}
	Queue runQueues()
	{
		sortProcessArrival();
		Queue ganttChartQueue;
		int q0index = 0, q1index = 0, q2index = 0;
		int realindex = 0, ganttindex = 0;
		int time = 0;
		while (realindex < getNoOfProcesses() ||q0index < queue0.getNoOfProcesses() ||q1index < queue1.getNoOfProcesses()
			|| q2index < queue2.getNoOfProcesses())
		{
			while (realindex < getNoOfProcesses() && (*this)[realindex].getArrivalTime() <= time)
			{
				queue0.addProcess((*this)[realindex]);
				displayQueues();
				Sleep(1000);
				system("CLS");
				realindex++;
			}
			if (!(queue0.isEmpty()) && q0index < queue0.getNoOfProcesses())
			{
				runProcessesOfQ0(q0index, ganttChartQueue, ganttindex, time);
				promoteToQueue1(q1index, q2index, time);
			}
			else if (!(queue1.isEmpty()) && q0index == queue0.getNoOfProcesses()
				&& q1index != queue1.getNoOfProcesses())
			{
				runProcessesOfQ1(q1index, ganttChartQueue, ganttindex, time);
				promoteToQueue1(q1index, q2index, time);
			}
			else if (!(queue2.isEmpty()) && q0index == queue0.getNoOfProcesses() && q1index ==
				queue1.getNoOfProcesses() && q2index != queue2.getNoOfProcesses())
			{
				runProcessesOfQ2(q2index, ganttChartQueue, ganttindex, time);
				promoteToQueue1(q1index, q2index, time);
			}
			if (q0index == queue0.getNoOfProcesses()
				&& q1index == queue1.getNoOfProcesses()
				&& q2index == queue2.getNoOfProcesses()
				&& realindex != getNoOfProcesses())
			{
				time = (*this)[realindex].getArrivalTime();
			}
		}
		return ganttChartQueue;
	}
public:
	//copy creation of the array for the chart
	MLFQueue() : queue0(5), queue1(10)
	{}
	void GanttChart()
	{
	    Queue ganttQueue = runQueues();
		displayQueues();
		cout << "\n\n";
		ganttQueue.addWaitingTime();
		ganttQueue.sortProcessArrival();
		int processCount = ganttQueue.getNoOfProcesses();
		int totalTime = 0;
		for (int i = 0; i < ganttQueue.getNoOfProcesses(); i++)
		{
			totalTime += ganttQueue[i].getBurstTime();
		}
		int time = 0;
		int startIndex = 0;
		int finishIndex = 0;
		while (time != totalTime)
		{
			bool stop = false;
			int tempTime = 0;
			for (int i = startIndex; i < processCount && !stop; i++)
			{
				if (tempTime + ganttQueue[i].getBurstTime() < 60)
				{
					finishIndex = i;
					tempTime += ganttQueue[i].getBurstTime();
				}
			}
			time = displayChart(ganttQueue, startIndex, finishIndex, time);
			startIndex = finishIndex + 1;
			cout << "\n";
		}
	}
};

#endif