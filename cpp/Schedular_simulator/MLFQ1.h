#ifndef MLFQ_H
#define MLFQ_H

#include <Windows.h>
#include "Queues.h"
#include "RoundRobin.h"
#include "SRTF.h"
#include<iomanip>

//global function
int getLength(int pid)
{
	int length = 0;
	while (pid != 0)
	{
		pid = pid / 10;
		length++;
	}
	return length;
}
class MLFQueue : public Queue
{
	RoundRobin queue0;
	RoundRobin queue1;
	SRTF queue2;

	int displayChart(Queue& gQ, int initialIndex, int finalIndex, int t)
	{
		int processCount = gQ.getNoOfProcesses();
		int temptime = t;
		for (int i = initialIndex; i <= finalIndex; i++)
		{
			Process p = gQ[i];
			int time = temptime;
			if (i == 0)
				cout << " ";
			for (int j = 0; time != 0; j++)
			{
				cout << " ";
				time = time/10;
			}
			if (p.getBurstTime() % 2 != 0)
				cout << " ";
			cout << setw((p.getBurstTime() / 2)+getLength(p.getProcessID())+1.0) << 'P' << p.getProcessID();
			cout << setw(p.getBurstTime() / 2) << "";
			if (p.getBurstTime() % 2 != 0)
				cout << " ";
			temptime += p.getBurstTime();
			time = t;

		}
		cout << "\n";
		temptime = t;
		if (temptime != 0)
		{
			int time = temptime;
			for (int i = 0; i < time; i++)
			{
				cout << "|";
				time =time/10;
			}
		}
		for (int i = initialIndex; i <= finalIndex; i++)
		{
			Process p = gQ[i];
			cout.fill('-');
			if (i == 0)
				cout << "|";
			if (p.getBurstTime() % 2 != 0)
				cout << "-";
			cout << setw(p.getBurstTime()+ getLength(p.getProcessID()) + 1.0) << "";
			temptime += p.getBurstTime();
			int time = temptime;
			for (int j = 0; time != 0; j++)
			{
				cout << "|";
				time = time/ 10;
			}
		}
		cout << "\n";
		temptime = t;
		if (temptime != 0)
		{
			cout << temptime;
		}
		for (int i = initialIndex; i <= finalIndex; i++)
		{
			Process p = gQ[i];
			cout.fill(' ');
			if (i == 0)
				cout << temptime;
			if (p.getBurstTime() % 2 != 0)
			{
				cout << " ";
			}
			cout << setw((p.getBurstTime()+ getLength(p.getProcessID()) + 1.0)) << "";
			temptime += p.getBurstTime();
			cout << temptime;
		}
		return temptime;
	}
	void displayQueues()
	{
		//i scaled 50ms to 5
		cout << "Process ID\tArrival Time\tBurst Time\n";
		for (int i = 0; i < getNoOfProcesses(); i++)
		{
			cout << "    " << (*this)[i].getProcessID() << "\t\t     " << (*this)[i].getArrivalTime()
				<< "\t\t    " << (*this)[i].getBurstTime() << "\n";
		}
		cout << "\nNo Of Processes:"<<getNoOfProcesses()<<'\n';
		cout << "Process Represtation: (PID:Starting:Burst)\n";
		cout << "Q2 (50 ms):";
		for (int i = 0; i < queue0.getNoOfProcesses(); i++)
		{
			cout << "(" << queue0[i].getProcessID()<< ":" << queue0[i].getArrivalTime() << ":" << queue0[i].getBurstTime();
			cout << ") |   ";
		}
		cout << "\n";
		cout << "Q1 (100 ms):";
		for (int i = 0; i < queue1.getNoOfProcesses(); i++)
		{
			cout << "(P" << queue1[i].getProcessID() << ":" << queue1[i].getArrivalTime() << ":" << queue1[i].getBurstTime();
			cout << ") |  ";
		}
		cout << "\n";
		cout << "Q2:";
		for (int i = 0; i < queue2.getNoOfProcesses(); i++)
		{
			cout << "(P" << queue2[i].getProcessID() << ":" << queue2[i].getArrivalTime() << ":" << queue2[i].getBurstTime();
			cout << ") |  ";
		}
	}

	void selectMinimumBurstProcess(int& queue2Itr)
	{
		int smallest = queue2[queue2Itr].getBurstTime();
		int index = queue2Itr;
		for (int i = queue2Itr; i < queue2.getNoOfProcesses(); i++)
		{
			if (smallest > queue2[i].getBurstTime())
			{
				smallest = queue2[i].getBurstTime();
				index = i;
			}
		}
		Process temp = queue2[index];
		queue2[index] = queue2[queue2Itr];
		queue2[queue2Itr] = temp;
	}

