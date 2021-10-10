#ifndef START_APP_H
#define START_APP_H

#include "MLFQueue.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class startApp
{
	MLFQueue queue;

	char* tokenize(char* str, int& length, char delim)
	{
		int index = -1;
		bool found = 0;
		for (int i = 0; i < length && !found; i++)
		{
			if (str[i] == delim)
			{
				index = i;
				found = 1;
			}
		}
		if (index != -1)
		{
			char* token = new char[index + 1];
			int i;
			for (i = 0; i < index; i++)
			{
				token[i] = str[i];
			}
			token[i] = '\0';
			index++;
			i = 0;
			int tempIndex = index;
			for (i = 0; index < length; i++, index++)
			{
				str[i] = str[index];
			}
			length -= tempIndex;
			str[i] = '\0';
			return token;
		}
		else
		{
			return str;
		}
	}

	int convertStrToNum(char* arr)
	{
		int num = 0;
		int multiplier = 1;
		for (int i = 0; arr[i] != '\0'; i++)
		{
			num = num * multiplier + arr[i] - '0';
			multiplier *= 10;
		}
		return num;
	}

public:
	void readFromFile(string fileName)
	{
		ifstream fin;
		fin.open(fileName);
		while (!(fin.eof()))
		{
			string s;
			fin >> s;
			const int size = s.length();
			char* charStr = new char[size];
			int i;
			for (i = 0; i < s.length(); i++)
			{
				charStr[i] = s[i];
			}
			charStr[i] = '\0';
			char* pid;
			char* arrivalStr;
		    char* burstStr;
			int length = s.length();
			pid = tokenize(charStr, length, ':');
			arrivalStr = tokenize(charStr, length, ':');
			burstStr = tokenize(charStr, length, ':');
			int arrival = convertStrToNum(arrivalStr);
			int burst = convertStrToNum(burstStr);
			string s2 = "P";
			s2 += pid;
			queue.add(Process(s2, burst, arrival));
		}
	}
	void displayGanttChart()
	{
		queue.displayGanttChart();
	}
};

#endif