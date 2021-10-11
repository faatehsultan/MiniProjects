#include"RoundRobin.h"
RoundRobin::RoundRobin(int timeQuantum)
{
	setTimeQuantum(timeQuantum);
}
int RoundRobin::getTimeQuantum()
{
	return timeQuantum;
}
void RoundRobin::setTimeQuantum(int timeQuantum)
{
	if (timeQuantum > 0)
		this->timeQuantum = timeQuantum;
}