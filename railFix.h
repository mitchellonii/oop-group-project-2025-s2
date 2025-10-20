#ifndef RAILFIX_H
#define RAILFIX_H
#include "Task.h"
#include <string>

using namespace std;

class railFix : public Task{
    private:
        string necessaryTool;
    public:
        railFix();
        railFix(int timeTaken, string necessaryTool);
        void fixRail();
};

#endif