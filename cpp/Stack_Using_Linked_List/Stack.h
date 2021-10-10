#ifndef STACK_H
#define STACK_H
#include<exception>
template <typename T>
struct Node
{
	T info;
	Node <T>* next;
public:
	Node()
	{
		next = nullptr;
	}
	Node(T val)
	{
		info = val;
		next = nullptr;
	}
};
template <typename T>
class Stack
{
	int numberOfElements;
	Node <T>* head;
	void insertAtHead(T val)
	{
		Node <T>* x = new Node<T>(val);
		x->next = head;
		head = x;
		numberOfElements++;
	}
	void removeAtHead()
	{
		Node <T>* p = head;
		if (p != nullptr)
		{
			head = p->next;
			numberOfElements--;
			delete p;
			return;
		}
	}
public:
	Stack()
	{
		numberOfElements = 0;
		head = nullptr;
	}
	void push(T val)
	{
		insertAtHead(val);
	}
	T pop()
	{
		T val;
		if (head != nullptr)
			val = head->info;
		else
			throw exception();
		removeAtHead();
		numberOfElements--;
	}
	int getNumberOfElements()
	{
		return numberOfElements;
	}
	bool isEmpty()
	{
		return numberOfElements == 0;
	}
	T stackTop()
	{
		if (isEmpty())
			throw exception();
		return head->info;
	}
	~Stack()
	{
		if (head != nullptr)
		{
			removeAtHead();
			numberOfElements--;
		}
	}
};
#endif // !STACK_H
