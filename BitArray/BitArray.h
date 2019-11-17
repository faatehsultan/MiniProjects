#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

class BitArray
{
	int capacity;
	unsigned char * data;
	bool isValidBit(int i);
	//extra
	static unsigned long long toBin(long long);
public:
	BitArray(int n = 8);
	~BitArray();
	int getCapacity();
	BitArray(const BitArray & ref);
	void on(int bitNo);
	void off(int bitNo);
	int checkBitStatus(int bitNo);
	void invert(int bitNo);
	void dump();
	void dumpIEEE754();
	BitArray AND(BitArray);
	BitArray OR(BitArray);
	void shiftLeft(int);
	void shiftRight(int);
	unsigned long long getUnSignedIntegralValue();
	void setIntegralValue(unsigned long long);
};
#endif BIT_ARRAY_H