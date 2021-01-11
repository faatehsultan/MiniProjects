#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H
#include <iostream>
using namespace std;
//BitArray class
class BitArray
{
	int capacity;
	unsigned char * data;
	bool isValidBit(int i)const;
	void resize(int newCapacity);
public:
	BitArray(int n = 8);
	~BitArray();
	int getCapacity()const;
	BitArray(const BitArray & ref);
	void on(int bitNo);
	void off(int bitNo);
	int checkBitStatus(int bitNo)const;
	void invert(int bitNo);
	void dump()const;
	friend ostream & operator<<(ostream & coutBitArray, const BitArray & ba);
	void dumpIEEE754()const;
	BitArray AND(BitArray);
	BitArray OR(BitArray);
	void shiftLeft(int);
	void shiftRight(int);
	unsigned long long getUnSignedIntegralValue();
	void setIntegralValue(unsigned long long);
	explicit operator unsigned long long int();
};
#endif BIT_ARRAY_H