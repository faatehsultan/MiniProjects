#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H
#include "Queues.h"

class RoundRobin : public Queue
{
	int timeQuantum;
public:
	RoundRobin(int timeQuantum);
	int getTimeQuantum();
	void setTimeQuantum(int timeQuantum);
};
#endif // !ROUND_ROBIN