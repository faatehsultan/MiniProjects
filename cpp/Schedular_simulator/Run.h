#ifndef RUN_H
#define RUN_H

#include "MLFQ.h"
#include <iostream>
#include <fstream>
using namespace std;

class startApp
{
	MLFQueue queue;

public:
	void readFromFile(string fileName)
	{
		ifstream ifs;
		ifs.open(fileName);
		while (!(ifs.eof()))
		{
			if (!(ifs.eof()))
			{
				int id, arr, burst;
				ifs >> id;
				ifs >> arr;
				ifs >> burst;
				queue.addProcess(Process(id, burst, arr));
			}
		}
	}
	void displayGanttChart()
	{
		queue.GanttChart();
	}
};
#endif