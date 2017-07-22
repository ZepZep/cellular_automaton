#include "casimulator.h"

#include <cmath>

CASimulator::CASimulator()
{
    length = 0;
    currentLine = new bool[1];
    futureLine = new bool[1];
}

void CASimulator::setLine(bool *line, int len)
{
    if(length < len)
    {
        delete[] currentLine;
        delete[] futureLine;

        currentLine = new bool[len];
        futureLine = new bool[len];
    }

    length = len;

    for(int i = 0; i<len; i++)
    {
        currentLine[i] = line[i];
    }
}

void CASimulator::setRule(int rule)
{
    this->rule = rule;
}

bool *CASimulator::nextLine()
{
    for(int i=0; i<length; i++)
    {
        bool cell = (rule >> getNeighbours(i)) & 1;
        futureLine[i]=cell;
    }

    bool *tmp = futureLine;
    futureLine = currentLine;
    currentLine = tmp;

    return currentLine;
}

int CASimulator::getLen()
{
    return length;
}

int CASimulator::getRule()
{
    return rule;
}

int CASimulator::getNeighbours(int c)
{
    int neigh = 0;
    for(int i=0; i<3; i++)
    {
        int index = (length + c + 1 - i) % length;
        neigh += ( (int)currentLine[index] ) << i;
    }

    return neigh;
}