	void promoteToQueue0(int& queue1Itr, int& time)
	{
		while (queue1Itr < queue1.getNoOfProcesses() && queue1[queue1Itr].getArrivalTime() + 20 <= time)
		{
			Process p = queue1[queue1Itr];
			p.setArrivalTime(queue1[queue1Itr].getArrivalTime() + 20);
			queue0.addProcess(p);
			displayQueues();
			Sleep(1000);
			system("CLS");
			queue1.removeProcessAtIndex(queue1Itr);
			displayQueues();
			Sleep(1000);
			system("CLS");
		}
	}

	void promoteToQueue1(int& queue1Itr, int& queue2Itr, int& time)
	{
		while (queue2Itr < queue2.getNoOfProcesses() && queue2[queue2Itr].getArrivalTime() + 30 <= time)
		{
			Process p = queue2[queue2Itr];
			p.setArrivalTime(queue2[queue2Itr].getArrivalTime() + 30);
			queue1.addProcess(p);
			displayQueues();
			Sleep(1000);
			system("CLS");
			queue2.removeProcessAtIndex(queue2Itr);
			displayQueues();
			Sleep(1000);
			system("CLS");
		}
		promoteToQueue0(queue1Itr, time);
	}

	void runQueue0(int& RRIterator, Queue& ganttQueue, int& ganttIterator,
		int& time)
	{
		if (RRIterator < queue0.getNoOfProcesses())
		{
			Process p = queue0[RRIterator];
			p.setArrivalTime(time);
			ganttQueue.addProcess(p);
			int currProcessLeftBurst = queue0[RRIterator].getBurstTime();
			int currProcessDoneBurst = 0;
			time += queue0[RRIterator].getBurstTime();
			currProcessDoneBurst += currProcessLeftBurst;
			if (currProcessDoneBurst > queue0.getTimeQuantum())
			{
				currProcessDoneBurst = queue0.getTimeQuantum();
				currProcessLeftBurst -= queue0.getTimeQuantum();
				time -= currProcessLeftBurst;
				Process p = queue0[RRIterator];
				p.setBurstTime(currProcessLeftBurst);
				p.setArrivalTime(time);
				queue1.addProcess(p);
				displayQueues();
				Sleep(1000);
				system("CLS");
				ganttQueue[ganttIterator].setBurstTime(currProcessDoneBurst);
				queue0[RRIterator].setBurstTime(currProcessDoneBurst);
			}
			RRIterator++;
			ganttIterator++;
		}
	}

	void runQueue1(int& RRIterator, Queue& ganttQueue, int& ganttIterator,
		int& time)
	{
		if (RRIterator < queue1.getNoOfProcesses())
		{
			Process p = queue1[RRIterator];
			p.setArrivalTime(time);
			ganttQueue.addProcess(p);
			int currProcessLeftBurst = queue1[RRIterator].getBurstTime();
			int currProcessDoneBurst = 0;
			time += queue1[RRIterator].getBurstTime();
			currProcessDoneBurst += currProcessLeftBurst;
			if (currProcessDoneBurst > queue1.getTimeQuantum())
			{
				currProcessDoneBurst = queue1.getTimeQuantum();
				currProcessLeftBurst -= queue1.getTimeQuantum();
				time -= currProcessLeftBurst;
				Process p = queue1[RRIterator];
				p.setBurstTime(currProcessLeftBurst);
				p.setArrivalTime(time);
				queue2.addProcess(p);
				displayQueues();
				Sleep(1000);
				system("CLS");
				ganttQueue[ganttIterator].setBurstTime(currProcessDoneBurst);
				queue1[RRIterator].setBurstTime(currProcessDoneBurst);
			}
			RRIterator++;
			ganttIterator++;
		}
	}

	void runQueue2(int& SRTFIterator, Queue& ganttQueue, int& ganttIterator,
		int& time)
	{
		if (SRTFIterator < queue2.getNoOfProcesses())
		{
			selectMinimumBurstProcess(SRTFIterator);
			Process p = queue2[SRTFIterator];
			p.setArrivalTime(time);
			ganttQueue.addProcess(p);
			time += queue2[SRTFIterator].getBurstTime();
			SRTFIterator++;
			ganttIterator++;
		}
	}

