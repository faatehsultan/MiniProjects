#include<iostream>
#include "BitArray.h"
using namespace std;


bool BitArray::isValidBit(int i)const
{
	return (i >= 0 && i < capacity);
}

void BitArray::resize(int newCapacity)
{
	int s = (int)ceil((float)newCapacity / 8);
	unsigned char * temp = new unsigned char[s];
	for (int i = 0; i < s; i++)
		temp[i] = data[i];
	this->~BitArray();
	capacity = newCapacity;
	data = temp;
}

BitArray::BitArray(int n)
{
	capacity = n;
	int s = (int)ceil((float)capacity / 8);
	data = new unsigned char[s];
	for (int i = 0; i < s; i++)
		data[i] = data[i] & 0;
}

BitArray::~BitArray()
{
	if (!data)
		return;
	capacity = 0;
	delete data;
	data = nullptr;
}

int BitArray::getCapacity()const
{
	return capacity;
}

BitArray::BitArray(const BitArray & ref)
{
	capacity = ref.capacity;
	int s = (int)ceil((float)capacity / 8);
	data = new unsigned char[s];
	for (int i = 0; i < s; i++)
		data[i] = ref.data[i];
}

void BitArray::on(int bitNo)
{
	data[bitNo / 8] = data[bitNo / 8] | (1 << (bitNo % 8));
}

void BitArray::off(int bitNo)
{
	data[bitNo / 8] = data[bitNo / 8] & ~(1 << (bitNo % 8));
}

int BitArray::checkBitStatus(int bitNo)const
{
	return data[bitNo / 8] & (1 << (bitNo % 8));
}

void BitArray::invert(int bitNo)
{
	data[bitNo / 8] = data[bitNo / 8] ^ (1 << (bitNo % 8));
}

void BitArray::dump()const
{
	for (int i = capacity - 1; i >= 0; i--)
	{
		if (checkBitStatus(i))
			cout << 1;
		else
			cout << 0;
		if (i % 8 == 0)
			cout << " ";
	}
}

void BitArray::dumpIEEE754()const
{
	cout << "IEEE-754 Floating Point Value: ";
	int i = capacity - 1;
	checkBitStatus(i) ? cout << 1 << " " : cout << 0 << " ";
	i--;
	for (; i >= 23; i--)
		checkBitStatus(i) ? cout << 1 : cout << 0;
	cout << " ";
	for (; i >= 0; i--)
		checkBitStatus(i) ? cout << 1 : cout << 0;
}

BitArray BitArray::AND(BitArray ba)
{
	int resultCapacity = getCapacity();
	if (ba.getCapacity() > resultCapacity)
		resultCapacity = ba.getCapacity();
	BitArray result(resultCapacity);
	for (int i = 0; i < resultCapacity; i++)
	{
		if (checkBitStatus(i) && ba.checkBitStatus(i))
			result.on(i);
	}
	return result;
}

BitArray BitArray::OR(BitArray ba)
{
	int resultCapacity = getCapacity();
	if (ba.getCapacity() > resultCapacity)
		resultCapacity = ba.getCapacity();
	BitArray result(resultCapacity);
	for (int i = 0; i < resultCapacity; i++)
	{
		if (checkBitStatus(i) || ba.checkBitStatus(i))
			result.on(i);
	}
	return result;
}

void BitArray::shiftLeft(int noOfShifts)
{
	for (int i = 0; i < (int)ceil((float)capacity / 8); i++)
		data[i] = data[i] << noOfShifts;
}

void BitArray::shiftRight(int noOfShifts)
{
	for (int i = 0; i < (int)ceil((float)capacity / 8); i++)
		data[i] = data[i] >> noOfShifts;
}

unsigned long long BitArray::getUnSignedIntegralValue()
{
	unsigned long long result = 0;
	for (int i = 0; i < getCapacity(); i++)
	{
		if (checkBitStatus(i))
			result = result + (1 << i);
	}
	return result;
}

void BitArray::setIntegralValue(unsigned long long n) //non-negative numbers only
{
	int newCapacity = 0;
	for (unsigned long long int i = 1; i <= n; i = i * 2, newCapacity++);
	resize(newCapacity);

	for (int i = capacity; i >= 0; i--)
	{
		on(i);
		if (getUnSignedIntegralValue() > n)
			off(i);
	}
}

BitArray::operator unsigned long long int() //non-negative numbers only
{
	return getUnSignedIntegralValue();
}


ostream & operator<<(ostream & coutBitArray, const BitArray & ba)
{
	ba.dump();
	return coutBitArray;
}
