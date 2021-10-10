#ifndef M_L_F_QUEUE_H
#define M_L_F_QUEUE_H

#include "ProcessQueue.h"
#include "RR.h"
#include "SRTF.h"
#include <Windows.h>

class MLFQueue : public ProcessQueue
{
	RR queue0;
	RR queue1;
	SRTF queue2;

	void dumpGanttChartStats(ProcessQueue& ganttQueue)
	{
		cout << "Process ID\tArrival Time\tBurst Time\t Wait Time\tTurn Around Time\tResponse Time\n";
		int avgResponseTime = 0;
		int avgWaitingTime = 0;
		for (int i = 0; i < getProcessesCount(); i++)
		{
			string pName = (*this)[i].getProcessName();
			int arrivalTime = (*this)[i].getArrivalTime();
			int burstTime = (*this)[i].getBurstTime();
			int startTime = -1;
			int finalTime = 0;
			int time = 0;
			for (int j = 0; j < ganttQueue.getProcessesCount(); j++)
			{
				if (pName == ganttQueue[j].getProcessName())
				{
					if (startTime == -1)
					{
						startTime = time;
						finalTime = time + ganttQueue[j].getBurstTime();
					}
					else
						finalTime = time + ganttQueue[j].getBurstTime();
				}
				time += ganttQueue[j].getBurstTime();
			}
			int waitTime = finalTime - arrivalTime - burstTime;
			int turnAroundTime = finalTime - arrivalTime;
			int responseTime = startTime - arrivalTime;
			cout << "    " << pName << "\t\t    " << arrivalTime << "\t\t    " 
				<< burstTime << "\t\t    " << waitTime << "\t\t    " 
				<< turnAroundTime << "\t\t             " << responseTime << "\n";
			avgResponseTime += responseTime;
			avgWaitingTime += waitTime;
		}
		cout << "\n\t Average Waiting Time: " << avgWaitingTime/double((*this).getProcessesCount())
			 << "\n\tAverage Response Time: " << avgResponseTime/double((*this).getProcessesCount());
	}

	int dumpChart(ProcessQueue& ganttQueue, int startIndex, int finishIndex, int time)
	{
		int processCount = ganttQueue.getProcessesCount();
		int tempTime = time;
		for (int i = startIndex; i <= finishIndex; i++)
		{
			Process p = ganttQueue[i];
			int dupTime = tempTime;
			if (i == 0)
				cout << " ";
			for (int j = 0; dupTime != 0; j++)
			{
				cout << " ";
				dupTime /= 10;
			}
			if (p.getBurstTime() % 2 != 0)
				cout << " ";
			cout << setw((p.getBurstTime() / 2) + p.getProcessName().length()) << p.getProcessName();
			cout << setw(p.getBurstTime() / 2) << "";
			if (p.getBurstTime() % 2 != 0)
				cout << " ";
			tempTime += p.getBurstTime();
			dupTime = time;

		}
		cout << "\n";
		tempTime = time;
		if (tempTime != 0)
		{
			int dupTime = tempTime;
			for (int i = 0; dupTime != 0; i++)
			{
				cout << "|";
				dupTime /= 10;
			}
		}
		for (int i = startIndex; i <= finishIndex; i++)
		{
			Process p = ganttQueue[i];
			cout.fill('-');
			if (i == 0)
				cout << "|";
			if (p.getBurstTime() % 2 != 0)
				cout << "-";
			cout << setw(p.getBurstTime() + p.getProcessName().length()) << "";
			tempTime += p.getBurstTime();
			int dupTime = tempTime;
			for (int j = 0; dupTime != 0; j++)
			{
				cout << "|";
				dupTime /= 10;
			}
		}
		cout << "\n";
		tempTime = time;
		if (tempTime != 0)
		{
			cout << tempTime;
		}
		for (int i = startIndex; i <= finishIndex; i++)
		{
			Process p = ganttQueue[i];
			cout.fill(' ');
			if (i == 0)
				cout << tempTime;
			if (p.getBurstTime() % 2 != 0)
			{
				cout << " ";
			}
			cout << setw((p.getBurstTime() + p.getProcessName().length())) << "";
			tempTime += p.getBurstTime();
			cout << tempTime;
		}
		return tempTime;
	}

	void dumpQueues()
	{
		cout << "Process ID\tArrival Time\tBurst Time\n";
		for (int i = 0; i < getProcessesCount(); i++)
		{
			cout << "    " << (*this)[i].getProcessName() << "\t\t     " << (*this)[i].getArrivalTime()
				<< "\t\t    " << (*this)[i].getBurstTime() << "\n";
		}
		cout << "\n";
		cout << " QUEUE 0 RR - 5: ";
		for (int i = 0; i < queue0.getProcessesCount(); i++)
		{
			cout << queue0[i].getProcessName() << ":" << queue0[i].getArrivalTime() << ":" << queue0[i].getBurstTime();
			cout << "  ";
		}
		cout << "\n";
		cout << "QUEUE 1 RR - 10: ";
		for (int i = 0; i < queue1.getProcessesCount(); i++)
		{
			cout << queue1[i].getProcessName() << ":" << queue1[i].getArrivalTime() << ":" << queue1[i].getBurstTime();
			cout << "  ";
		}
		cout << "\n";
		cout << "   QUEUE 2 SRTF: ";
		for (int i = 0; i < queue2.getProcessesCount(); i++)
		{
			cout << queue2[i].getProcessName() << ":" << queue2[i].getArrivalTime() << ":" << queue2[i].getBurstTime();
			cout << "  ";
		}
	}

