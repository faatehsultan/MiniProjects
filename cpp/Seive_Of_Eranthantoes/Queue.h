#ifndef QUEUE_H
#define QUEUE_H
#include <exception>
template <typename T>
class Queue
{
private:
	int rear;
	int front;
	int capacity;
	int noOfElements;
	T* data;
public:
	Queue()
	{
		rear = front = noOfElements = 0;
		capacity = 1;
		data = new T[capacity];
	}
	~Queue()
	{
		if (!data)
			return;
		delete[]data;
		data = nullptr;
	}
	bool isEmpty()
	{
		return noOfElements == 0;
	}
	bool isFull()
	{
		return noOfElements == capacity;
	}
	int getNumberOfElements()
	{
		return noOfElements;
	}
	int getCapacity()
	{
		return capacity;
	}
	void enQueue(T val)
	{
		if (isFull())
		{
			reSize(capacity * 2);
		}
		data[rear]=val;
		rear = (rear + 1) % capacity;
		noOfElements++;
	}
	T deQueue()
	{
		if (isEmpty())
			throw exception();
		T val = data[front];
		front = (front + 1) % capacity;
		noOfElements--;
		if (noOfElements > 0 && noOfElements == capacity / 4)
			reSize(capacity / 2);
		return val;
	}
	T getElementAtFront()
	{
		if (isEmpty())
			throw exception("Helloo");
		return data[front];
	}
private:
	void reSize(int newSize)
	{
		T* temp = new T[newSize];
		for (int j = 0, i = front; j < noOfElements; j++)
		{
			temp[j] = data[i];
			i = (i + 1) % capacity;
		}
		this->~Queue();
		data = temp;
		capacity = newSize;
		rear = noOfElements;
		front = 0;
	}
};
#endif // !QUEUE_H
