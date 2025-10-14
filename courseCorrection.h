#ifndef COURSECORRECTION_H
#define COURSECORRECTION_H
#include "Task.h"

class courseCorrection : public Task{
    private:
        bool toolsNeeded = false;
        int timeTaken = 5;
    public:
        void correctCourse();
};

#endif