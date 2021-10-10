#ifndef RR_H
#define RR_H

#include <iomanip>
#include "ProcessQueue.h"

class RR : public ProcessQueue
{
	int timeQuantum;

public:

	RR(int timeQuantum)
	{
		setTimeQuantum(timeQuantum);
	}
	
	int getTimeQuantum()
	{
		return timeQuantum;
	}

	void setTimeQuantum(int timeQuantum)
	{
		if (timeQuantum > 0)
		{
			this->timeQuantum = timeQuantum;
		}
	}
};

#endif