	Queue runQueues()
	{
		sortProcessArrival();
		Queue ganttQueue;
		int queue0Iterator = 0, queue1Iterator = 0, queue2Iterator = 0, origIterator = 0, ganttIterator = 0;
		//int time = (*this)[0].getArrivalTime();
		int time = 0;
		while (origIterator < getNoOfProcesses() ||
			queue0Iterator < queue0.getNoOfProcesses() ||
			queue1Iterator < queue1.getNoOfProcesses() ||
			queue2Iterator < queue2.getNoOfProcesses())
		{
			while (origIterator < getNoOfProcesses() && (*this)[origIterator].getArrivalTime() <= time)
			{
				queue0.addProcess((*this)[origIterator]);
				displayQueues();
				Sleep(1000);
				system("CLS");
				origIterator++;
			}
			if (!(queue0.isEmpty()) && queue0Iterator < queue0.getNoOfProcesses())
			{
				runQueue0(queue0Iterator, ganttQueue, ganttIterator, time);
				promoteToQueue1(queue1Iterator, queue2Iterator, time);
			}
			else if (!(queue1.isEmpty()) && queue0Iterator == queue0.getNoOfProcesses()
				&& queue1Iterator != queue1.getNoOfProcesses())
			{
				runQueue1(queue1Iterator, ganttQueue, ganttIterator, time);
				promoteToQueue1(queue1Iterator, queue2Iterator, time);
			}
			else if (!(queue2.isEmpty()) && queue0Iterator == queue0.getNoOfProcesses()
				&& queue1Iterator == queue1.getNoOfProcesses() && queue2Iterator != queue2.getNoOfProcesses())
			{
				runQueue2(queue2Iterator, ganttQueue, ganttIterator, time);
				promoteToQueue1(queue1Iterator, queue2Iterator, time);
			}
			if (queue0Iterator == queue0.getNoOfProcesses()
				&& queue1Iterator == queue1.getNoOfProcesses()
				&& queue2Iterator == queue2.getNoOfProcesses()
				&& origIterator != (*this).getNoOfProcesses())
			{
				time = (*this)[origIterator].getArrivalTime();
			}
		}
		return ganttQueue;
	}

public:

	MLFQueue() : queue0(5), queue1(10)
	{}

	void displayGanttChart(int count)
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
			cout << "\n\n";
		}
		cout << "\n";
		//Creation of an array
		int** arr = new int* [count];
		for (int i = 0; i < count; i++)
		{
			arr[i] = new int[3];
			arr[i][0] = this->operator[](i).getProcessID();
			arr[i][1] = -1;
			arr[i][2] = 0;
		}
		for (int i = 0; i<ganttQueue.getNoOfProcesses(); i++)
		{
			if (ganttQueue[i].getProcessID() != -1)
			{
				bool flag = false;
				for (int j = 0; j < count && !flag; j++)
				{
					if (ganttQueue[i].getProcessID() == arr[j][0])
					{
						if (arr[j][1] != -1 && arr[j][1] > ganttQueue[i].getArrivalTime())
							arr[j][1] = ganttQueue[i].getArrivalTime();
						if (arr[j][2] < ganttQueue[i].getArrivalTime() + ganttQueue[i].getBurstTime())
							arr[j][2] = ganttQueue[i].getArrivalTime() + ganttQueue[i].getBurstTime();
						flag = true;
					}
				}
			}
		}
		double avgWait = 0;
		double avgturnaround = 0;
		cout << count;
		cout << "PID\t Arrival\tBurst\tTurnArround\tWaiting\n";
		for (int i = 0; i < count; i++)
		{
			cout << "P" << this->operator[](i).getProcessID() << "\t   " << this->operator[](i).getArrivalTime()
				<< "\t\t" << this->operator[](i).getBurstTime() << "\t    " << arr[i][2] - arr[i][1]-1- this->operator[](i).getArrivalTime() <<"\t\t  "
				<< arr[i][2] -arr[i][1]- this->operator[](i).getArrivalTime()-this->operator[](i).getBurstTime()-1<<'\n';
			avgturnaround += arr[i][2] - arr[i][1] - 1;
			avgWait += arr[i][2] - arr[i][1]- this->operator[](i).getArrivalTime() - this->operator[](i).getBurstTime() - 1;
		}
		avgWait = avgWait / count;
		avgturnaround = avgturnaround / count;
		cout << "\n";
		cout << "Average Wait:"<<avgWait<<'\n';
		cout << "Average TurnAround:" << avgturnaround;
	}
};
#endif //MLFQ