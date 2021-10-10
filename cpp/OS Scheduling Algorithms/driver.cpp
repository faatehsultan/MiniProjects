#include <iostream>
#include <fstream>
#include "ProcessQueue.h"
#include "Process.h"
#include "SRTF.h"
#include "RR.h"
#include "startApp.h"
using namespace std;

int main()
{
    char c;

   /* startApp x;
    x.readFromFile("InputFile1.txt");
    x.displayGanttChart();

    cout << "\n\nPress Enter to start executing file 2...";
    cin.get(c);
    system("CLS");

    startApp y;
    y.readFromFile("InputFile2.txt");
    y.displayGanttChart();

    cout << "\n\nPress Enter to start executing file 3...";
    cin.get(c);
    system("CLS");
    */
    startApp z;
    z.readFromFile("InputFile3.txt");
    z.displayGanttChart();
    
    return 0;
}