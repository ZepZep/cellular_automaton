#ifndef CASIMULATOR_H
#define CASIMULATOR_H


class CASimulator
{
public:
    CASimulator();

    void setLine(bool *line, int len);
    void setRule(int rule);

    bool *nextLine();

    int getLen();
    int getRule();

private:
    int length;
    int rule;

    bool *currentLine;
    bool *futureLine;

    int getNeighbours(int c);
};

#endif // CASIMULATOR_H
