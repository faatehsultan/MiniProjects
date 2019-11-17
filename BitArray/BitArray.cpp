#include<iostream>
#include "BitArray.h"
using namespace std;


bool BitArray::isValidBit(int i)
{
	return (i >= 0 && i < capacity);
}

unsigned long long BitArray::toBin(long long num)
{
	if (num < 0)
		num = num * (-1);
	unsigned long long bin = 0, n = num, ten = 1;
	while (!(n % 2))
	{
		ten = ten * 10;
		n = n / 2;
	}
	n = 0;
	while (num)
	{
		n = (n * 10) + (num % 2);
		num = num / 2;
	}
	while (n)
	{
		bin = (bin * 10) + (n % 10);
		n = n / 10;
	}
	return bin * ten;
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

int BitArray::getCapacity()
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

int BitArray::checkBitStatus(int bitNo)
{
	return data[bitNo / 8] & (1 << (bitNo % 8));
}

void BitArray::invert(int bitNo)
{
	data[bitNo / 8] = data[bitNo / 8] ^ (1 << (bitNo % 8));
}

void BitArray::dump()
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

void BitArray::dumpIEEE754()
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

void BitArray::setIntegralValue(unsigned long long n)
{
	////assuming that integral value is within the allocated range of bitarray
	//if (n)
	//	on(0);
	//int bitCount = 1;
	//while (getUnSignedIntegralValue() <= n)
	//{
	//	shiftLeft(1);
	//	bitCount++;
	//}
	//shiftRight(1);
	//bitCount--;
	//for (int i = 0; i <= capacity/*getUnSignedIntegralValue() <= n*/; i++)
	//{
	//	on(i);
	//	if (getUnSignedIntegralValue() > n)
	//		off(i);
	//}
	unsigned long long binTemp = toBin(n), bits = 0;;
	while (binTemp)
	{
		binTemp = binTemp / 10;
		bits++;
	}
	if (bits > capacity)
	{
		delete data;
		data = nullptr;
		//resize the bitarray
		capacity = bits;
		int s = (int)ceil((float)capacity / 8);
		data = new unsigned char[s];
		for (int i = 0; i < s; i++)
			data[i] = data[i] & 0;
	}
	unsigned long long i = 0, bin = toBin(n);
	while (bin)
	{
		if (bin % 10)
			on(i);
		bin = bin / 10;
		i++;
	}
}