	void selectMinimumBurstProcess(int& queue2Itr)
	{
		int smallest = queue2[queue2Itr].getBurstTime();
		int index = queue2Itr;
		for (int i = queue2Itr; i < queue2.getProcessesCount(); i++)
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
		while (queue1Itr < queue1.getProcessesCount() && queue1[queue1Itr].getArrivalTime() + 20 <= time)
		{
			Process p = queue1[queue1Itr];
			p.setArrivalTime(queue1[queue1Itr].getArrivalTime() + 20);
			queue0.add(p);
			dumpQueues();
			Sleep(1000);
			system("CLS");
			queue1.remove(queue1Itr);
			dumpQueues();
			Sleep(1000);
			system("CLS");
		}
	}

	void promoteToQueue1(int& queue1Itr, int& queue2Itr, int& time)
	{
		while (queue2Itr < queue2.getProcessesCount() && queue2[queue2Itr].getArrivalTime() + 30 <= time)
		{
			Process p = queue2[queue2Itr];
			p.setArrivalTime(queue2[queue2Itr].getArrivalTime() + 30);
			queue1.add(p);
			dumpQueues();
			Sleep(1000);
			system("CLS");
			queue2.remove(queue2Itr);
			dumpQueues();
			Sleep(1000);
			system("CLS");
		}
		promoteToQueue0(queue1Itr, time);
	}

	void runQueue0(int& RRIterator, ProcessQueue& ganttQueue, int& ganttIterator,
				   int& time)
	{
		if (RRIterator < queue0.getProcessesCount())
		{
			Process p = queue0[RRIterator];
			p.setArrivalTime(time);
			ganttQueue.add(p);
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
				queue1.add(p);
				dumpQueues();
				Sleep(1000);
				system("CLS");
				ganttQueue[ganttIterator].setBurstTime(currProcessDoneBurst);
				queue0[RRIterator].setBurstTime(currProcessDoneBurst);
			}
			RRIterator++;
			ganttIterator++;
		}
	}

	void runQueue1(int& RRIterator, ProcessQueue& ganttQueue, int& ganttIterator,
		int& time)
	{
		if (RRIterator < queue1.getProcessesCount())
		{
			Process p = queue1[RRIterator];
			p.setArrivalTime(time);
			ganttQueue.add(p);
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
				queue2.add(p);
				dumpQueues();
				Sleep(1000);
				system("CLS");
				ganttQueue[ganttIterator].setBurstTime(currProcessDoneBurst);
				queue1[RRIterator].setBurstTime(currProcessDoneBurst);
			}
			RRIterator++;
			ganttIterator++;
		}
	}

	void runQueue2(int& SRTFIterator, ProcessQueue& ganttQueue, int& ganttIterator,
		int& time)
	{
		if (SRTFIterator < queue2.getProcessesCount())
		{
			selectMinimumBurstProcess(SRTFIterator);
			Process p = queue2[SRTFIterator];
			p.setArrivalTime(time);
			ganttQueue.add(p);
			time += queue2[SRTFIterator].getBurstTime();
			SRTFIterator++;
			ganttIterator++;
		}
	}

	ProcessQueue runQueues()
	{
		sortProcessByArrivalTime();
		ProcessQueue ganttQueue;
		int queue0Iterator = 0, queue1Iterator = 0, queue2Iterator = 0, origIterator = 0, ganttIterator = 0;
		int time = 0;
		while (origIterator < getProcessesCount() ||
			   queue0Iterator < queue0.getProcessesCount() ||
			   queue1Iterator < queue1.getProcessesCount() ||
			   queue2Iterator < queue2.getProcessesCount())
		{
			while (origIterator < getProcessesCount() && (*this)[origIterator].getArrivalTime() <= time)
			{
				queue0.add((*this)[origIterator]);
				dumpQueues();
				Sleep(1000);
				system("CLS");
				origIterator++;
			}
			if (!(queue0.isEmpty()) && queue0Iterator < queue0.getProcessesCount())
			{
				runQueue0(queue0Iterator, ganttQueue, ganttIterator, time);
				promoteToQueue1(queue1Iterator, queue2Iterator, time);
			}
			else if (!(queue1.isEmpty()) && queue0Iterator == queue0.getProcessesCount()
				&& queue1Iterator != queue1.getProcessesCount())
			{
				runQueue1(queue1Iterator, ganttQueue, ganttIterator, time);
				promoteToQueue1(queue1Iterator, queue2Iterator, time);
			}
			else if (!(queue2.isEmpty()) && queue0Iterator == queue0.getProcessesCount()
				&& queue1Iterator == queue1.getProcessesCount() && queue2Iterator != queue2.getProcessesCount())
			{
				runQueue2(queue2Iterator, ganttQueue, ganttIterator, time);
				promoteToQueue1(queue1Iterator, queue2Iterator, time);
			}
			if (queue0Iterator == queue0.getProcessesCount() 
				&& queue1Iterator == queue1.getProcessesCount()
				&& queue2Iterator == queue2.getProcessesCount()
				&& origIterator != (*this).getProcessesCount())
			{
				time = (*this)[origIterator].getArrivalTime();
			}
		}
		return ganttQueue;
	}

public:

	MLFQueue() : queue0(5), queue1(10)
	{}

	void displayGanttChart()
	{
		ProcessQueue ganttQueue = runQueues();
		dumpQueues();
		cout << "\n\n";
		ganttQueue.addIdleTime();
		ganttQueue.sortProcessByArrivalTime();
		int processCount = ganttQueue.getProcessesCount();
		int totalTime = 0;
		for (int i = 0; i < ganttQueue.getProcessesCount(); i++)
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
			time = dumpChart(ganttQueue, startIndex, finishIndex, time);
			startIndex = finishIndex + 1;
			cout << "\n\n";
		}

		dumpGanttChartStats(ganttQueue);
	}
};

#endif