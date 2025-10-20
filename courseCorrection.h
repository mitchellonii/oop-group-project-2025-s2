#ifndef COURSECORRECTION_H
#define COURSECORRECTION_H
#include "Task.h"
#include <string>

class courseCorrection : public Task{
    private:
        std::string correctionDirection;
    public:
        courseCorrection();
        courseCorrection(int timeTaken, std::string correctionDirection);
        void correctCourse();
        std::string get_correctionDirection();
        void set_correctionDirection(std::string newCorrectionDirection);
};

#endif