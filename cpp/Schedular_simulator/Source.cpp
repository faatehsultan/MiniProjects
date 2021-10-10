#include <iostream>
#include <fstream>
using namespace std;
#include "MLFQ1.h"
int readProcessfromFile(string fName,MLFQueue &q)
{
	int count=0;
	ifstream ifs;
	ifs.open(fName);
	while (!(ifs.eof()))
	{
		if (!(ifs.eof()))
		{
			int id, arr, burst;
			ifs >> id;
			ifs >> arr;
			ifs >> burst;
			q.addProcess(Process(id, burst, arr));
			count++;
		}
	}
	return count;
}
void displayGanttChart(MLFQueue &q,int processCount)
{
	q.displayGanttChart(processCount);
}
int main()
{
	MLFQueue q;
	int proCount= readProcessfromFile("InputFile1.txt",q);
	displayGanttChart(q,proCount);
	return 0;
}
