#include<iostream>
using namespace std;
#include <queue>
#include <cmath>
#include "Queue.h"
void displayPrime(int N)
{

	Queue<int>primeQueue, q1;
	for (int i = 2; i <= N; i++)
		q1.enQueue(i);
	int limit = sqrt(N), p;
	do
	{
		p = q1.deQueue();
		Queue<int> temp;
		primeQueue.enQueue(p);
		while (!q1.isEmpty())
		{
			if (q1.getElementAtFront() % p != 0)
			{
				temp.enQueue(q1.getElementAtFront());
			}
			q1.deQueue();
		}
		while (!temp.isEmpty())
		{
			q1.enQueue(temp.deQueue());
		}
	} while (p < limit);
	while (!q1.isEmpty())
	{
		primeQueue.enQueue(q1.deQueue());
	}
	while (!primeQueue.isEmpty())
	{
		cout << primeQueue.deQueue()<< ' ';
	}
}
int main()
{
	cout << "Enter the number N:";
	int N;
	cin >> N;
	displayPrime(N);
	cout << "\n*********************new*************************\n";
	Queue<int> q;
	try
	{
		q.getElementAtFront();
	}
	catch (exception & e)
	{
		cout <<"Exception: "<< e.what();
	}
	return 0;
}